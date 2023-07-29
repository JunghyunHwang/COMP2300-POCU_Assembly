#include <assert.h>

#include "potushop.h"
#include "image.h"

ALIGN16 typedef struct vector4 {
    float x;
    float y;
    float z;
    float w;
} vector4_t;

const static vector4_t GRAYSCALE = { 0.3f, 0.59f, 0.11f, 0.f };

const static vector4_t SEPIA_R = { 0.393f, 0.769f, 0.189f, 0.f };
const static vector4_t SEPIA_G = { 0.349f, 0.686f, 0.168f, 0.f };
const static vector4_t SEPIA_B = { 0.272f, 0.534f, 0.131f, 0.f };

const static vector4_t ONE = { 1.f, 1.f, 1.f, 1.f };
static float s_limits;

static float s_brightness;

static float s_rescale;
static float s_in_min;
static float s_in_max;
static float s_out_min;

void set_brightness_arg(int brightness)
{
    assert(brightness >= -100 && brightness <= 100);
    assert(sizeof(vector4_t) == 16);

    if (brightness < 0) {
        s_limits = 0.0f;
    }
    else {
        s_limits = 1.0f;
    }

    s_brightness = brightness / 255.0;
}

void set_level_args(int in_min, int in_max, int out_min, int out_max)
{
    assert(in_min >= 0 && in_min <= 253);
    assert(in_max >= 2 && in_max <= 255);
    assert(in_min < in_max);

    assert(out_min >= 0 && out_min <= 255);
    assert(out_max >= 0 && out_max <= 255);

    s_in_min = in_min / 255.0;
    s_in_max = in_max / 255.0;
    s_out_min = out_min / 255.0;
    s_rescale = (float)(out_max - out_min) / (in_max - in_min);
}

void to_grayscale(void)
{
    __asm {
        mov ecx, g_num_pixels
        mov eax, 00h

    loop_gray:
        movaps xmm0, [g_pixels + eax]
        dpps xmm0, GRAYSCALE, 01110111b
        movaps [g_pixels+eax], xmm0

        add eax, 10h
        loop loop_gray
    }
}

void to_sepia(void)
{
    __asm {
        mov ecx, g_num_pixels
        mov eax, 00h
        
    loop_sepia:
        xorps xmm1, xmm1
        movaps xmm0, [g_pixels+eax]

        movaps xmm2, xmm0
        dpps xmm2, SEPIA_R, 01110001b
        orps xmm1, xmm2

        movaps xmm2, xmm0
        dpps xmm2, SEPIA_G, 01110010b
        orps xmm1, xmm2

        movaps xmm2, xmm0
        dpps xmm2, SEPIA_B, 01110100b
        orps xmm1, xmm2

        minps xmm1, ONE
        movaps [g_pixels+eax], xmm1

        add eax, 10h
        loop loop_sepia
    }
}

void change_brightness(void)
{
    __asm {
        mov ecx, g_num_pixels
        mov eax, OFFSET g_pixels

        movss xmm1, s_brightness
        movss xmm2, s_limits

        shufps xmm1, xmm1, 00h
        shufps xmm2, xmm2, 00h

    loop_brightness:
        movaps xmm0, [eax]
        addps xmm0, xmm1
        maxps xmm0, xmm2

        movaps [eax], xmm0

        add eax, 10h
        loop loop_brightness
    }
}

void change_levels(void)
{
    __asm {
        mov ecx, g_num_pixels
        mov eax, OFFSET g_pixels

        movss xmm1, s_in_min
        movss xmm2, s_in_max
        movss xmm3, s_out_min
        movss xmm4, s_rescale

        shufps xmm1, xmm1, 00h
        shufps xmm2, xmm2, 00h
        shufps xmm3, xmm3, 00h
        shufps xmm4, xmm4, 00h

    loop_levels:
        movaps xmm0, [eax]
        maxps xmm0, xmm1
        minps xmm0, xmm2
        subps xmm0, xmm1
        mulps xmm0, xmm4
        addps xmm0, xmm3

        movaps [eax], xmm0
        
        add eax, 10h
        loop loop_levels
    }
}
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

static vector4_t s_brightness = { 0.f, 0.f, 0.f, 0.f };

const static vector4_t ZERO = { 0.f, 0.f, 0.f, 0.f };
const static vector4_t ONE = { 1.f, 1.f, 1.f, 1.f };
static vector4_t limits = { 1.f, 1.f, 1.f, 1.f };

static vector4_t s_levelValue = { 0.f, 0.f, 0.f, 0.f };
static vector4_t s_in_min = { 0.f, 0.f, 0.f, 0.f };
static vector4_t s_out_min = { 0.f, 0.f, 0.f, 0.f };

void set_brightness_arg(int brightness)
{
    assert(brightness >= -100 && brightness <= 100);
    assert(sizeof(vector4_t) == 16);

    if (brightness < 0) {
        limits = ZERO;
    }
    else {
        limits = ONE;
    }

    float brightnessValue = brightness / 255.0;
    s_brightness.x = brightnessValue;
    s_brightness.y = brightnessValue;
    s_brightness.z = brightnessValue;
}

void set_level_args(int in_min, int in_max, int out_min, int out_max)
{
    assert(in_min >= 0 && in_min <= 253);
    assert(in_max >= 2 && in_max <= 255);
    assert(in_min < in_max);

    assert(out_min >= 0 && out_min <= 255);
    assert(out_max >= 0 && out_max <= 255);

    float value = (double)(out_max - out_min) / (in_max - in_min);
    s_levelValue.x = value;
    s_levelValue.y = value;
    s_levelValue.z = value;

    value = in_min / 255.0;
    s_in_min.x = value;
    s_in_min.y = value;
    s_in_min.z = value;

    value = out_min / 255.0;
    s_out_min.x = value;
    s_out_min.y = value;
    s_out_min.z = value;
}

void to_grayscale(void)
{
    __asm {
        mov ecx, g_num_pixels
        xor eax, eax

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
        xor eax, eax
        
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
        xor eax, eax

    loop_brightness:
        movaps xmm0, [g_pixels+eax]
        addps xmm0, s_brightness
        maxps xmm0, limits
        movaps [g_pixels+eax], xmm0

        add eax, 10h
        loop loop_brightness
    }
}

void change_levels(void)
{
    __asm {
        mov ecx, g_num_pixels
        xor eax, eax

    loop_levels:
        movaps xmm0, [g_pixels+eax]
        subps xmm0, [s_in_min]
        minps xmm0, [s_in_min]
        mulps xmm0, [s_levelValue]
        addps xmm0, [s_out_min]

        movaps [g_pixels+eax], xmm0
        
        add eax, 10h
        loop loop_levels
    }
}
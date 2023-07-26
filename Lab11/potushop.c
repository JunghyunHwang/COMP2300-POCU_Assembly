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

void set_brightness_arg(int brightness)
{
    assert(brightness >= -100 && brightness <= 100);
    assert(sizeof(vector4_t) == 16);
}

void set_level_args(int in_min, int in_max, int out_min, int out_max)
{
    assert(in_min >= 0 && in_min <= 253);
    assert(in_max >= 2 && in_max <= 255);
    assert(in_min < in_max);

    assert(out_min >= 0 && out_min <= 255);
    assert(out_max >= 0 && out_max <= 255);
}

void to_grayscale(void)
{
    __asm {
        mov ecx,g_num_pixels
        mov eax,00h

    loop_gray:
        movaps xmm0,[g_pixels+eax]
        mulps xmm0,GRAYSCALE
        haddps xmm0,xmm0
        haddps xmm0,xmm0
        movaps [g_pixels+eax],xmm0

        add eax, 10h
        loop loop_gray
    }
}

void to_sepia(void)
{

}

void change_brightness(void)
{

}

void change_levels(void)
{

}
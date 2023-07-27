#include "transformer.h"

#include <stdio.h>

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

const static vec4_t v0 = { 1.0, 2.0, 3.0, 4.0 };
const static vec4_t v1 = { 5.0, 6.0, 7.0, 8.0 };
const static vec4_t v2 = { 9.0, 10.0, 11.0, 12.0 };
const static vec4_t v3 = { 13.0, 14.0, 15.0, 16.0 };

size_t read_points(vec4_t* points, const size_t count)
{
    vec4_t* p_points = points;
    size_t number_of_points = 0;
    
    for (size_t i = 0; i < count; ++i) {
        if (scanf("%f %f %f", &p_points->x, &p_points->y, &p_points->z) == EOF) {
            break;
        }

        ++p_points;
        ++number_of_points;
    }

    return number_of_points;
}

void print_csv(const vec4_t* points, const size_t count)
{
    const vec4_t* p_points = points;

    for (size_t i = 0; i < count; ++i) {
        printf("%.4f, %.4f %.4f\n", p_points->x, p_points->y, p_points->z);
        ++p_points;
    }
}

void transpose(mat4_t* mat)
{
    __asm {
        mov eax, mat

        movaps xmm0,[eax]
        movaps xmm1, [eax+16]
        movaps xmm2, [eax+32]
        movaps xmm3, [eax+48]

        movaps xmm4, xmm0
        shufps xmm4, xmm1, 01000100b
        movaps xmm5, xmm0
        shufps xmm5, xmm1, 11101110b
        movaps xmm6, xmm2
        shufps xmm6, xmm3, 01000100b
        movaps xmm7, xmm2
        shufps xmm7, xmm3, 11101110b

        movaps xmm0, xmm4
        shufps xmm4, xmm6, 10001000b

        movaps [eax], xmm4

        movaps xmm4, xmm0
        shufps xmm4, xmm6, 11011101b

        movaps [eax+16], xmm4

        movaps xmm1, xmm5
        shufps xmm5, xmm7, 10001000b

        movaps [eax+32], xmm5
        
        movaps xmm5, xmm1
        shufps xmm5, xmm7, 11011101b

        movaps[eax+48], xmm5
    }
}

void transform(vec4_t* dst, const vec4_t* src, const mat4_t* mat_tr)
{

}

void concatenate(mat4_t* dst, const mat4_t* m0, const mat4_t* m1_tr)
{

}

void run(vec4_t* world_pts, const vec4_t* local_pts, const size_t count, const vec3_t* scale, const vec3_t* rotation, const vec3_t* translation)
{

}
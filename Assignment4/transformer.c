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

    while (number_of_points < count) {
        int ret = scanf("%f%f%f", &p_points->x, &p_points->y, &p_points->z);

        if (ret < 3) {
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
    __asm {
        mov eax, src
        mov edx, mat_tr
        xorps xmm3, xmm3

        movaps xmm0, [eax]
        movaps xmm1, [edx]
        dpps xmm0, xmm1, 11110001b
        orps xmm3, xmm0

        movaps xmm0, [eax]
        movaps xmm1, [edx+16]
        dpps xmm0, xmm1, 11110010b
        orps xmm3, xmm0

        movaps xmm0, [eax]
        movaps xmm1, [edx+32]
        dpps xmm0, xmm1, 11110100b
        orps xmm3, xmm0

        movaps xmm0, [eax]
        movaps xmm1, [edx+48]
        dpps xmm0, xmm1, 11111000b
        orps xmm3, xmm0

        mov eax, dst
        movaps [eax], xmm3
    }
}

void concatenate(mat4_t* dst, const mat4_t* m0, const mat4_t* m1_tr)
{
    __asm {
        mov esi, m0
        mov edi, m1_tr
        mov edx, dst
        mov ecx, 04h
        xor eax, eax
        
    loop_con:
        xorps xmm3, xmm3
        movaps xmm0, [esi+eax]

        movaps xmm1, xmm0
        movaps xmm2, [edi]
        dpps xmm1, xmm2, 11110001b
        orps xmm3, xmm1

        movaps xmm1, xmm0
        movaps xmm2, [edi+16]
        dpps xmm1, xmm2, 11110010b
        orps xmm3, xmm1

        movaps xmm1, xmm0
        movaps xmm2, [edi+32]
        dpps xmm1, xmm2, 11110100b
        orps xmm3, xmm1

        movaps xmm1, xmm0
        movaps xmm2, [edi+48]
        dpps xmm1, xmm2, 11111000b
        orps xmm3, xmm1

        movaps [edx+eax], xmm3

        add eax, 10h
        loop loop_con
    }
}

void run(vec4_t* world_pts, const vec4_t* local_pts, const size_t count, const vec3_t* scale, const vec3_t* rotation, const vec3_t* translation)
{
    mat4_t m_scale;
    mat4_t m_rotation_x;
    mat4_t m_rotation_y;
    mat4_t m_rotation_z;
    mat4_t m_translation;
    mat4_t temp1;
    mat4_t temp2;
    mat4_t temp3;
    mat4_t m_result;
    const vec4_t* p_local = local_pts;
    vec4_t* p_world = world_pts;

    // Get transform matrix
    mat_scale(&m_scale, scale->x, scale->y, scale->z);
    mat_rotation_x(&m_rotation_x, rotation->x);
    mat_rotation_y(&m_rotation_y, rotation->y);
    mat_rotation_z(&m_rotation_z, rotation->z);
    mat_translation(&m_translation, translation->x, translation->y, translation->z);

    // Matrix * Matrix
    transpose(&m_rotation_x);
    concatenate(&temp1, &m_scale, &m_rotation_x);

    transpose(&m_rotation_z);
    concatenate(&temp2, &m_rotation_y, &m_rotation_z);

    transpose(&temp2);
    concatenate(&temp3, &temp1, &temp2);

    transpose(&m_translation);
    concatenate(&m_result, &temp3, &m_translation);

    transpose(&m_result);

    for (size_t i = 0; i < count; ++i) {
        transform(p_world++, p_local++, &m_result);
    }
}
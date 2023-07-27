#include "transformer.h"

#include <stdio.h>

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

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
    }
}

void transpose(mat4_t* mat)
{

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
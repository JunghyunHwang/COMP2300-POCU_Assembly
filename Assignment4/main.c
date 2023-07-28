#include "transformer.h"
#include <assert.h>
#include <string.h>

#define ASSERT_MAT_EQUALS(expected, actual) assert(memcmp(expected, actual, sizeof(mat4_t)) == 0)
#define ASSERT_VEC_EQUALS(expected, actual) assert(memcmp(expected, actual, sizeof(vec4_t)) == 0)

int main(void)
{
    enum { MAX_POINTS = 512 };

    vec4_t points[MAX_POINTS];

    size_t count = read_points(points, MAX_POINTS);

    return 0;
}
#include "matrix.h"
#include "transformer.h"

#include <stdio.h>

int main(void)
{
	vec4_t points[512];

	size_t count = read_points(points, 512);

	return 0;
}

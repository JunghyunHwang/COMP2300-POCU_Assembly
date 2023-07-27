#include "matrix.h"
#include "transformer.h"

#include <stdio.h>

int main(void)
{
    mat4_t mat = {
    {  1.f, 2.f,   3.f, 0.f },
    {  5.f, 6.f,   7.f, 0.f },
    {  9.f, 10.f, 11.f, 0.f },
    { 13.f, 14.f, 15.f, 1.f },
    };

    transpose(&mat);

	return 0;
}

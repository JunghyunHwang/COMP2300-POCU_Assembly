#include <stdio.h>
#define ALIGN8 __declspec(align(8))

int main(void)
{
	ALIGN8 short v[2] = { 10, -10 };
	ALIGN8 int res[2];

	__asm {
		movq mm0,v
		movq mm7,mm0
		psraw mm7,15
		punpcklwd mm0,mm7

		movq res,mm0
		emms
	}

	return 0;
}
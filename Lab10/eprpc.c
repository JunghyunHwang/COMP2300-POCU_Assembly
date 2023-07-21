#include "eprpc.h"

void __declspec(naked) eprpc_init(void)
{
	__asm {
		finit
		ret
	}
}

void eprpc_load(const double num)
{
	__asm {
		fld num
	}
}

void eprpc_get_result(double* out_result)
{
	__asm {
		mov edx, [ebp+8]
		fst QWORD PTR [edx]
	}
}

void __declspec(naked) eprpc_add(void)
{
	__asm {
		fadd
		ret
	}
}

void __declspec(naked) eprpc_sub(void)
{
	__asm {
		fsub
		ret
	}
}

void __declspec(naked) eprpc_mul(void)
{
	__asm {
		fmul
		ret
	}
}

void __declspec(naked) eprpc_div(void)
{
	__asm {
		fdiv
		ret
	}
}

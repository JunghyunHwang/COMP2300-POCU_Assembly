#include <assert.h>
#include <stdio.h>

#include "calc.h"
#include "eprpc.h"

enum { NUM_DATA = 16 };

int main(void)
{
	double result;
	double operands[NUM_DATA];
	op_t ops[NUM_DATA];
	
	parse_rpn("2.34e-4 4.523e-3 3.2 0.002 * + /", ops, operands, NUM_DATA);

	calculate(ops, operands);
	eprpc_get_result(&result);

	assert(0.021422686075254049 == result);

	parse_rpn("3.2 5.7 8.1 9.0 - + 1.1 / *", ops, operands, NUM_DATA);

	calculate(ops, operands);
	eprpc_get_result(&result);

	assert(13.963636363636363 == result);

	return 0;
}

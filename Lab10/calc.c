#include <assert.h>
#include <stdlib.h>

#include "calc.h"
#include "eprpc.h"

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

void parse_rpn(const char* line, op_t* ops, double* operands, size_t count)
{
	const char* p_start = line;
	const char* p_end = line;

	op_t* p_ops = ops;
	double* p_operands = operands;

	while (TRUE) {
		double temp = strtold(p_start, &p_end);
		*p_operands++ = temp;

		switch (*p_end) {
		case '+':
			*p_ops++ = OP_ADD;
			++p_end;
			break;
		case '-':
			*p_ops++ = OP_SUB;
			++p_end;
			break;
		case '*':
			*p_ops++ = OP_MUL;
			++p_end;
			break;
		case '/':
			*p_ops++ = OP_DIV;
			++p_end;
			break;
		case ' ':
			*p_ops++ = OP_LOAD;
			break;
		default:
			assert(FALSE);
			break;
		}

		if (*p_end == '\0')
		{
			*p_ops++ = OP_END;
			break;
		}

		++p_end;
		p_start = p_end;
	}

	assert(p_ops - ops <= (int)count);
	assert(p_operands - operands <= (int)count);
}

void calculate(const op_t* op, const double* operands)
{
	op_t* p_ops = op;
	double* p_operands = operands;

	while (*p_ops != OP_END)
	{
		switch (*p_ops)
		{
		case OP_LOAD:
			eprpc_load(*p_operands);
			break;
		case OP_ADD:
			eprpc_add();
			break;
		case OP_SUB:
			eprpc_sub();
			break;
		case OP_MUL:
			eprpc_mul();
			break;
		case OP_DIV:
			eprpc_div();
			break;
		default:
			assert(FALSE);
			break;
		}

		++p_operands;
		++p_ops;
	}
}

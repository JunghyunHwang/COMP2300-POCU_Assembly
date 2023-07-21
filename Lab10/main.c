#include <assert.h>
#include <stdio.h>

#include "calc.h"
#include "eprpc.h"

enum { NUM_DATA = 16 };

static void buildbot_test(void)
{
    enum {
        NUM_DATA = 512
    };

    const double EPSILON = 0.000001;

    {
        double result;
        double operands[NUM_DATA] = { 0, };
        op_t ops[NUM_DATA] = { 0, };

        double expected_result = 266.0;
        double expected_operands[NUM_DATA] = { 1.0000000000000000, 2.0000000000000000, 0.0000000000000000, 3.0000000000000000, 0.0000000000000000, 4.0000000000000000, 0.0000000000000000, 5.0000000000000000, 0.0000000000000000, 6.0000000000000000, 0.0000000000000000, 7.0000000000000000, 0.0000000000000000, 8.0000000000000000, 0.0000000000000000, 9.0000000000000000, 0.0000000000000000, 10.000000000000000, 0.0000000000000000, 11.000000000000000, 0.0000000000000000, 12.000000000000000, 0.0000000000000000, 13.000000000000000, 0.0000000000000000, 14.000000000000000, 0.0000000000000000, 15.000000000000000, 0.0000000000000000, 16.000000000000000, };
        op_t expected_ops[NUM_DATA] = { OP_LOAD, OP_LOAD, OP_MUL, OP_LOAD, OP_SUB, OP_LOAD, OP_ADD, OP_LOAD, OP_DIV, OP_LOAD, OP_MUL, OP_LOAD, OP_MUL, OP_LOAD, OP_ADD, OP_LOAD, OP_SUB, OP_LOAD, OP_MUL, OP_LOAD, OP_DIV, OP_LOAD, OP_MUL, OP_LOAD, OP_SUB, OP_LOAD, OP_ADD, OP_LOAD, OP_SUB, OP_LOAD, OP_ADD, OP_END, };

        parse_rpn("1 2 * 3 - 4 + 5 / 6 * 7 * 8 + 9 - 10 * 11 / 12 * 13 - 14 + 15 - 16 +", ops, operands, NUM_DATA);

        assert(memcmp(operands, expected_operands, NUM_DATA) == 0); // string.h
        assert(memcmp(ops, expected_ops, NUM_DATA) == 0);

        calculate(ops, operands);
        eprpc_get_result(&result);

        assert(fabs(result - expected_result) <= EPSILON); // math.h
    }
}

int main(void)
{
    buildbot_test();
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

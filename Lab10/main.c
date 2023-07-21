#include "test.h"

int main(void)
{
    test_only_operand();
    test_official();
    buildbot_test();

    return 0;
}

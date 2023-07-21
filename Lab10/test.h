#ifndef TEST_H
#define TEST_H

#include <string.h>
#include <math.h>
#include <assert.h>

#include "calc.h"
#include "eprpc.h"

enum {
    NUM_DATA = 512
};

void test_official(void);
void buildbot_test(void);

#endif /* TEST_H*/
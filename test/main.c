#include "test_box.h"

int
main()
{    // @formatter:off
    enum test_status (*tests[])() = { // @formatter:on
            &test_box_suite
    };
    int n_tests = sizeof tests / sizeof tests[0];
    return run_tests(tests, n_tests);
}
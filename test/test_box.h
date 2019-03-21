

#ifndef NOISE_MAKER_TEST_BOX_H
#define NOISE_MAKER_TEST_BOX_H

#include <mn_test.h>
#include <vec.h>
#include <box.h>

enum test_status
test_box_contain_vec()
{
    struct vec2i point1;
    point1.x = 13;
    point1.y = 10;

    struct vec2i point2;
    point2.x = 0;
    point2.y = 0;

    struct vec2i point3;
    point3.x = -11;
    point3.y = -14;

    struct box box1;
    box1.left = 5;
    box1.bottom = 5;
    box_set_height(&box1, 10);
    box_set_width(&box1, 10);
    ASSERT_BOOL_EQUAL(true, box_contain_vec2i(&box1, &point1));
    ASSERT_BOOL_EQUAL(false, box_contain_vec2i(&box1, &point2));
    ASSERT_BOOL_EQUAL(false, box_contain_vec2i(&box1, &point3));

    struct box box2;
    box2.left = -15;
    box2.bottom = -25;
    box_set_height(&box2, 11);
    box_set_width(&box2, 13);
    ASSERT_BOOL_EQUAL(true, box_contain_vec2i(&box2, &point3));
    ASSERT_BOOL_EQUAL(false, box_contain_vec2i(&box2, &point1));
    ASSERT_BOOL_EQUAL(false, box_contain_vec2i(&box2, &point2));

    struct box box3;
    box3.left = -5;
    box3.bottom = -6;
    box_set_height(&box3, 10);
    box_set_width(&box3, 9);
    ASSERT_BOOL_EQUAL(true, box_contain_vec2i(&box3, &point2));
    ASSERT_BOOL_EQUAL(false, box_contain_vec2i(&box3, &point1));
    ASSERT_BOOL_EQUAL(false, box_contain_vec2i(&box3, &point3));
    return TEST_STATUS_SUCCESS;
}

enum test_status
test_box_suite()
{
    // @formatter:off
    enum test_status (*tests[])() = { // @formatter:on
            &test_box_contain_vec
    };
    int n_tests = sizeof tests / sizeof tests[0];
    return run_tests(tests, n_tests);
}

#endif //NOISE_MAKER_TEST_BOX_H

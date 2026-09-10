#include <unity.h>
#include "animation/AnimationType.h"

void test_animation_type_none_to_string()
{
    TEST_ASSERT_EQUAL_STRING(
        "none",
        animationTypeToString(AnimationType::None));
}

void test_animation_type_snake_to_string()
{
    TEST_ASSERT_EQUAL_STRING(
        "snake",
        animationTypeToString(AnimationType::Snake));
}

void test_animation_type_breathing_to_string()
{
    TEST_ASSERT_EQUAL_STRING(
        "breathing",
        animationTypeToString(AnimationType::Breathing));
}

void run_animation_type_tests()
{
    RUN_TEST(test_animation_type_none_to_string);
    RUN_TEST(test_animation_type_snake_to_string);
    RUN_TEST(test_animation_type_breathing_to_string);
}

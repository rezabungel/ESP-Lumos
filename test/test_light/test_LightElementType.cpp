#include <unity.h>
#include "LightElementType.h"

void test_light_element_type_house_to_string()
{
    TEST_ASSERT_EQUAL_STRING(
        "house",
        lightElementTypeToString(LightElementType::House));
}

void test_light_element_type_room_to_string()
{
    TEST_ASSERT_EQUAL_STRING(
        "room",
        lightElementTypeToString(LightElementType::Room));
}

void test_light_element_type_light_group_to_string()
{
    TEST_ASSERT_EQUAL_STRING(
        "lightGroup",
        lightElementTypeToString(LightElementType::LightGroup));
}

void test_light_element_type_strip_to_string()
{
    TEST_ASSERT_EQUAL_STRING(
        "strip",
        lightElementTypeToString(LightElementType::Strip));
}

void run_light_element_type_tests()
{
    RUN_TEST(test_light_element_type_house_to_string);
    RUN_TEST(test_light_element_type_room_to_string);
    RUN_TEST(test_light_element_type_light_group_to_string);
    RUN_TEST(test_light_element_type_strip_to_string);
}

#include <unity.h>
#include "Color.h"

void test_color_to_json()
{
    JsonBuilder json;
    Color color = {255, 128, 0};

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(color.toJson(json));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"color\":{\"r\":255,\"g\":128,\"b\":0}}",
        json.data());
}

void test_color_to_json_min_values()
{
    JsonBuilder json;
    Color color = {0, 0, 0};

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(color.toJson(json));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"color\":{\"r\":0,\"g\":0,\"b\":0}}",
        json.data());
}

void test_color_to_json_max_values()
{
    JsonBuilder json;
    Color color = {255, 255, 255};

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(color.toJson(json));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"color\":{\"r\":255,\"g\":255,\"b\":255}}",
        json.data());
}

void run_color_tests()
{
    RUN_TEST(test_color_to_json);
    RUN_TEST(test_color_to_json_min_values);
    RUN_TEST(test_color_to_json_max_values);
}

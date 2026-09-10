#include <unity.h>
#include "animation/AnimationState.h"

void test_animation_state_none_to_json()
{
    JsonBuilder json;
    AnimationState state = {
        AnimationType::None,
        {}};

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(state.toJson(json));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"animation\":{\"type\":\"none\",\"parameters\":{}}}",
        json.data());
}

void test_animation_state_snake_to_json()
{
    JsonBuilder json;
    AnimationState state = {
        AnimationType::Snake,
        {.snake = {
             .speed = 50,
             .length = 10}}};

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(state.toJson(json));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"animation\":{\"type\":\"snake\",\"parameters\":{\"speed\":50,\"length\":10}}}",
        json.data());
}

void test_animation_state_breathing_to_json()
{
    JsonBuilder json;
    AnimationState state = {
        AnimationType::Breathing,
        {.breathing = {
             .speed = 100,
             .minBrightness = 20,
             .maxBrightness = 200}}};

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(state.toJson(json));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"animation\":{\"type\":\"breathing\",\"parameters\":{\"speed\":100,\"minBrightness\":20,\"maxBrightness\":200}}}",
        json.data());
}

void run_animation_state_tests()
{
    RUN_TEST(test_animation_state_none_to_json);
    RUN_TEST(test_animation_state_snake_to_json);
    RUN_TEST(test_animation_state_breathing_to_json);
}

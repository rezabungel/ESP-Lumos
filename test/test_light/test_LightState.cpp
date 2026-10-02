#include <unity.h>
#include "LightState.h"

void test_light_state_default_to_json()
{
    JsonBuilder json;
    LightState state;

    TEST_ASSERT_TRUE(state.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}",
        json.data());
}

void test_light_state_enabled_to_json()
{
    JsonBuilder json;

    LightState state;
    state.enabled = true;
    state.color = {255, 128, 0};
    state.brightness = 128;
    state.animation.type = AnimationType::None;
    state.animation.parameters = {};

    TEST_ASSERT_TRUE(state.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"enabled\":true,\"color\":{\"r\":255,\"g\":128,\"b\":0},\"brightness\":128,\"animation\":{\"type\":\"none\",\"parameters\":{}}}",
        json.data());
}

void test_light_state_snake_animation_to_json()
{
    JsonBuilder json;

    LightState state;
    state.enabled = true;
    state.color = {0, 255, 0};
    state.brightness = 200;
    state.animation.type = AnimationType::Snake;
    state.animation.parameters.snake.speed = 50;
    state.animation.parameters.snake.length = 10;

    TEST_ASSERT_TRUE(state.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"enabled\":true,\"color\":{\"r\":0,\"g\":255,\"b\":0},\"brightness\":200,\"animation\":{\"type\":\"snake\",\"parameters\":{\"speed\":50,\"length\":10}}}",
        json.data());
}

void test_light_state_breathing_animation_to_json()
{
    JsonBuilder json;

    LightState state;
    state.enabled = true;
    state.color = {0, 0, 255};
    state.brightness = 180;
    state.animation.type = AnimationType::Breathing;
    state.animation.parameters.breathing.speed = 100;
    state.animation.parameters.breathing.minBrightness = 20;
    state.animation.parameters.breathing.maxBrightness = 200;

    TEST_ASSERT_TRUE(state.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"enabled\":true,\"color\":{\"r\":0,\"g\":0,\"b\":255},\"brightness\":180,\"animation\":{\"type\":\"breathing\",\"parameters\":{\"speed\":100,\"minBrightness\":20,\"maxBrightness\":200}}}",
        json.data());
}

void run_light_state_tests()
{
    RUN_TEST(test_light_state_default_to_json);
    RUN_TEST(test_light_state_enabled_to_json);
    RUN_TEST(test_light_state_snake_animation_to_json);
    RUN_TEST(test_light_state_breathing_animation_to_json);
}

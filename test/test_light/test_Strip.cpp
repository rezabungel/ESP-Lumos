#include <unity.h>
#include "Strip.h"

void test_strip_to_json_default_state()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    JsonBuilder json;

    TEST_ASSERT_TRUE(strip.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"strip1\",\"name\":\"Living room strip\",\"type\":\"strip\",\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}",
        json.data());
}

void test_strip_to_json_with_light_state()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    LightState state = {
        .enabled = true,
        .color = {255, 128, 0},
        .brightness = 128,
        .animation = {
            .type = AnimationType::None,
            .parameters = {}}};

    strip.setLightState(state);

    JsonBuilder json;

    TEST_ASSERT_TRUE(strip.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"strip1\",\"name\":\"Living room strip\",\"type\":\"strip\",\"state\":{\"enabled\":true,\"color\":{\"r\":255,\"g\":128,\"b\":0},\"brightness\":128,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}",
        json.data());
}

void test_strip_to_json_with_snake_animation()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    LightState state = {
        .enabled = true,
        .color = {0, 255, 0},
        .brightness = 200,
        .animation = {
            .type = AnimationType::Snake,
            .parameters = {
                .snake = {
                    .speed = 50,
                    .length = 5}}}};

    strip.setLightState(state);

    JsonBuilder json;

    TEST_ASSERT_TRUE(strip.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"strip1\",\"name\":\"Living room strip\",\"type\":\"strip\",\"state\":{\"enabled\":true,\"color\":{\"r\":0,\"g\":255,\"b\":0},\"brightness\":200,\"animation\":{\"type\":\"snake\",\"parameters\":{\"speed\":50,\"length\":5}}}}",
        json.data());
}

void run_strip_tests()
{
    RUN_TEST(test_strip_to_json_default_state);
    RUN_TEST(test_strip_to_json_with_light_state);
    RUN_TEST(test_strip_to_json_with_snake_animation);
}

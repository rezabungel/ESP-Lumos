#include <unity.h>
#include <FastLED.h>
#include "Strip.h"

void assert_color_equal(const CRGB &expected, const CRGB &actual)
{
    TEST_ASSERT_EQUAL_UINT8(expected.r, actual.r);
    TEST_ASSERT_EQUAL_UINT8(expected.g, actual.g);
    TEST_ASSERT_EQUAL_UINT8(expected.b, actual.b);
}

void test_strip_size_and_data()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    TEST_ASSERT_EQUAL_UINT16(10, strip.size());
    TEST_ASSERT_NOT_NULL(strip.data());

    for (uint16_t i = 0; i < strip.size(); ++i)
    {
        assert_color_equal(CRGB::Black, strip.data()[i]);
    }
}

void test_strip_get_id_and_name()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    TEST_ASSERT_EQUAL_STRING("strip1", strip.getId());
    TEST_ASSERT_EQUAL_STRING("Living room strip", strip.getName());
}

void test_strip_get_type()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    TEST_ASSERT_EQUAL(
        LightElementType::Strip,
        strip.getType());
}

void test_strip_set_light_state()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    LightState state;
    state.enabled = true;
    state.color = {255, 100, 50};
    state.brightness = 128;

    state.animation.type = AnimationType::Snake;
    state.animation.parameters.snake.speed = 50;
    state.animation.parameters.snake.length = 3;

    strip.setLightState(state);

    TEST_ASSERT_TRUE(strip.getLightState().enabled);

    TEST_ASSERT_EQUAL_UINT8(
        255,
        strip.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(
        100,
        strip.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(
        50,
        strip.getLightState().color.b);

    TEST_ASSERT_EQUAL_UINT8(
        128,
        strip.getLightState().brightness);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip.getLightState().animation.type);

    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip.getLightState().animation.parameters.snake.speed);

    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip.getLightState().animation.parameters.snake.length);
}

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

    LightState state;
    state.enabled = true;
    state.color = {255, 128, 0};
    state.brightness = 128;
    state.animation.type = AnimationType::None;
    state.animation.parameters = {};

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

    LightState state;
    state.enabled = true;
    state.color = {255, 128, 0};
    state.brightness = 200;
    state.animation.type = AnimationType::Snake;
    state.animation.parameters.snake.speed = 50;
    state.animation.parameters.snake.length = 5;

    strip.setLightState(state);

    JsonBuilder json;

    TEST_ASSERT_TRUE(strip.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"strip1\",\"name\":\"Living room strip\",\"type\":\"strip\",\"state\":{\"enabled\":true,\"color\":{\"r\":255,\"g\":128,\"b\":0},\"brightness\":200,\"animation\":{\"type\":\"snake\",\"parameters\":{\"speed\":50,\"length\":5}}}}",
        json.data());
}

void test_strip_on()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    strip.off();
    strip.on();

    TEST_ASSERT_TRUE(strip.getLightState().enabled);
}

void test_strip_off()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    strip.on();
    strip.off();

    TEST_ASSERT_FALSE(strip.getLightState().enabled);
}

void test_strip_set_color()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    Color color = {10, 20, 30};

    strip.setColor(color);

    TEST_ASSERT_EQUAL_UINT8(10, strip.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, strip.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, strip.getLightState().color.b);
}

void test_strip_set_brightness()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    strip.setBrightness(123);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        strip.getLightState().brightness);
}

void test_strip_set_animation_state()
{
    Strip<46> strip("strip1", "Living room strip", 10);

    AnimationState animationState;
    animationState.type = AnimationType::Snake;
    animationState.parameters.snake.speed = 50;
    animationState.parameters.snake.length = 3;

    strip.setAnimationState(animationState);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip.getLightState().animation.type);

    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip.getLightState().animation.parameters.snake.speed);

    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip.getLightState().animation.parameters.snake.length);
}

void test_strip_render_sets_static_color()
{
    const uint16_t stripLength = 10;
    Strip<46> strip("strip1", "Living room strip", stripLength);

    LightState state;
    state.enabled = true;
    state.color = {255, 128, 64};
    state.brightness = 255;
    state.animation.type = AnimationType::None;
    state.animation.parameters = {};

    const CRGB expectedColor(255, 128, 64);
    const uint32_t now = 1;

    strip.setLightState(state);

    TEST_ASSERT_TRUE(strip.render(now));

    for (uint16_t i = 0; i < stripLength; ++i)
    {
        assert_color_equal(expectedColor, strip.data()[i]);
    }
}

void test_strip_render_turns_off_disabled_strip()
{
    const uint16_t stripLength = 10;
    Strip<46> strip("strip1", "Living room strip", stripLength);

    LightState state;
    state.enabled = false;
    state.color = {255, 128, 64};
    state.brightness = 255;
    state.animation.type = AnimationType::None;
    state.animation.parameters = {};

    const uint32_t now = 1;

    strip.setLightState(state);

    TEST_ASSERT_TRUE(strip.render(now));

    for (uint16_t i = 0; i < stripLength; ++i)
    {
        assert_color_equal(CRGB::Black, strip.data()[i]);
    }
}

void test_strip_render_returns_false_when_nothing_changed()
{
    const uint16_t stripLength = 10;
    Strip<46> strip("strip1", "Living room strip", stripLength);

    LightState state;
    state.enabled = true;
    state.color = {255, 128, 64};
    state.brightness = 255;
    state.animation.type = AnimationType::None;
    state.animation.parameters = {};

    const uint32_t now = 1;

    strip.setLightState(state);

    TEST_ASSERT_TRUE(strip.render(now));
    TEST_ASSERT_FALSE(strip.render(now));
}

void test_strip_render_steps_animation()
{
    const uint16_t stripLength = 10;
    Strip<46> strip("strip1", "Living room strip", stripLength);

    LightState state;
    state.enabled = true;
    state.color = {255, 128, 64};
    state.brightness = 255;
    state.animation.type = AnimationType::Snake;
    state.animation.parameters.snake.speed = 50;
    state.animation.parameters.snake.length = 3;

    const CRGB expectedColor(255, 128, 64);

    const uint32_t beforeAnimationUpdate =
        state.animation.parameters.snake.speed - 1;
    const uint32_t firstAnimationUpdate =
        state.animation.parameters.snake.speed;
    const uint32_t beforeNextAnimationUpdate =
        firstAnimationUpdate + state.animation.parameters.snake.speed - 1;
    const uint32_t secondAnimationUpdate =
        state.animation.parameters.snake.speed * 2;

    strip.setLightState(state);

    TEST_ASSERT_FALSE(strip.render(beforeAnimationUpdate));

    for (uint16_t i = 0; i < stripLength; ++i)
    {
        assert_color_equal(CRGB::Black, strip.data()[i]);
    }

    TEST_ASSERT_TRUE(strip.render(firstAnimationUpdate));

    assert_color_equal(expectedColor, strip.data()[0]);
    assert_color_equal(expectedColor, strip.data()[1]);
    assert_color_equal(expectedColor, strip.data()[2]);

    for (uint16_t i = 3; i < stripLength; ++i)
    {
        assert_color_equal(CRGB::Black, strip.data()[i]);
    }

    TEST_ASSERT_FALSE(strip.render(beforeNextAnimationUpdate));

    assert_color_equal(expectedColor, strip.data()[0]);
    assert_color_equal(expectedColor, strip.data()[1]);
    assert_color_equal(expectedColor, strip.data()[2]);

    for (uint16_t i = 3; i < stripLength; ++i)
    {
        assert_color_equal(CRGB::Black, strip.data()[i]);
    }

    TEST_ASSERT_TRUE(strip.render(secondAnimationUpdate));

    assert_color_equal(CRGB::Black, strip.data()[0]);
    assert_color_equal(expectedColor, strip.data()[1]);
    assert_color_equal(expectedColor, strip.data()[2]);
    assert_color_equal(expectedColor, strip.data()[3]);

    for (uint16_t i = 4; i < stripLength; ++i)
    {
        assert_color_equal(CRGB::Black, strip.data()[i]);
    }
}

void run_strip_tests()
{
    RUN_TEST(test_strip_size_and_data);
    RUN_TEST(test_strip_get_id_and_name);
    RUN_TEST(test_strip_get_type);
    RUN_TEST(test_strip_set_light_state);
    RUN_TEST(test_strip_to_json_default_state);
    RUN_TEST(test_strip_to_json_with_light_state);
    RUN_TEST(test_strip_to_json_with_snake_animation);
    RUN_TEST(test_strip_on);
    RUN_TEST(test_strip_off);
    RUN_TEST(test_strip_set_color);
    RUN_TEST(test_strip_set_brightness);
    RUN_TEST(test_strip_set_animation_state);
    RUN_TEST(test_strip_render_sets_static_color);
    RUN_TEST(test_strip_render_turns_off_disabled_strip);
    RUN_TEST(test_strip_render_returns_false_when_nothing_changed);
    RUN_TEST(test_strip_render_steps_animation);
}

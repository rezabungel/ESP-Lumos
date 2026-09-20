#include <unity.h>
#include <FastLED.h>
#include "animation/snake/SnakeAnimation.h"

void assert_color_equal(const CRGB &expected, const CRGB &actual)
{
    TEST_ASSERT_EQUAL_UINT8(expected.r, actual.r);
    TEST_ASSERT_EQUAL_UINT8(expected.g, actual.g);
    TEST_ASSERT_EQUAL_UINT8(expected.b, actual.b);
}

void test_snake_animation_does_not_update_before_first_step()
{
    SnakeParameters parameters;
    parameters.speed = 50;
    parameters.length = 3;
    SnakeAnimation animation(parameters);

    const uint16_t stripLength = 5;
    CRGB leds[stripLength];
    fill_solid(leds, stripLength, CRGB::Black);

    const uint32_t beforeAnimationUpdate = parameters.speed - 1;

    LightState state;
    state.color = {255, 100, 50};

    TEST_ASSERT_FALSE(
        animation.step(
            state,
            leds,
            stripLength,
            beforeAnimationUpdate));

    for (uint8_t i = 0; i < stripLength; ++i)
    {
        assert_color_equal(CRGB::Black, leds[i]);
    }
}

void test_snake_animation_starts_with_configured_length_and_color()
{
    SnakeParameters parameters;
    parameters.speed = 50;
    parameters.length = 3;
    SnakeAnimation animation(parameters);

    const uint16_t stripLength = 5;
    CRGB leds[stripLength];
    fill_solid(leds, stripLength, CRGB::Black);

    const uint32_t animationUpdateTime = parameters.speed;

    LightState state;
    state.color = {255, 100, 50};

    const CRGB expectedColor(255, 100, 50);

    TEST_ASSERT_TRUE(
        animation.step(
            state,
            leds,
            stripLength,
            animationUpdateTime));

    assert_color_equal(expectedColor, leds[0]);
    assert_color_equal(expectedColor, leds[1]);
    assert_color_equal(expectedColor, leds[2]);
    assert_color_equal(CRGB::Black, leds[3]);
    assert_color_equal(CRGB::Black, leds[4]);
}

void test_snake_animation_does_not_update_before_next_step()
{
    SnakeParameters parameters;
    parameters.speed = 50;
    parameters.length = 3;
    SnakeAnimation animation(parameters);

    const uint16_t stripLength = 5;
    CRGB leds[stripLength];
    fill_solid(leds, stripLength, CRGB::Black);

    const uint32_t firstAnimationUpdate = parameters.speed;
    const uint32_t beforeNextAnimationUpdate =
        firstAnimationUpdate + parameters.speed - 1;
    const uint32_t nextAnimationUpdate =
        firstAnimationUpdate + parameters.speed;

    LightState state;
    state.color = {255, 100, 50};

    const CRGB expectedColor(255, 100, 50);

    TEST_ASSERT_TRUE(
        animation.step(
            state,
            leds,
            stripLength,
            firstAnimationUpdate));

    assert_color_equal(expectedColor, leds[0]);
    assert_color_equal(expectedColor, leds[1]);
    assert_color_equal(expectedColor, leds[2]);
    assert_color_equal(CRGB::Black, leds[3]);
    assert_color_equal(CRGB::Black, leds[4]);

    TEST_ASSERT_FALSE(
        animation.step(
            state,
            leds,
            stripLength,
            beforeNextAnimationUpdate));

    assert_color_equal(expectedColor, leds[0]);
    assert_color_equal(expectedColor, leds[1]);
    assert_color_equal(expectedColor, leds[2]);
    assert_color_equal(CRGB::Black, leds[3]);
    assert_color_equal(CRGB::Black, leds[4]);

    TEST_ASSERT_TRUE(
        animation.step(
            state,
            leds,
            stripLength,
            nextAnimationUpdate));

    assert_color_equal(CRGB::Black, leds[0]);
    assert_color_equal(expectedColor, leds[1]);
    assert_color_equal(expectedColor, leds[2]);
    assert_color_equal(expectedColor, leds[3]);
    assert_color_equal(CRGB::Black, leds[4]);
}

void test_snake_animation_moves_and_wraps_around_strip()
{
    SnakeParameters parameters;
    parameters.speed = 50;
    parameters.length = 3;
    SnakeAnimation animation(parameters);

    const uint16_t stripLength = 5;
    CRGB leds[stripLength];
    fill_solid(leds, stripLength, CRGB::Black);

    const uint32_t firstAnimationUpdate = parameters.speed;
    const uint32_t secondAnimationUpdate = parameters.speed * 2;
    const uint32_t thirdAnimationUpdate = parameters.speed * 3;
    const uint32_t fourthAnimationUpdate = parameters.speed * 4;

    LightState state;
    state.color = {255, 100, 50};

    const CRGB expectedColor(255, 100, 50);

    // First step: [C][C][C][ ][ ]
    TEST_ASSERT_TRUE(
        animation.step(
            state,
            leds,
            stripLength,
            firstAnimationUpdate));

    assert_color_equal(expectedColor, leds[0]);
    assert_color_equal(expectedColor, leds[1]);
    assert_color_equal(expectedColor, leds[2]);
    assert_color_equal(CRGB::Black, leds[3]);
    assert_color_equal(CRGB::Black, leds[4]);

    // Second step: [ ][C][C][C][ ]
    TEST_ASSERT_TRUE(
        animation.step(
            state,
            leds,
            stripLength,
            secondAnimationUpdate));

    assert_color_equal(CRGB::Black, leds[0]);
    assert_color_equal(expectedColor, leds[1]);
    assert_color_equal(expectedColor, leds[2]);
    assert_color_equal(expectedColor, leds[3]);
    assert_color_equal(CRGB::Black, leds[4]);

    // Third step: [ ][ ][C][C][C]
    TEST_ASSERT_TRUE(
        animation.step(
            state,
            leds,
            stripLength,
            thirdAnimationUpdate));

    assert_color_equal(CRGB::Black, leds[0]);
    assert_color_equal(CRGB::Black, leds[1]);
    assert_color_equal(expectedColor, leds[2]);
    assert_color_equal(expectedColor, leds[3]);
    assert_color_equal(expectedColor, leds[4]);

    // Fourth step: [C][ ][ ][C][C]
    TEST_ASSERT_TRUE(
        animation.step(
            state,
            leds,
            stripLength,
            fourthAnimationUpdate));

    assert_color_equal(expectedColor, leds[0]);
    assert_color_equal(CRGB::Black, leds[1]);
    assert_color_equal(CRGB::Black, leds[2]);
    assert_color_equal(expectedColor, leds[3]);
    assert_color_equal(expectedColor, leds[4]);
}

void run_snake_animation_tests()
{
    RUN_TEST(test_snake_animation_does_not_update_before_first_step);
    RUN_TEST(test_snake_animation_starts_with_configured_length_and_color);
    RUN_TEST(test_snake_animation_does_not_update_before_next_step);
    RUN_TEST(test_snake_animation_moves_and_wraps_around_strip);
}

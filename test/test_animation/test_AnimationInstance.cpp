#include <unity.h>
#include <FastLED.h>
#include "animation/AnimationInstance.h"

void test_animation_instance_starts_without_animation()
{
    AnimationInstance animationInstance;

    TEST_ASSERT_EQUAL(
        AnimationType::None,
        animationInstance.getAnimationType());

    const uint16_t stripLength = 5;
    CRGB leds[stripLength];
    LightState lightState;

    const uint32_t now = 1;

    TEST_ASSERT_FALSE(
        animationInstance.step(
            lightState,
            leds,
            stripLength,
            now));
}

void test_animation_instance_sets_none_animation()
{
    AnimationInstance animationInstance;

    AnimationState animationState;
    animationState.type = AnimationType::None;

    TEST_ASSERT_TRUE(
        animationInstance.setAnimationState(animationState));

    TEST_ASSERT_EQUAL(
        AnimationType::None,
        animationInstance.getAnimationType());
}

void test_animation_instance_sets_snake_animation()
{
    AnimationInstance animationInstance;

    AnimationState animationState;
    animationState.type = AnimationType::Snake;
    animationState.parameters.snake.speed = 50;
    animationState.parameters.snake.length = 3;

    TEST_ASSERT_TRUE(
        animationInstance.setAnimationState(animationState));

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        animationInstance.getAnimationType());
}

void test_animation_instance_sets_breathing_animation()
{
    AnimationInstance animationInstance;

    AnimationState animationState;
    animationState.type = AnimationType::Breathing;
    animationState.parameters.breathing.speed = 50;
    animationState.parameters.breathing.minBrightness = 0;
    animationState.parameters.breathing.maxBrightness = 255;

    TEST_ASSERT_TRUE(
        animationInstance.setAnimationState(animationState));

    TEST_ASSERT_EQUAL(
        AnimationType::Breathing,
        animationInstance.getAnimationType());
}

void test_animation_instance_replaces_current_animation()
{
    AnimationInstance animationInstance;

    AnimationState snakeState;
    snakeState.type = AnimationType::Snake;
    snakeState.parameters.snake.speed = 50;
    snakeState.parameters.snake.length = 3;

    TEST_ASSERT_TRUE(
        animationInstance.setAnimationState(snakeState));

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        animationInstance.getAnimationType());

    AnimationState breathingState;
    breathingState.type = AnimationType::Breathing;
    breathingState.parameters.breathing.speed = 50;
    breathingState.parameters.breathing.minBrightness = 0;
    breathingState.parameters.breathing.maxBrightness = 255;

    TEST_ASSERT_TRUE(
        animationInstance.setAnimationState(breathingState));

    TEST_ASSERT_EQUAL(
        AnimationType::Breathing,
        animationInstance.getAnimationType());
}

void test_animation_instance_resets_animation()
{
    AnimationInstance animationInstance;

    AnimationState animationState;
    animationState.type = AnimationType::Snake;
    animationState.parameters.snake.speed = 50;
    animationState.parameters.snake.length = 3;

    TEST_ASSERT_TRUE(
        animationInstance.setAnimationState(animationState));

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        animationInstance.getAnimationType());

    animationInstance.resetAnimation();

    TEST_ASSERT_EQUAL(
        AnimationType::None,
        animationInstance.getAnimationType());

    const uint16_t stripLength = 5;
    CRGB leds[stripLength];
    LightState lightState;

    const uint32_t now = 1;

    TEST_ASSERT_FALSE(
        animationInstance.step(
            lightState,
            leds,
            stripLength,
            now));
}

void test_animation_instance_reset_handles_no_animation()
{
    AnimationInstance animationInstance;

    TEST_ASSERT_EQUAL(
        AnimationType::None,
        animationInstance.getAnimationType());

    animationInstance.resetAnimation();

    TEST_ASSERT_EQUAL(
        AnimationType::None,
        animationInstance.getAnimationType());
}

void test_animation_instance_steps_current_animation()
{
    AnimationInstance animationInstance;

    AnimationState animationState;
    animationState.type = AnimationType::Snake;
    animationState.parameters.snake.speed = 50;
    animationState.parameters.snake.length = 3;

    TEST_ASSERT_TRUE(
        animationInstance.setAnimationState(animationState));

    const uint16_t stripLength = 5;
    CRGB leds[stripLength];
    LightState lightState;

    const uint32_t animationUpdateTime =
        animationState.parameters.snake.speed;

    TEST_ASSERT_TRUE(
        animationInstance.step(
            lightState,
            leds,
            stripLength,
            animationUpdateTime));
}

void run_animation_instance_tests()
{
    RUN_TEST(test_animation_instance_starts_without_animation);
    RUN_TEST(test_animation_instance_sets_none_animation);
    RUN_TEST(test_animation_instance_sets_snake_animation);
    RUN_TEST(test_animation_instance_sets_breathing_animation);
    RUN_TEST(test_animation_instance_replaces_current_animation);
    RUN_TEST(test_animation_instance_resets_animation);
    RUN_TEST(test_animation_instance_reset_handles_no_animation);
    RUN_TEST(test_animation_instance_steps_current_animation);
}

#include <unity.h>
#include "animation/AnimationFactory.h"
#include "animation/snake/SnakeAnimation.h"
#include "animation/breathing/BreathingAnimation.h"

void test_animation_factory_returns_null_for_none()
{
    AnimationStorage storage;

    AnimationState state;
    state.type = AnimationType::None;

    Animation *animation =
        AnimationFactory::create(storage, state);

    TEST_ASSERT_NULL(animation);
}

void test_animation_factory_creates_and_destroys_snake_animation()
{
    AnimationStorage storage;

    AnimationState state;
    state.type = AnimationType::Snake;
    state.parameters.snake.speed = 50;
    state.parameters.snake.length = 3;

    Animation *animation =
        AnimationFactory::create(storage, state);

    TEST_ASSERT_NOT_NULL(animation);

    SnakeAnimation *snakeAnimation =
        dynamic_cast<SnakeAnimation *>(animation);

    TEST_ASSERT_NOT_NULL(snakeAnimation);

    AnimationFactory::destroy(animation, state.type);
}

void test_animation_factory_creates_and_destroys_breathing_animation()
{
    AnimationStorage storage;

    AnimationState state;
    state.type = AnimationType::Breathing;
    state.parameters.breathing.speed = 50;
    state.parameters.breathing.minBrightness = 0;
    state.parameters.breathing.maxBrightness = 255;

    Animation *animation =
        AnimationFactory::create(storage, state);

    TEST_ASSERT_NOT_NULL(animation);

    BreathingAnimation *breathingAnimation =
        dynamic_cast<BreathingAnimation *>(animation);

    TEST_ASSERT_NOT_NULL(breathingAnimation);

    AnimationFactory::destroy(animation, state.type);
}

void test_animation_factory_destroy_handles_null()
{
    AnimationFactory::destroy(nullptr, AnimationType::None);
}

void run_animation_factory_tests()
{
    RUN_TEST(test_animation_factory_returns_null_for_none);
    RUN_TEST(test_animation_factory_creates_and_destroys_snake_animation);
    RUN_TEST(test_animation_factory_creates_and_destroys_breathing_animation);
    RUN_TEST(test_animation_factory_destroy_handles_null);
}

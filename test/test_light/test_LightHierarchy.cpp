#include <unity.h>
#include "House.h"
#include "Room.h"
#include "LightGroup.h"
#include "Strip.h"

struct LightHierarchyFixture
{
    House house{"house", "House"};

    Room roomA{"roomA", "Room A"};
    Room roomB{"roomB", "Room B"};

    LightGroup groupA{"groupA", "Group A"};
    LightGroup groupC{"groupC", "Group C"};

    Strip<46> stripA1{"stripA1", "Strip A1", 10};
    Strip<48> stripA2{"stripA2", "Strip A2", 10};
    Strip<50> stripB1{"stripB1", "Strip B1", 10};
    Strip<52> stripC1{"stripC1", "Strip C1", 10};
    Strip<54> stripD{"stripD", "Strip D", 10};

    LightHierarchyFixture()
    {
        groupA.addElement(&stripA1);
        groupA.addElement(&stripA2);

        roomA.addElement(&groupA);
        roomB.addElement(&stripB1);

        groupC.addElement(&stripC1);

        house.addElement(&roomA);
        house.addElement(&roomB);
        house.addElement(&groupC);
        house.addElement(&stripD);
    }
};

void test_light_hierarchy_set_light_state()
{
    LightHierarchyFixture hierarchy;

    LightState state;
    state.enabled = true;
    state.color = {255, 100, 50};
    state.brightness = 128;

    state.animation.type = AnimationType::Snake;
    state.animation.parameters.snake.speed = 50;
    state.animation.parameters.snake.length = 3;

    hierarchy.house.setLightState(state);

    TEST_ASSERT_TRUE(hierarchy.stripA1.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, hierarchy.stripA1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, hierarchy.stripA1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, hierarchy.stripA1.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, hierarchy.stripA1.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripA1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripA1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripA1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_TRUE(hierarchy.stripA2.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, hierarchy.stripA2.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, hierarchy.stripA2.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, hierarchy.stripA2.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, hierarchy.stripA2.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripA2.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripA2.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripA2.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_TRUE(hierarchy.stripB1.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, hierarchy.stripB1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, hierarchy.stripB1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, hierarchy.stripB1.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, hierarchy.stripB1.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripB1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripB1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripB1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_TRUE(hierarchy.stripC1.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, hierarchy.stripC1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, hierarchy.stripC1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, hierarchy.stripC1.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, hierarchy.stripC1.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripC1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripC1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripC1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_TRUE(hierarchy.stripD.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, hierarchy.stripD.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, hierarchy.stripD.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, hierarchy.stripD.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, hierarchy.stripD.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripD.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripD.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripD.getLightState().animation.parameters.snake.length);
}

void test_light_hierarchy_on()
{
    LightHierarchyFixture hierarchy;

    hierarchy.stripA1.off();
    hierarchy.stripA2.off();
    hierarchy.stripB1.off();
    hierarchy.stripC1.off();
    hierarchy.stripD.off();

    hierarchy.house.on();

    TEST_ASSERT_TRUE(hierarchy.stripA1.getLightState().enabled);
    TEST_ASSERT_TRUE(hierarchy.stripA2.getLightState().enabled);
    TEST_ASSERT_TRUE(hierarchy.stripB1.getLightState().enabled);
    TEST_ASSERT_TRUE(hierarchy.stripC1.getLightState().enabled);
    TEST_ASSERT_TRUE(hierarchy.stripD.getLightState().enabled);
}

void test_light_hierarchy_off()
{
    LightHierarchyFixture hierarchy;

    hierarchy.stripA1.on();
    hierarchy.stripA2.on();
    hierarchy.stripB1.on();
    hierarchy.stripC1.on();
    hierarchy.stripD.on();

    hierarchy.house.off();

    TEST_ASSERT_FALSE(hierarchy.stripA1.getLightState().enabled);
    TEST_ASSERT_FALSE(hierarchy.stripA2.getLightState().enabled);
    TEST_ASSERT_FALSE(hierarchy.stripB1.getLightState().enabled);
    TEST_ASSERT_FALSE(hierarchy.stripC1.getLightState().enabled);
    TEST_ASSERT_FALSE(hierarchy.stripD.getLightState().enabled);
}

void test_light_hierarchy_set_color()
{
    LightHierarchyFixture hierarchy;

    Color color = {10, 20, 30};

    hierarchy.house.setColor(color);

    TEST_ASSERT_EQUAL_UINT8(10, hierarchy.stripA1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, hierarchy.stripA1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, hierarchy.stripA1.getLightState().color.b);

    TEST_ASSERT_EQUAL_UINT8(10, hierarchy.stripA2.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, hierarchy.stripA2.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, hierarchy.stripA2.getLightState().color.b);

    TEST_ASSERT_EQUAL_UINT8(10, hierarchy.stripB1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, hierarchy.stripB1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, hierarchy.stripB1.getLightState().color.b);

    TEST_ASSERT_EQUAL_UINT8(10, hierarchy.stripC1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, hierarchy.stripC1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, hierarchy.stripC1.getLightState().color.b);

    TEST_ASSERT_EQUAL_UINT8(10, hierarchy.stripD.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, hierarchy.stripD.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, hierarchy.stripD.getLightState().color.b);
}

void test_light_hierarchy_set_brightness()
{
    LightHierarchyFixture hierarchy;

    hierarchy.house.setBrightness(123);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        hierarchy.stripA1.getLightState().brightness);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        hierarchy.stripA2.getLightState().brightness);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        hierarchy.stripB1.getLightState().brightness);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        hierarchy.stripC1.getLightState().brightness);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        hierarchy.stripD.getLightState().brightness);
}

void test_light_hierarchy_set_animation_state()
{
    LightHierarchyFixture hierarchy;

    AnimationState animationState;
    animationState.type = AnimationType::Snake;
    animationState.parameters.snake.speed = 50;
    animationState.parameters.snake.length = 3;

    hierarchy.house.setAnimationState(animationState);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripA1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripA1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripA1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripA2.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripA2.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripA2.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripB1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripB1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripB1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripC1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripC1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripC1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        hierarchy.stripD.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        hierarchy.stripD.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        hierarchy.stripD.getLightState().animation.parameters.snake.length);
}

void run_light_hierarchy_tests()
{
    RUN_TEST(test_light_hierarchy_set_light_state);
    RUN_TEST(test_light_hierarchy_on);
    RUN_TEST(test_light_hierarchy_off);
    RUN_TEST(test_light_hierarchy_set_color);
    RUN_TEST(test_light_hierarchy_set_brightness);
    RUN_TEST(test_light_hierarchy_set_animation_state);
}

#include <unity.h>
#include "LightGroup.h"
#include "Strip.h"

void test_light_container_get_id_and_name()
{
    LightGroup group("group1", "Living room group");

    TEST_ASSERT_EQUAL_STRING("group1", group.getId());
    TEST_ASSERT_EQUAL_STRING("Living room group", group.getName());
}

void test_light_container_add_element()
{
    LightGroup group("group1", "group1");
    Strip<46> strip("strip1", "strip1", 10);

    TEST_ASSERT_TRUE(group.addElement(&strip));

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&strip),
        group.findElementByPointer(&strip));

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&strip),
        group.findElementByName("strip1"));
}

void test_light_container_rejects_null_element()
{
    LightGroup group("group1", "group1");

    TEST_ASSERT_FALSE(group.addElement(nullptr));
}

void test_light_container_rejects_duplicate_pointer()
{
    LightGroup group("group1", "group1");
    Strip<46> strip("strip1", "strip1", 10);

    TEST_ASSERT_TRUE(group.addElement(&strip));
    TEST_ASSERT_FALSE(group.addElement(&strip));
}

void test_light_container_rejects_duplicate_name()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip1", 10);

    TEST_ASSERT_TRUE(group.addElement(&strip1));
    TEST_ASSERT_FALSE(group.addElement(&strip2));
}

void test_light_container_find_element_by_pointer()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&strip1),
        group.findElementByPointer(&strip1));

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&strip2),
        group.findElementByPointer(&strip2));

    TEST_ASSERT_NULL(
        group.findElementByPointer(nullptr));
}

void test_light_container_find_element_by_name()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&strip1),
        group.findElementByName("strip1"));

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&strip2),
        group.findElementByName("strip2"));

    TEST_ASSERT_NULL(
        group.findElementByName("unknown"));
}

void test_light_container_does_not_find_unregistered_element()
{
    LightGroup group("group1", "group1");

    Strip<46> strip("strip1", "strip1", 10);
    Strip<48> unregisteredStrip("unregisteredStrip", "unregisteredStrip", 10);

    group.addElement(&strip);

    TEST_ASSERT_NULL(
        group.findElementByPointer(&unregisteredStrip));

    TEST_ASSERT_NULL(
        group.findElementByName("unregisteredStrip"));
}

// This test is tied to LIGHT_GROUP_MAX_STRIPS.
// If the configured maximum changes, update the number of strips in this test.
void test_light_container_rejects_element_when_full()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);
    Strip<50> strip3("strip3", "strip3", 10);
    Strip<52> strip4("strip4", "strip4", 10);

    TEST_ASSERT_TRUE(group.addElement(&strip1));
    TEST_ASSERT_TRUE(group.addElement(&strip2));
    TEST_ASSERT_TRUE(group.addElement(&strip3));

    TEST_ASSERT_FALSE(group.addElement(&strip4));
}

void test_light_container_set_light_state()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);
    Strip<50> strip3("strip3", "strip3", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);
    group.addElement(&strip3);

    LightState state;
    state.enabled = true;
    state.color = {255, 100, 50};
    state.brightness = 128;

    state.animation.type = AnimationType::Snake;
    state.animation.parameters.snake.speed = 50;
    state.animation.parameters.snake.length = 3;

    group.setLightState(state);

    TEST_ASSERT_TRUE(strip1.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, strip1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, strip1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, strip1.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, strip1.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_TRUE(strip2.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, strip2.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, strip2.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, strip2.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, strip2.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip2.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip2.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip2.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_TRUE(strip3.getLightState().enabled);
    TEST_ASSERT_EQUAL_UINT8(255, strip3.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(100, strip3.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(50, strip3.getLightState().color.b);
    TEST_ASSERT_EQUAL_UINT8(128, strip3.getLightState().brightness);
    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip3.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip3.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip3.getLightState().animation.parameters.snake.length);
}

void test_light_container_on()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);
    Strip<50> strip3("strip3", "strip3", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);
    group.addElement(&strip3);

    strip1.off();
    strip2.off();
    strip3.off();

    group.on();

    TEST_ASSERT_TRUE(strip1.getLightState().enabled);
    TEST_ASSERT_TRUE(strip2.getLightState().enabled);
    TEST_ASSERT_TRUE(strip3.getLightState().enabled);
}

void test_light_container_off()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);
    Strip<50> strip3("strip3", "strip3", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);
    group.addElement(&strip3);

    strip1.on();
    strip2.on();
    strip3.on();

    group.off();

    TEST_ASSERT_FALSE(strip1.getLightState().enabled);
    TEST_ASSERT_FALSE(strip2.getLightState().enabled);
    TEST_ASSERT_FALSE(strip3.getLightState().enabled);
}

void test_light_container_set_color()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);
    Strip<50> strip3("strip3", "strip3", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);
    group.addElement(&strip3);

    Color color = {10, 20, 30};

    group.setColor(color);

    TEST_ASSERT_EQUAL_UINT8(10, strip1.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, strip1.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, strip1.getLightState().color.b);

    TEST_ASSERT_EQUAL_UINT8(10, strip2.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, strip2.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, strip2.getLightState().color.b);

    TEST_ASSERT_EQUAL_UINT8(10, strip3.getLightState().color.r);
    TEST_ASSERT_EQUAL_UINT8(20, strip3.getLightState().color.g);
    TEST_ASSERT_EQUAL_UINT8(30, strip3.getLightState().color.b);
}

void test_light_container_set_brightness()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);
    Strip<50> strip3("strip3", "strip3", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);
    group.addElement(&strip3);

    group.setBrightness(123);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        strip1.getLightState().brightness);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        strip2.getLightState().brightness);

    TEST_ASSERT_EQUAL_UINT8(
        123,
        strip3.getLightState().brightness);
}

void test_light_container_set_animation_state()
{
    LightGroup group("group1", "group1");

    Strip<46> strip1("strip1", "strip1", 10);
    Strip<48> strip2("strip2", "strip2", 10);
    Strip<50> strip3("strip3", "strip3", 10);

    group.addElement(&strip1);
    group.addElement(&strip2);
    group.addElement(&strip3);

    AnimationState animationState;
    animationState.type = AnimationType::Snake;
    animationState.parameters.snake.speed = 50;
    animationState.parameters.snake.length = 3;

    group.setAnimationState(animationState);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip1.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip1.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip1.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip2.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip2.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip2.getLightState().animation.parameters.snake.length);

    TEST_ASSERT_EQUAL(
        AnimationType::Snake,
        strip3.getLightState().animation.type);
    TEST_ASSERT_EQUAL_UINT16(
        50,
        strip3.getLightState().animation.parameters.snake.speed);
    TEST_ASSERT_EQUAL_UINT16(
        3,
        strip3.getLightState().animation.parameters.snake.length);
}

void run_light_container_tests()
{
    RUN_TEST(test_light_container_get_id_and_name);
    RUN_TEST(test_light_container_add_element);
    RUN_TEST(test_light_container_rejects_null_element);
    RUN_TEST(test_light_container_rejects_duplicate_pointer);
    RUN_TEST(test_light_container_rejects_duplicate_name);
    RUN_TEST(test_light_container_find_element_by_pointer);
    RUN_TEST(test_light_container_find_element_by_name);
    RUN_TEST(test_light_container_does_not_find_unregistered_element);
    RUN_TEST(test_light_container_rejects_element_when_full);
    RUN_TEST(test_light_container_set_light_state);
    RUN_TEST(test_light_container_on);
    RUN_TEST(test_light_container_off);
    RUN_TEST(test_light_container_set_color);
    RUN_TEST(test_light_container_set_brightness);
    RUN_TEST(test_light_container_set_animation_state);
}

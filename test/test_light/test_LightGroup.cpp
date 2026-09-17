#include <unity.h>
#include "LightGroup.h"
#include "Strip.h"

void test_light_group_to_json_empty()
{
    LightGroup lightGroup("lightGroup", "Light Group");

    JsonBuilder json;

    TEST_ASSERT_TRUE(lightGroup.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"lightGroup\",\"name\":\"Light Group\",\"type\":\"lightGroup\",\"children\":[]}",
        json.data());
}

void test_light_group_to_json_with_one_strip()
{
    LightGroup lightGroup("lightGroup", "Light Group");
    Strip<46> strip("strip1", "Strip 1", 10);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip));

    JsonBuilder json;

    TEST_ASSERT_TRUE(lightGroup.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"lightGroup\",\"name\":\"Light Group\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}",
        json.data());
}

void test_light_group_to_json_with_two_strips()
{
    LightGroup lightGroup("lightGroup", "Light Group");

    Strip<46> strip1("strip1", "Strip 1", 10);
    Strip<48> strip2("strip2", "Strip 2", 20);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup.addElement(&strip2));

    JsonBuilder json;

    TEST_ASSERT_TRUE(lightGroup.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"lightGroup\",\"name\":\"Light Group\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}},"
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}",
        json.data());
}

void test_light_group_to_json_with_static_and_animated_strips()
{
    LightGroup lightGroup("lightGroup", "Light Group");

    Strip<46> strip1("strip1", "Strip 1", 10);
    Strip<48> strip2("strip2", "Strip 2", 20);

    LightState state1 = {
        .enabled = true,
        .color = {255, 0, 0},
        .brightness = 128,
        .animation = {
            .type = AnimationType::None,
            .parameters = {}}};

    LightState state2 = {
        .enabled = true,
        .color = {0, 255, 0},
        .brightness = 200,
        .animation = {
            .type = AnimationType::Snake,
            .parameters = {
                .snake = {
                    .speed = 50,
                    .length = 5}}}};

    strip1.setLightState(state1);
    strip2.setLightState(state2);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup.addElement(&strip2));

    JsonBuilder json;

    TEST_ASSERT_TRUE(lightGroup.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"lightGroup\",\"name\":\"Light Group\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":true,\"color\":{\"r\":255,\"g\":0,\"b\":0},"
        "\"brightness\":128,\"animation\":{\"type\":\"none\",\"parameters\":{}}}},"
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":true,\"color\":{\"r\":0,\"g\":255,\"b\":0},"
        "\"brightness\":200,\"animation\":{\"type\":\"snake\",\"parameters\":{\"speed\":50,\"length\":5}}}}"
        "]}",
        json.data());
}

void run_light_group_tests()
{
    RUN_TEST(test_light_group_to_json_empty);
    RUN_TEST(test_light_group_to_json_with_one_strip);
    RUN_TEST(test_light_group_to_json_with_two_strips);
    RUN_TEST(test_light_group_to_json_with_static_and_animated_strips);
}

#include <unity.h>
#include "Room.h"
#include "LightGroup.h"
#include "Strip.h"

void test_room_to_json_empty()
{
    Room room("room", "Room");

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":[]}",
        json.data());
}

void test_room_to_json_with_one_light_group()
{
    Room room("room", "Room");

    LightGroup lightGroup("lightGroup1", "Light Group 1");
    Strip<46> strip("strip1", "Strip 1", 10);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip));
    TEST_ASSERT_TRUE(room.addElement(&lightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}",
        json.data());
}

void test_room_to_json_with_two_light_groups()
{
    Room room("room", "Room");

    LightGroup lightGroup1("lightGroup1", "Light Group 1");
    LightGroup lightGroup2("lightGroup2", "Light Group 2");

    Strip<46> strip1("strip1", "Strip 1", 10);
    Strip<48> strip2("strip2", "Strip 2", 20);

    TEST_ASSERT_TRUE(lightGroup1.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup2.addElement(&strip2));

    TEST_ASSERT_TRUE(room.addElement(&lightGroup1));
    TEST_ASSERT_TRUE(room.addElement(&lightGroup2));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]},"
        "{\"id\":\"lightGroup2\",\"name\":\"Light Group 2\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}",
        json.data());
}

void test_room_to_json_with_light_group_and_multiple_strips()
{
    Room room("room", "Room");

    LightGroup lightGroup("lightGroup1", "Light Group 1");

    Strip<46> strip1("strip1", "Strip 1", 10);
    Strip<48> strip2("strip2", "Strip 2", 20);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup.addElement(&strip2));

    TEST_ASSERT_TRUE(room.addElement(&lightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}},"
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}",
        json.data());
}

void test_room_to_json_with_light_group_and_direct_strip()
{
    Room room("room", "Room");

    LightGroup lightGroup("lightGroup1", "Light Group 1");

    Strip<46> groupStrip("groupStrip", "Group Strip", 10);
    Strip<48> directStrip("directStrip", "Direct Strip", 20);

    TEST_ASSERT_TRUE(lightGroup.addElement(&groupStrip));

    TEST_ASSERT_TRUE(room.addElement(&lightGroup));
    TEST_ASSERT_TRUE(room.addElement(&directStrip));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"groupStrip\",\"name\":\"Group Strip\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]},"
        "{\"id\":\"directStrip\",\"name\":\"Direct Strip\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}",
        json.data());
}

void test_room_to_json_with_direct_strip()
{
    Room room("room", "Room");

    Strip<46> strip("strip1", "Strip 1", 10);

    TEST_ASSERT_TRUE(room.addElement(&strip));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}",
        json.data());
}

void test_room_to_json_with_static_and_animated_strips()
{
    Room room("room", "Room");

    LightGroup lightGroup1("lightGroup1", "Light Group 1");
    LightGroup lightGroup2("lightGroup2", "Light Group 2");

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

    TEST_ASSERT_TRUE(lightGroup1.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup2.addElement(&strip2));

    TEST_ASSERT_TRUE(room.addElement(&lightGroup1));
    TEST_ASSERT_TRUE(room.addElement(&lightGroup2));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":true,\"color\":{\"r\":255,\"g\":0,\"b\":0},"
        "\"brightness\":128,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]},"
        "{\"id\":\"lightGroup2\",\"name\":\"Light Group 2\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":true,\"color\":{\"r\":0,\"g\":255,\"b\":0},"
        "\"brightness\":200,\"animation\":{\"type\":\"snake\",\"parameters\":{\"speed\":50,\"length\":5}}}}"
        "]}"
        "]}",
        json.data());
}

void run_room_tests()
{
    RUN_TEST(test_room_to_json_empty);
    RUN_TEST(test_room_to_json_with_one_light_group);
    RUN_TEST(test_room_to_json_with_two_light_groups);
    RUN_TEST(test_room_to_json_with_light_group_and_multiple_strips);
    RUN_TEST(test_room_to_json_with_light_group_and_direct_strip);
    RUN_TEST(test_room_to_json_with_direct_strip);
    RUN_TEST(test_room_to_json_with_static_and_animated_strips);
}

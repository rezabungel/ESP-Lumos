#include <unity.h>
#include "House.h"
#include "Room.h"
#include "LightGroup.h"
#include "Strip.h"

void test_house_to_json_empty()
{
    House house("house", "House");

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":[]}",
        json.data());
}

void test_house_to_json_with_room_light_group_and_strip()
{
    House house("house", "House");

    Room room("room1", "Room 1");
    LightGroup lightGroup("lightGroup1", "Light Group 1");
    Strip<46> strip("strip1", "Strip 1", 10);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip));
    TEST_ASSERT_TRUE(room.addElement(&lightGroup));
    TEST_ASSERT_TRUE(house.addElement(&room));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}"
        "]}",
        json.data());
}

void test_house_to_json_with_two_rooms_and_their_light_groups()
{
    House house("house", "House");

    Room room1("room1", "Room 1");
    Room room2("room2", "Room 2");

    LightGroup lightGroup1("lightGroup1", "Light Group 1");
    LightGroup lightGroup2("lightGroup2", "Light Group 2");

    Strip<46> strip1("strip1", "Strip 1", 10);
    Strip<48> strip2("strip2", "Strip 2", 20);

    TEST_ASSERT_TRUE(lightGroup1.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup2.addElement(&strip2));

    TEST_ASSERT_TRUE(room1.addElement(&lightGroup1));
    TEST_ASSERT_TRUE(room2.addElement(&lightGroup2));

    TEST_ASSERT_TRUE(house.addElement(&room1));
    TEST_ASSERT_TRUE(house.addElement(&room2));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]},"
        "{\"id\":\"room2\",\"name\":\"Room 2\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup2\",\"name\":\"Light Group 2\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}"
        "]}",
        json.data());
}

void test_house_to_json_with_light_group_and_strip()
{
    House house("house", "House");

    LightGroup lightGroup("lightGroup1", "Light Group 1");
    Strip<46> strip("strip1", "Strip 1", 10);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip));
    TEST_ASSERT_TRUE(house.addElement(&lightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}",
        json.data());
}

void test_house_to_json_with_room_and_direct_light_group()
{
    House house("house", "House");

    Room room("room1", "Room 1");

    LightGroup roomLightGroup("roomLightGroup", "Room Light Group");
    LightGroup houseLightGroup("houseLightGroup", "House Light Group");

    Strip<46> roomGroupStrip("roomGroupStrip", "Room Group Strip", 10);
    Strip<48> houseGroupStrip("houseGroupStrip", "House Group Strip", 20);

    TEST_ASSERT_TRUE(roomLightGroup.addElement(&roomGroupStrip));
    TEST_ASSERT_TRUE(room.addElement(&roomLightGroup));

    TEST_ASSERT_TRUE(houseLightGroup.addElement(&houseGroupStrip));

    TEST_ASSERT_TRUE(house.addElement(&room));
    TEST_ASSERT_TRUE(house.addElement(&houseLightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"roomLightGroup\",\"name\":\"Room Light Group\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"roomGroupStrip\",\"name\":\"Room Group Strip\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]},"
        "{\"id\":\"houseLightGroup\",\"name\":\"House Light Group\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"houseGroupStrip\",\"name\":\"House Group Strip\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}",
        json.data());
}

void test_house_to_json_with_room_and_multiple_light_groups()
{
    House house("house", "House");
    Room room("room1", "Room 1");

    LightGroup lightGroup1("lightGroup1", "Light Group 1");
    LightGroup lightGroup2("lightGroup2", "Light Group 2");

    Strip<46> strip1("strip1", "Strip 1", 10);
    Strip<48> strip2("strip2", "Strip 2", 20);

    TEST_ASSERT_TRUE(lightGroup1.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup2.addElement(&strip2));

    TEST_ASSERT_TRUE(room.addElement(&lightGroup1));
    TEST_ASSERT_TRUE(room.addElement(&lightGroup2));

    TEST_ASSERT_TRUE(house.addElement(&room));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
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
        "]}"
        "]}",
        json.data());
}

void test_house_to_json_with_room_light_group_and_multiple_strips()
{
    House house("house", "House");

    Room room("room1", "Room 1");
    LightGroup lightGroup("lightGroup1", "Light Group 1");

    Strip<46> strip1("strip1", "Strip 1", 10);
    Strip<48> strip2("strip2", "Strip 2", 20);

    TEST_ASSERT_TRUE(lightGroup.addElement(&strip1));
    TEST_ASSERT_TRUE(lightGroup.addElement(&strip2));

    TEST_ASSERT_TRUE(room.addElement(&lightGroup));
    TEST_ASSERT_TRUE(house.addElement(&room));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}},"
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]}"
        "]}",
        json.data());
}

void test_house_to_json_with_mixed_children()
{
    House house("house", "House");

    Room room("room1", "Room 1");
    LightGroup roomLightGroup1("roomLightGroup1", "Room Light Group 1");
    LightGroup roomLightGroup2("roomLightGroup2", "Room Light Group 2");

    LightGroup houseLightGroup("houseLightGroup", "House Light Group");

    Strip<46> roomGroupStrip1("roomGroupStrip1", "Room Group Strip 1", 10);
    Strip<48> roomGroupStrip2("roomGroupStrip2", "Room Group Strip 2", 20);
    Strip<50> houseGroupStrip("houseGroupStrip", "House Group Strip", 30);
    Strip<52> houseStrip("houseStrip", "House Strip", 40);

    TEST_ASSERT_TRUE(roomLightGroup1.addElement(&roomGroupStrip1));
    TEST_ASSERT_TRUE(roomLightGroup2.addElement(&roomGroupStrip2));
    TEST_ASSERT_TRUE(houseLightGroup.addElement(&houseGroupStrip));

    TEST_ASSERT_TRUE(room.addElement(&roomLightGroup1));
    TEST_ASSERT_TRUE(room.addElement(&roomLightGroup2));

    TEST_ASSERT_TRUE(house.addElement(&room));
    TEST_ASSERT_TRUE(house.addElement(&houseLightGroup));

    TEST_ASSERT_TRUE(house.addElement(&houseStrip));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"roomLightGroup1\",\"name\":\"Room Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"roomGroupStrip1\",\"name\":\"Room Group Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]},"
        "{\"id\":\"roomLightGroup2\",\"name\":\"Room Light Group 2\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"roomGroupStrip2\",\"name\":\"Room Group Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}"
        "]},"
        "{\"id\":\"houseLightGroup\",\"name\":\"House Light Group\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"houseGroupStrip\",\"name\":\"House Group Strip\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]},"
        "{\"id\":\"houseStrip\",\"name\":\"House Strip\",\"type\":\"strip\","
        "\"state\":{\"enabled\":false,\"color\":{\"r\":0,\"g\":0,\"b\":0},"
        "\"brightness\":255,\"animation\":{\"type\":\"none\",\"parameters\":{}}}}"
        "]}",
        json.data());
}

void test_house_to_json_with_static_and_animated_strips()
{
    House house("house", "House");

    Room room("room1", "Room 1");
    LightGroup lightGroup("lightGroup1", "Light Group 1");

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

    TEST_ASSERT_TRUE(room.addElement(&lightGroup));
    TEST_ASSERT_TRUE(house.addElement(&room));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":["
        "{\"id\":\"strip1\",\"name\":\"Strip 1\",\"type\":\"strip\","
        "\"state\":{\"enabled\":true,\"color\":{\"r\":255,\"g\":0,\"b\":0},"
        "\"brightness\":128,\"animation\":{\"type\":\"none\",\"parameters\":{}}}},"
        "{\"id\":\"strip2\",\"name\":\"Strip 2\",\"type\":\"strip\","
        "\"state\":{\"enabled\":true,\"color\":{\"r\":0,\"g\":255,\"b\":0},"
        "\"brightness\":200,\"animation\":{\"type\":\"snake\",\"parameters\":{\"speed\":50,\"length\":5}}}}"
        "]}"
        "]}"
        "]}",
        json.data());
}

void run_house_tests()
{
    RUN_TEST(test_house_to_json_empty);
    RUN_TEST(test_house_to_json_with_room_light_group_and_strip);
    RUN_TEST(test_house_to_json_with_two_rooms_and_their_light_groups);
    RUN_TEST(test_house_to_json_with_light_group_and_strip);
    RUN_TEST(test_house_to_json_with_room_and_direct_light_group);
    RUN_TEST(test_house_to_json_with_room_and_multiple_light_groups);
    RUN_TEST(test_house_to_json_with_room_light_group_and_multiple_strips);
    RUN_TEST(test_house_to_json_with_mixed_children);
    RUN_TEST(test_house_to_json_with_static_and_animated_strips);
}

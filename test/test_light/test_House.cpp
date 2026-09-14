#include <unity.h>
#include "House.h"
#include "Room.h"
#include "LightGroup.h"

void test_house_to_json_empty()
{
    House house("house", "House");

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":[]}",
        json.data());
}

void test_house_to_json_with_one_room()
{
    House house("house", "House");
    Room room("room1", "Room 1");

    TEST_ASSERT_TRUE(house.addElement(&room));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":[]}"
        "]}",
        json.data());
}

void test_house_to_json_with_two_rooms()
{
    House house("house", "House");
    Room room1("room1", "Room 1");
    Room room2("room2", "Room 2");

    TEST_ASSERT_TRUE(house.addElement(&room1));
    TEST_ASSERT_TRUE(house.addElement(&room2));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":[]},"
        "{\"id\":\"room2\",\"name\":\"Room 2\",\"type\":\"room\",\"children\":[]}"
        "]}",
        json.data());
}

void test_house_to_json_with_one_light_group()
{
    House house("house", "House");
    LightGroup lightGroup("lightGroup1", "Light Group 1");

    TEST_ASSERT_TRUE(house.addElement(&lightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":[]}"
        "]}",
        json.data());
}

void test_house_to_json_with_room_and_light_group()
{
    House house("house", "House");
    Room room("room1", "Room 1");
    LightGroup lightGroup("lightGroup1", "Light Group 1");

    TEST_ASSERT_TRUE(house.addElement(&room));
    TEST_ASSERT_TRUE(house.addElement(&lightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":[]},"
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":[]}"
        "]}",
        json.data());
}

void test_house_to_json_with_room_containing_two_light_groups()
{
    House house("house", "House");
    Room room("room1", "Room 1");

    LightGroup lightGroup1("lightGroup1", "Light Group 1");
    LightGroup lightGroup2("lightGroup2", "Light Group 2");

    TEST_ASSERT_TRUE(room.addElement(&lightGroup1));
    TEST_ASSERT_TRUE(room.addElement(&lightGroup2));

    TEST_ASSERT_TRUE(house.addElement(&room));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":[]},"
        "{\"id\":\"lightGroup2\",\"name\":\"Light Group 2\",\"type\":\"lightGroup\",\"children\":[]}"
        "]}"
        "]}",
        json.data());
}

void test_house_to_json_with_mixed_nested_elements()
{
    House house("house", "House");

    Room room("room1", "Room 1");
    LightGroup roomLightGroup1("roomLightGroup1", "Room Light Group 1");
    LightGroup roomLightGroup2("roomLightGroup2", "Room Light Group 2");

    LightGroup houseLightGroup("houseLightGroup", "House Light Group");

    TEST_ASSERT_TRUE(room.addElement(&roomLightGroup1));
    TEST_ASSERT_TRUE(room.addElement(&roomLightGroup2));

    TEST_ASSERT_TRUE(house.addElement(&room));
    TEST_ASSERT_TRUE(house.addElement(&houseLightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(house.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\",\"children\":["
        "{\"id\":\"room1\",\"name\":\"Room 1\",\"type\":\"room\",\"children\":["
        "{\"id\":\"roomLightGroup1\",\"name\":\"Room Light Group 1\",\"type\":\"lightGroup\",\"children\":[]},"
        "{\"id\":\"roomLightGroup2\",\"name\":\"Room Light Group 2\",\"type\":\"lightGroup\",\"children\":[]}"
        "]},"
        "{\"id\":\"houseLightGroup\",\"name\":\"House Light Group\",\"type\":\"lightGroup\",\"children\":[]}"
        "]}",
        json.data());
}

// TODO: Add Strip-based test cases once Strip testing is available
// in the native environment.
//
// The tests should cover different hierarchy variants, including:
// - House -> LightGroup -> Strip
// - House -> Room -> LightGroup -> Strip
// - House -> Room -> multiple LightGroups -> Strips
// - House -> Room -> LightGroup -> multiple Strips
// - mixed branches containing Rooms and LightGroups with Strips
//
// The tests should also verify serialized Strip state.

void run_house_tests()
{
    RUN_TEST(test_house_to_json_empty);
    RUN_TEST(test_house_to_json_with_one_room);
    RUN_TEST(test_house_to_json_with_two_rooms);
    RUN_TEST(test_house_to_json_with_one_light_group);
    RUN_TEST(test_house_to_json_with_room_and_light_group);
    RUN_TEST(test_house_to_json_with_room_containing_two_light_groups);
    RUN_TEST(test_house_to_json_with_mixed_nested_elements);
}

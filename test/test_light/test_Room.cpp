#include <unity.h>
#include "Room.h"
#include "LightGroup.h"

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

    TEST_ASSERT_TRUE(room.addElement(&lightGroup));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":[]}"
        "]}",
        json.data());
}

void test_room_to_json_with_two_light_groups()
{
    Room room("room", "Room");

    LightGroup lightGroup1("lightGroup1", "Light Group 1");
    LightGroup lightGroup2("lightGroup2", "Light Group 2");

    TEST_ASSERT_TRUE(room.addElement(&lightGroup1));
    TEST_ASSERT_TRUE(room.addElement(&lightGroup2));

    JsonBuilder json;

    TEST_ASSERT_TRUE(room.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\",\"name\":\"Room\",\"type\":\"room\",\"children\":["
        "{\"id\":\"lightGroup1\",\"name\":\"Light Group 1\",\"type\":\"lightGroup\",\"children\":[]},"
        "{\"id\":\"lightGroup2\",\"name\":\"Light Group 2\",\"type\":\"lightGroup\",\"children\":[]}"
        "]}",
        json.data());
}

// TODO: Add Strip-based test cases once Strip testing is available
// in the native environment.
//
// The tests should cover:
// - Room -> LightGroup -> Strip
// - Room -> LightGroup -> multiple Strips
// - Room -> multiple LightGroups -> Strips
// - different Strip states.

void run_room_tests()
{
    RUN_TEST(test_room_to_json_empty);
    RUN_TEST(test_room_to_json_with_one_light_group);
    RUN_TEST(test_room_to_json_with_two_light_groups);
}

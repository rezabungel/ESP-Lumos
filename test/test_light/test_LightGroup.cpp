#include <unity.h>
#include "LightGroup.h"

void test_light_group_to_json_empty()
{
    LightGroup lightGroup("lightGroup", "Light Group");

    JsonBuilder json;

    TEST_ASSERT_TRUE(lightGroup.toJson(json));

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"lightGroup\",\"name\":\"Light Group\",\"type\":\"lightGroup\",\"children\":[]}",
        json.data());
}

// TODO: Add Strip-based test cases once Strip testing is available
// in the native environment.
//
// The tests should cover:
// - LightGroup -> one Strip
// - LightGroup -> multiple Strips
// - different Strip states
// - animated and non-animated Strips.

void run_light_group_tests()
{
    RUN_TEST(test_light_group_to_json_empty);
}

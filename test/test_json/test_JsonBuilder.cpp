#include <unity.h>
#include "json/JsonBuilder.h"

void test_empty_object()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING("{}", json.data());
    TEST_ASSERT_EQUAL_UINT16(2, json.size());
}

void test_empty_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginArray());
    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_EQUAL_STRING("[]", json.data());
    TEST_ASSERT_EQUAL_UINT16(2, json.size());
}

void test_object_fields()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("id", "house"));
    TEST_ASSERT_TRUE(json.add("name", "House"));
    TEST_ASSERT_TRUE(json.add("type", "house"));

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"name\":\"House\",\"type\":\"house\"}",
        json.data());
}

void test_object_bool_field()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("enabled", true));
    TEST_ASSERT_TRUE(json.add("disabled", false));

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"enabled\":true,\"disabled\":false}",
        json.data());
}

void test_object_uint8_field()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("zero", static_cast<uint8_t>(0)));
    TEST_ASSERT_TRUE(json.add("value", static_cast<uint8_t>(128)));
    TEST_ASSERT_TRUE(json.add("max", static_cast<uint8_t>(255)));

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"zero\":0,\"value\":128,\"max\":255}",
        json.data());
}

void test_object_uint16_field()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("zero", static_cast<uint16_t>(0)));
    TEST_ASSERT_TRUE(json.add("value", static_cast<uint16_t>(12345)));
    TEST_ASSERT_TRUE(json.add("max", static_cast<uint16_t>(65535)));

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"zero\":0,\"value\":12345,\"max\":65535}",
        json.data());
}

void test_object_mixed_field_types()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("id", "strip1"));
    TEST_ASSERT_TRUE(json.add("enabled", true));
    TEST_ASSERT_TRUE(json.add("r", static_cast<uint8_t>(255)));
    TEST_ASSERT_TRUE(json.add("brightness", static_cast<uint8_t>(128)));
    TEST_ASSERT_TRUE(json.add("speed", static_cast<uint16_t>(500)));

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"strip1\",\"enabled\":true,\"r\":255,"
        "\"brightness\":128,\"speed\":500}",
        json.data());
}

void test_object_empty_string_value()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("name", ""));

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"name\":\"\"}",
        json.data());
}

void test_single_object_in_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginArray());

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "room1"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_EQUAL_STRING(
        "[{\"id\":\"room1\"}]",
        json.data());
}

void test_multiple_objects_in_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginArray());

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "room1"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "room2"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_EQUAL_STRING(
        "[{\"id\":\"room1\"},{\"id\":\"room2\"}]",
        json.data());
}

void test_nested_object()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.beginObject("children"));
    TEST_ASSERT_TRUE(json.add("id", "room1"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"children\":{\"id\":\"room1\"}}",
        json.data());
}

void test_nested_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.beginArray("children"));

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "room1"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "room2"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endArray());
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"children\":[{\"id\":\"room1\"},{\"id\":\"room2\"}]}",
        json.data());
}

void test_nested_object_and_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("id", "house"));

    TEST_ASSERT_TRUE(json.beginArray("children"));

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "room1"));

    TEST_ASSERT_TRUE(json.beginArray("children"));

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "group1"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endArray());
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endArray());
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\",\"children\":[{\"id\":\"room1\","
        "\"children\":[{\"id\":\"group1\"}]}]}",
        json.data());
}

void test_cannot_begin_object_inside_object_without_name()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_FALSE(json.beginObject());

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING("{}", json.data());
}

void test_cannot_begin_array_inside_object_without_name()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_FALSE(json.beginArray());

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING("{}", json.data());
}

void test_failed_begin_object_does_not_break_builder()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_FALSE(json.beginObject());

    TEST_ASSERT_TRUE(json.add("id", "house"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\"}",
        json.data());
}

void test_failed_begin_array_does_not_break_builder()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_FALSE(json.beginArray());

    TEST_ASSERT_TRUE(json.add("id", "house"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\"}",
        json.data());
}

void test_can_begin_object_inside_object_with_name()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.beginObject("children"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"children\":{}}",
        json.data());
}

void test_can_begin_array_inside_object_with_name()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_TRUE(json.beginArray("children"));
    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"children\":[]}",
        json.data());
}

void test_can_begin_object_inside_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginArray());

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_EQUAL_STRING(
        "[{}]",
        json.data());
}

void test_can_begin_array_inside_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginArray());

    TEST_ASSERT_TRUE(json.beginArray());
    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_EQUAL_STRING(
        "[[]]",
        json.data());
}

void test_cannot_close_empty_builder()
{
    JsonBuilder json;

    TEST_ASSERT_FALSE(json.endObject());
    TEST_ASSERT_FALSE(json.endArray());

    TEST_ASSERT_EQUAL_STRING("", json.data());
    TEST_ASSERT_EQUAL_UINT16(0, json.size());
}

void test_cannot_close_object_as_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    TEST_ASSERT_FALSE(json.endArray());

    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING("{}", json.data());
}

void test_cannot_close_array_as_object()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginArray());

    TEST_ASSERT_FALSE(json.endObject());

    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_EQUAL_STRING("[]", json.data());
}

void test_cannot_add_field_to_array()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginArray());

    TEST_ASSERT_FALSE(json.add("id", "house"));

    TEST_ASSERT_TRUE(json.endArray());

    TEST_ASSERT_EQUAL_STRING("[]", json.data());
}

void test_max_depth()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());    // 1
    TEST_ASSERT_TRUE(json.beginArray("a"));  // 2
    TEST_ASSERT_TRUE(json.beginObject());    // 3
    TEST_ASSERT_TRUE(json.beginArray("b"));  // 4
    TEST_ASSERT_TRUE(json.beginObject());    // 5
    TEST_ASSERT_TRUE(json.beginArray("c"));  // 6
    TEST_ASSERT_TRUE(json.beginObject());    // 7
    TEST_ASSERT_TRUE(json.beginObject("d")); // 8

    TEST_ASSERT_FALSE(json.beginObject());

    TEST_ASSERT_TRUE(json.endObject());
    TEST_ASSERT_TRUE(json.endObject());
    TEST_ASSERT_TRUE(json.endArray());
    TEST_ASSERT_TRUE(json.endObject());
    TEST_ASSERT_TRUE(json.endArray());
    TEST_ASSERT_TRUE(json.endObject());
    TEST_ASSERT_TRUE(json.endArray());
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"a\":[{\"b\":[{\"c\":[{\"d\":{}}]}]}]}",
        json.data());
}

void test_add_name_returns_false_on_buffer_overflow()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    char name[JSON_BUILDER_BUFFER_SIZE];
    memset(name, 'x', sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';

    TEST_ASSERT_FALSE(json.add(name));
}

void test_add_name_and_value_returns_false_on_buffer_overflow()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    char value[JSON_BUILDER_BUFFER_SIZE];
    memset(value, 'x', sizeof(value) - 1);
    value[sizeof(value) - 1] = '\0';

    TEST_ASSERT_FALSE(json.add("value", value));
}

void test_begin_object_returns_false_on_buffer_overflow()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    char name[JSON_BUILDER_BUFFER_SIZE];
    memset(name, 'x', sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';

    TEST_ASSERT_FALSE(json.beginObject(name));
}

void test_begin_array_returns_false_on_buffer_overflow()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());

    char name[JSON_BUILDER_BUFFER_SIZE];
    memset(name, 'x', sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';

    TEST_ASSERT_FALSE(json.beginArray(name));
}

void test_data_is_null_terminated()
{
    JsonBuilder json;

    TEST_ASSERT_TRUE(json.beginObject());
    TEST_ASSERT_TRUE(json.add("id", "house"));
    TEST_ASSERT_TRUE(json.endObject());

    TEST_ASSERT_EQUAL_CHAR('\0', json.data()[json.size()]);
}

void test_multiple_builders_are_independent()
{
    JsonBuilder json1;
    JsonBuilder json2;

    TEST_ASSERT_TRUE(json1.beginObject());
    TEST_ASSERT_TRUE(json1.add("id", "house"));
    TEST_ASSERT_TRUE(json1.endObject());

    TEST_ASSERT_TRUE(json2.beginObject());
    TEST_ASSERT_TRUE(json2.add("id", "room"));
    TEST_ASSERT_TRUE(json2.endObject());

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"house\"}",
        json1.data());

    TEST_ASSERT_EQUAL_STRING(
        "{\"id\":\"room\"}",
        json2.data());
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_empty_object);
    RUN_TEST(test_empty_array);

    RUN_TEST(test_object_fields);

    RUN_TEST(test_object_bool_field);
    RUN_TEST(test_object_uint8_field);
    RUN_TEST(test_object_uint16_field);
    RUN_TEST(test_object_mixed_field_types);
    RUN_TEST(test_object_empty_string_value);

    RUN_TEST(test_single_object_in_array);
    RUN_TEST(test_multiple_objects_in_array);

    RUN_TEST(test_nested_object);
    RUN_TEST(test_nested_array);
    RUN_TEST(test_nested_object_and_array);

    RUN_TEST(test_cannot_begin_object_inside_object_without_name);
    RUN_TEST(test_cannot_begin_array_inside_object_without_name);

    RUN_TEST(test_failed_begin_object_does_not_break_builder);
    RUN_TEST(test_failed_begin_array_does_not_break_builder);

    RUN_TEST(test_can_begin_object_inside_object_with_name);
    RUN_TEST(test_can_begin_array_inside_object_with_name);
    RUN_TEST(test_can_begin_object_inside_array);
    RUN_TEST(test_can_begin_array_inside_array);

    RUN_TEST(test_cannot_close_empty_builder);
    RUN_TEST(test_cannot_close_object_as_array);
    RUN_TEST(test_cannot_close_array_as_object);
    RUN_TEST(test_cannot_add_field_to_array);

    RUN_TEST(test_max_depth);

    RUN_TEST(test_add_name_returns_false_on_buffer_overflow);
    RUN_TEST(test_add_name_and_value_returns_false_on_buffer_overflow);
    RUN_TEST(test_begin_object_returns_false_on_buffer_overflow);
    RUN_TEST(test_begin_array_returns_false_on_buffer_overflow);

    RUN_TEST(test_data_is_null_terminated);

    RUN_TEST(test_multiple_builders_are_independent);

    return UNITY_END();
}

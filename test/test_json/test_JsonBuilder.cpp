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

    RUN_TEST(test_single_object_in_array);
    RUN_TEST(test_multiple_objects_in_array);

    RUN_TEST(test_nested_object);
    RUN_TEST(test_nested_array);
    RUN_TEST(test_nested_object_and_array);

    RUN_TEST(test_cannot_close_empty_builder);
    RUN_TEST(test_cannot_close_object_as_array);
    RUN_TEST(test_cannot_close_array_as_object);
    RUN_TEST(test_cannot_add_field_to_array);

    RUN_TEST(test_data_is_null_terminated);

    RUN_TEST(test_multiple_builders_are_independent);

    return UNITY_END();
}

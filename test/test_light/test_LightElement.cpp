#include <unity.h>
#include "LightElement.h"

class TestLightElement : public LightElement
{
public:
    TestLightElement(const char *id, const char *name)
        : LightElement(id, name)
    {
    }

    LightElementType getType() const override
    {
        return LightElementType::Strip;
    }

    bool toJson(JsonBuilder &) const override
    {
        return true;
    }

    void setLightState(const LightState &) override
    {
    }

    void on() override
    {
    }

    void off() override
    {
    }

    void setColor(const Color &) override
    {
    }

    void setBrightness(uint8_t) override
    {
    }

    void setAnimationState(const AnimationState &) override
    {
    }
};

void test_light_element_get_id()
{
    TestLightElement element("element1", "Element 1");

    TEST_ASSERT_EQUAL_STRING(
        "element1",
        element.getId());
}

void test_light_element_get_name()
{
    TestLightElement element("element1", "Element 1");

    TEST_ASSERT_EQUAL_STRING(
        "Element 1",
        element.getName());
}

void test_light_element_get_id_and_name_for_const_element()
{
    const TestLightElement element("element1", "Element 1");

    TEST_ASSERT_EQUAL_STRING(
        "element1",
        element.getId());

    TEST_ASSERT_EQUAL_STRING(
        "Element 1",
        element.getName());
}

void test_light_element_find_element_by_pointer()
{
    TestLightElement element("element1", "Element 1");
    TestLightElement anotherElement("element2", "Element 2");

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&element),
        element.findElementByPointer(&element));

    TEST_ASSERT_NULL(
        element.findElementByPointer(&anotherElement));

    TEST_ASSERT_NULL(
        element.findElementByPointer(nullptr));
}

void test_light_element_find_element_by_id()
{
    TestLightElement element("element1", "Element 1");

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&element),
        element.findElementById("element1"));

    TEST_ASSERT_NULL(
        element.findElementById("unknown"));

    TEST_ASSERT_NULL(
        element.findElementById(nullptr));
}

void test_light_element_find_element_by_id_for_const_element()
{
    const TestLightElement element("element1", "Element 1");

    TEST_ASSERT_EQUAL_PTR(
        static_cast<const LightElement *>(&element),
        element.findElementById("element1"));

    TEST_ASSERT_NULL(
        element.findElementById("unknown"));

    TEST_ASSERT_NULL(
        element.findElementById(nullptr));
}

void test_light_element_get_parent_returns_null_for_detached_element()
{
    TestLightElement element("element1", "Element 1");

    TEST_ASSERT_NULL(element.getParent());
}

void test_light_element_get_root_returns_self_for_detached_element()
{
    TestLightElement element("element1", "Element 1");

    TEST_ASSERT_EQUAL_PTR(
        static_cast<LightElement *>(&element),
        element.getRoot());
}

void test_light_element_get_parent_and_root_for_const_element()
{
    const TestLightElement element("element1", "Element 1");

    TEST_ASSERT_NULL(element.getParent());

    TEST_ASSERT_EQUAL_PTR(
        static_cast<const LightElement *>(&element),
        element.getRoot());
}

void run_light_element_tests()
{
    RUN_TEST(test_light_element_get_id);
    RUN_TEST(test_light_element_get_name);
    RUN_TEST(test_light_element_get_id_and_name_for_const_element);
    RUN_TEST(test_light_element_find_element_by_pointer);
    RUN_TEST(test_light_element_find_element_by_id);
    RUN_TEST(test_light_element_find_element_by_id_for_const_element);
    RUN_TEST(test_light_element_get_parent_returns_null_for_detached_element);
    RUN_TEST(test_light_element_get_root_returns_self_for_detached_element);
    RUN_TEST(test_light_element_get_parent_and_root_for_const_element);
}

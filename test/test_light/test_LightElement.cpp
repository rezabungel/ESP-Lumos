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

void run_light_element_tests()
{
    RUN_TEST(test_light_element_get_id);
    RUN_TEST(test_light_element_get_name);
    RUN_TEST(test_light_element_get_id_and_name_for_const_element);
}

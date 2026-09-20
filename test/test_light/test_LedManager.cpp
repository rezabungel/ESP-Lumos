#include <unity.h>
#include "LedManager.h"

class TestStripBase : public StripBase
{
public:
    bool renderCalled = false;
    uint32_t lastRenderTime = 0;
    bool renderResult = false;

    bool render(uint32_t now) override
    {
        renderCalled = true;
        lastRenderTime = now;
        return renderResult;
    }
};

class TestLedManager : public LedManager
{
public:
    bool showCalled = false;

protected:
    void show() override
    {
        showCalled = true;
    }
};

void test_led_manager_add_strip()
{
    LedManager manager;
    TestStripBase strip;

    TEST_ASSERT_TRUE(manager.addStrip(&strip));
}

void test_led_manager_rejects_null_strip()
{
    LedManager manager;

    TEST_ASSERT_FALSE(manager.addStrip(nullptr));
}

void test_led_manager_rejects_strip_when_full()
{
    LedManager manager;

    TestStripBase strips[LedManager::MAX_STRIPS + 1];

    for (uint8_t i = 0; i < LedManager::MAX_STRIPS; ++i)
    {
        TEST_ASSERT_TRUE(manager.addStrip(&strips[i]));
    }

    TEST_ASSERT_FALSE(
        manager.addStrip(&strips[LedManager::MAX_STRIPS]));
}

void test_led_manager_update_calls_render_on_all_strips()
{
    LedManager manager;

    TestStripBase strip1;
    TestStripBase strip2;
    TestStripBase strip3;

    TEST_ASSERT_TRUE(manager.addStrip(&strip1));
    TEST_ASSERT_TRUE(manager.addStrip(&strip2));
    TEST_ASSERT_TRUE(manager.addStrip(&strip3));

    manager.update(1234);

    TEST_ASSERT_TRUE(strip1.renderCalled);
    TEST_ASSERT_TRUE(strip2.renderCalled);
    TEST_ASSERT_TRUE(strip3.renderCalled);

    TEST_ASSERT_EQUAL_UINT32(1234, strip1.lastRenderTime);
    TEST_ASSERT_EQUAL_UINT32(1234, strip2.lastRenderTime);
    TEST_ASSERT_EQUAL_UINT32(1234, strip3.lastRenderTime);
}

void test_led_manager_update_does_not_show_when_no_strip_changed()
{
    TestLedManager manager;

    TestStripBase strip1;
    TestStripBase strip2;

    strip1.renderResult = false;
    strip2.renderResult = false;

    TEST_ASSERT_TRUE(manager.addStrip(&strip1));
    TEST_ASSERT_TRUE(manager.addStrip(&strip2));

    manager.update(1234);

    TEST_ASSERT_FALSE(manager.showCalled);
}

void test_led_manager_update_shows_when_strip_changed()
{
    TestLedManager manager;

    TestStripBase strip1;

    strip1.renderResult = true;

    TEST_ASSERT_TRUE(manager.addStrip(&strip1));

    manager.update(1234);

    TEST_ASSERT_TRUE(manager.showCalled);
}

void test_led_manager_update_shows_when_any_strip_changed()
{
    TestLedManager manager;

    TestStripBase strip1;
    TestStripBase strip2;
    TestStripBase strip3;

    strip1.renderResult = false;
    strip2.renderResult = true;
    strip3.renderResult = false;

    TEST_ASSERT_TRUE(manager.addStrip(&strip1));
    TEST_ASSERT_TRUE(manager.addStrip(&strip2));
    TEST_ASSERT_TRUE(manager.addStrip(&strip3));

    manager.update(1234);

    TEST_ASSERT_TRUE(manager.showCalled);
}

void run_led_manager_tests()
{
    RUN_TEST(test_led_manager_add_strip);
    RUN_TEST(test_led_manager_rejects_null_strip);
    RUN_TEST(test_led_manager_rejects_strip_when_full);
    RUN_TEST(test_led_manager_update_calls_render_on_all_strips);
    RUN_TEST(test_led_manager_update_does_not_show_when_no_strip_changed);
    RUN_TEST(test_led_manager_update_shows_when_strip_changed);
    RUN_TEST(test_led_manager_update_shows_when_any_strip_changed);
}

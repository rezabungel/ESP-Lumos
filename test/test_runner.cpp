#include <unity.h>

extern void run_json_builder_tests();
extern void run_color_tests();

void setUp()
{
}

void tearDown()
{
}

int main()
{
    UNITY_BEGIN();

    run_json_builder_tests();
    run_color_tests();

    return UNITY_END();
}

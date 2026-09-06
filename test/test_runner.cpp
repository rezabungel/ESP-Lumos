#include <unity.h>

extern void run_json_builder_tests();

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

    return UNITY_END();
}

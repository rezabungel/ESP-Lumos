#include <unity.h>

extern void run_animation_state_tests();
extern void run_animation_type_tests();
extern void run_snake_animation_tests();

void setUp()
{
}

void tearDown()
{
}

int main()
{
    UNITY_BEGIN();

    run_animation_state_tests();
    run_animation_type_tests();
    run_snake_animation_tests();

    return UNITY_END();
}

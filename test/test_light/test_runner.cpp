#include <unity.h>

extern void run_light_element_type_tests();
extern void run_light_state_tests();
extern void run_house_tests();
extern void run_room_tests();
extern void run_light_group_tests();
extern void run_strip_tests();
extern void run_light_container_tests();
extern void run_light_hierarchy_tests();
extern void run_led_manager_tests();

void setUp()
{
}

void tearDown()
{
}

int main()
{
    UNITY_BEGIN();

    run_light_element_type_tests();
    run_light_state_tests();

    run_house_tests();
    run_room_tests();
    run_light_group_tests();
    run_strip_tests();

    run_light_container_tests();
    run_light_hierarchy_tests();

    run_led_manager_tests();

    return UNITY_END();
}

#include <unity.h>

extern void run_request_body_context_tests();

void setUp()
{
}

void tearDown()
{
}

int main()
{
    UNITY_BEGIN();

    run_request_body_context_tests();

    return UNITY_END();
}

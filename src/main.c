#include <common.h>

static void testRoutines(void);

int main(void)
{
    halInit();
    chSysInit();

    #ifdef TEST_ROUTINE
        testRoutines();
    #else
        while(true)
        {

        }
    #endif
}

static void testRoutines(void)
{
    #if (TEST_ROUTINE == MOTOR_DIR_TEST_ROUTINE)
        lldTestDirectionMotorPower();
    #elif (TEST_ROUTINE == MOTOR_POWER_TEST_ROUTINE)
        lldTestMotorPower();
    #elif (TEST_ROUTINE == MOTOR_RAW_POWER_TEST_ROUTINE)
        lldTestRawMotorPower();
    #elif (TEST_ROUTINE == ENCODER_TEST_ROUTINE)
        lldTestEncoder();
    #endif
}

#include <common.h>
#include <tests.h>

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
        lldTestDirectionMotorPower(3);
    #elif (TEST_ROUTINE == MOTOR_POWER_TEST_ROUTINE)
        lldTestMotorPower(3);
    #elif (TEST_ROUTINE == MOTOR_RAW_POWER_TEST_ROUTINE)
        lldTestRawMotorPower(3);
    #elif (TEST_ROUTINE == ENCODER_TEST_ROUTINE)
        lldTestEncoder();
    #elif (TEST_ROUTINE == ODOMETRY_TEST_ROUTINE)
        odometryTestMotorSpeed();
    #elif (TEST_ROUTINE == MPU6050_TEST_ROUTINE)
        MPU6050Test();
    #endif
}

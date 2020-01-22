#include <tests.h>
#include <chprintf.h>
#include <odometry.h>

int32_t RPS_test = 0;
int32_t RPM_test = 0;

static bool serialInitialized = false;

static const SerialConfig sd7conf = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};

void serialOdometryInit(void)
{
    if (serialInitialized)
        return;

    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));
    sdStart(&SD7, &sd7conf);

    serialInitialized = true;
}

/**
 * @brief   Test motors rotation speed in revolutions per unit
 * @note    Revs value receives from encoder
 */
void odometryTestMotorSpeed(void)
{
    systime_t time = chVTGetSystemTime();
    odometryInit();
    serialOdometryInit();
    while(true)
    {
        RPS_test = (int32_t)odometryGetMotorSpeed(RPS);
        RPM_test = (int32_t)odometryGetMotorSpeed(RPM);
        chprintf(((BaseSequentialStream *)&SD7), "RPS:%d RPM:%d\n\r",
                 RPS_test, RPM_test);
        time = chThdSleepUntilWindowed(time, time + MS2ST(100));
    }
}

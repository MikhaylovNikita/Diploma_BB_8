#include <tests.h>
#include <chprintf.h>
#include <mpu6050.h>

int16_t mpu_test[7];
uint8_t k = 0;

static bool serialInitialized = false;

static const SerialConfig sd7conf = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};

void serialMPU6050Init(void)
{
    if (serialInitialized)
        return;

    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));
    sdStart(&SD7, &sd7conf);

    serialInitialized = true;
}

/**
 * @brief   Test MPU6050 output values of angle and acceleration
 * @note    Return raw values
 */
void MPU6050Test(void)
{
    systime_t time = chVTGetSystemTime();
    serialMPU6050Init();
    MPU6050Init();
    while(true)
    {
        chprintf(((BaseSequentialStream *)&SD7), "Angle:  ");
        for(k = 0; k < 3; k++)
        {
            mpu_test[k] = MPU6050GetData(k);
            chprintf(((BaseSequentialStream *)&SD7), "%d  ", mpu_test[k]);
        }
        chprintf(((BaseSequentialStream *)&SD7), "    Accel:  ");
        for(k = 4; k < 7; k++)
        {
            mpu_test[k] = MPU6050GetData(k);
            chprintf(((BaseSequentialStream *)&SD7), "%d  ", mpu_test[k]);
        }
        chprintf(((BaseSequentialStream *)&SD7), "\n\r");
        time = chThdSleepUntilWindowed(time, time + MS2ST(100));
    }
}

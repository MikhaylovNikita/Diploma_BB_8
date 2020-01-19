#include <ch.h>
#include <hal.h>
#include <chprintf.h>
#include <lld_control.h>
#include <tests.h>

int16_t val = 0;

/**
 * @brief   Test motors direction
 */
void lldTestDirectionMotorPower(void)
{
    systime_t time = chVTGetSystemTime();
    while (true)
    {
        char buf = sdGet(&SD7);
        switch(buf)
        {
            case '1':
                val = -50;
                lldControlSetMotorPower(val);
                break;

            case '2':
                val = 50;
                lldControlSetMotorPower(val);
                break;
        }
        chprintf(((BaseSequentialStream *)&SD7), "%d\r\n", val);
        time = chThdSleepUntilWindowed(time, time + MS2ST(250));
    }
}

/**
 * @brief   Test motors rotation speed
 * @note    Changing raw values of pwm dutycycle
 */
void lldTestRawMotorPower(void)
{
    systime_t time = chVTGetSystemTime();
    while (true)
    {
        char buf = sdGet(&SD7);
        switch(buf)
        {
            case '1':
                val -= 1000;
                val = ValLimit(val, pwmper*(-1), pwmper);
                lldControlSetRawMotorPower(val);
                break;

            case '2':
                val += 1000;
                val = ValLimit(val, pwmper*(-1), pwmper);
                lldControlSetRawMotorPower(val);
                break;
        }
        chprintf(((BaseSequentialStream *)&SD7), "%d\r\n", val);
        time = chThdSleepUntilWindowed(time, time + MS2ST(250));
    }
}

/**
 * @brief   Test motors rotation speed
 * @note    Changing percent values of pwm dutycycle
 */
void lldTestMotorPower(void)
{
    systime_t time = chVTGetSystemTime();
    while (true)
    {
        char buf = sdGet(&SD7);
        switch(buf)
        {
            case '1':
                val -= 10;
                val = ValLimit(val, -100, 100);
                lldControlSetMotorPower(val);
                break;

            case '2':
                val += 10;
                val = ValLimit(val, -100, 100);
                lldControlSetMotorPower(val);
                break;
        }
        chprintf(((BaseSequentialStream *)&SD7), "%d\r\n", val);
        time = chThdSleepUntilWindowed(time, time + MS2ST(250));
    }
}

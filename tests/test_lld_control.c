#include <tests.h>
#include <chprintf.h>
#include <lld_control.h>

int16_t val = 0;
bool direction = 1;
uint16_t raw_delta = 1000;
uint8_t delta = 10;
uint8_t test_duty = 70;

/**
 * @brief   Test motors direction
 */
void lldTestDirectionMotorPower(void)
{
    systime_t time = chVTGetSystemTime();
    lldControlInit();
    serialStartInit();
    test_duty = ValLimit(test_duty, 0, 100);
    while (true)
    {
        char buf = sdGet(&SD7);
        switch(buf)
        {
            case '1':
                val = -test_duty;
                break;

            case '2':
                val = test_duty;
                break;
        }
        val = ValLimit(val, -100, 100);
        lldControlSetMotorPower(val);
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
    lldControlInit();
    serialStartInit();
    raw_delta = ValLimit(raw_delta, 0, pwmper);
    while (true)
    {
        char buf = sdGet(&SD7);
        switch(buf)
        {
            case '1':
                if (val == 0 && direction == 1)
                {
                    direction = 0;
                    val += raw_delta;
                }
                else if (direction == 0)
                    val += raw_delta;
                else if (direction == 1)
                    val -= raw_delta;
                break;

            case '2':
                if (val == 0 && direction == 0)
                {
                    direction = 1;
                    val += raw_delta;
                }
                else if (direction == 1)
                    val += raw_delta;
                else if (direction == 0)
                    val -= raw_delta;
                break;
        }
        val = ValLimit(val, 0, pwmper);
        lldControlSetRawMotorPower(val, direction);
        chprintf(((BaseSequentialStream *)&SD7), "%d    %d\r\n", val, direction);
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
    lldControlInit();
    serialStartInit();
    delta = ValLimit(delta, 0, 100);
    while (true)
    {
        char buf = sdGet(&SD7);
        switch(buf)
        {
            case '1':
                val -= delta;
                break;

            case '2':
                val += delta;
                break;
        }
        val = ValLimit(val, -100, 100);
        lldControlSetMotorPower(val);
        chprintf(((BaseSequentialStream *)&SD7), "%d\r\n", val);
        time = chThdSleepUntilWindowed(time, time + MS2ST(250));
    }
}

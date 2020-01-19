#include <ch.h>
#include <hal.h>
#include <lld_control.h>

static PWMConfig pwm1conf = {
    .frequency = pwmfreq,
    .period = pwmper,
    .callback = NULL,
    .channels = {
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
    },
    .cr2 = 0,
    .dier = 0
};

static const SerialConfig sd7conf = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};

/**
 * @brief          Limits input value
 * @param   val    Input value
 * @param   low    Lower limit
 * @param   high   Upper limit
 */
int64_t ValLimit(int64_t val, int64_t low, int64_t high)
{
    if (val > high)
        val = high;
    else if (val < low)
        val = low;
    return val;
}

static bool isInitialized = false;

/**
 * @brief   Initialize periphery connected to driver control
 * @note    Stable for repeated calls
 */
void lldControlInit(void)
{
    if ( isInitialized )
            return;

    palSetPadMode(GPIOE, 9, PAL_MODE_ALTERNATE(1));
    palSetPadMode(GPIOE, 11, PAL_MODE_ALTERNATE(1));
    pwmStart(&PWMD1, &pwm1conf);

    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));
    sdStart(&SD7, &sd7conf);

    isInitialized = true;
}

/**
 * @brief              Set power for motor
 * @note               Changing raw values of pwm dutycycle
 * @param   pwmWidth   Motor power value [-10000 10000]
 */
void lldControlSetRawMotorPower(int64_t pwmWidth)
{
    pwmWidth = ValLimit(pwmWidth, pwmper*(-1), pwmper);
    if (pwmWidth < 0)
    {
        pwmDisableChannel(&PWMD1, 0);
        pwmEnableChannel(&PWMD1, 1, pwmWidth*(-1));
    }
    else
    {
        pwmEnableChannel(&PWMD1, 0, pwmWidth);
        pwmDisableChannel(&PWMD1, 1);
    }
}

/**
 * @brief                Set power for motor
 * @note                 Changing percent values of pwm dutycycle
 * @param   pwmPercent   Motor power value [-100 100]
 */
void lldControlSetMotorPower(int8_t pwmPercent)
{
    pwmPercent = ValLimit(pwmPercent, -100, 100);
    if (pwmPercent < 0)
    {
        pwmDisableChannel(&PWMD1, 0);
        pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwmPercent*(-100)));
    }
    else
    {
        pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwmPercent*100));
        pwmDisableChannel(&PWMD1, 1);
    }
}

#include <common.h>
#include <lld_control.h>

#define PWM1_CH0 PAL_LINE(GPIOE, 9)
#define PWM1_CH1 PAL_LINE(GPIOE, 11)

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

static bool isInitialized = false;

/**
 * @brief   Initialize periphery connected to driver control
 * @note    Stable for repeated calls
 */
void lldControlInit(void)
{
    if (isInitialized)
            return;

    palSetLineMode(PWM1_CH0, PAL_MODE_ALTERNATE(1));
    palSetLineMode(PWM1_CH1, PAL_MODE_ALTERNATE(1));
    pwmStart(&PWMD1, &pwm1conf);

    isInitialized = true;
}

/**
 * @brief              Set power for motor
 * @note               Changing raw values of pwm dutycycle
 * @param   pwmWidth   Motor power value [0 10000]
 */
void lldControlSetRawMotorPower(int64_t pwmWidth, bool direction)
{
    pwmWidth = ValLimit(pwmWidth, 0, pwmper);
    if (direction == 0)
    {
        pwmDisableChannel(&PWMD1, 0);
        pwmEnableChannel(&PWMD1, 1, pwmWidth);
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

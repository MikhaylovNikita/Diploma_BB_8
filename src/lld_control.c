#include <common.h>
#include <lld_control.h>

#define PWM4_CH3 PAL_LINE(GPIOD, 15)
#define PWM1_CH1 PAL_LINE(GPIOE, 11)
#define PWM1_CH2 PAL_LINE(GPIOE, 13)
#define PWM1_CH3 PAL_LINE(GPIOE, 14)
#define PWM2_CH2 PAL_LINE(GPIOB, 10)
#define PWM2_CH3 PAL_LINE(GPIOB, 11)

#define MOTOR_1_FW &PWMD4, 3
#define MOTOR_1_BW &PWMD1, 1
#define MOTOR_2_FW &PWMD1, 2
#define MOTOR_2_BW &PWMD1, 3
#define MOTOR_3_FW &PWMD2, 2
#define MOTOR_3_BW &PWMD2, 3

static PWMConfig pwm1conf = {
    .frequency = pwmfreq,
    .period = pwmper,
    .callback = NULL,
    .channels = {
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}
    },
    .cr2 = 0,
    .dier = 0
};

static PWMConfig pwm2conf = {
    .frequency = pwmfreq,
    .period = pwmper,
    .callback = NULL,
    .channels = {
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}
    },
    .cr2 = 0,
    .dier = 0
};

static PWMConfig pwm4conf = {
    .frequency = pwmfreq,
    .period = pwmper,
    .callback = NULL,
    .channels = {
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}
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

    palSetLineMode(PWM4_CH3, PAL_MODE_ALTERNATE(2));
    palSetLineMode(PWM1_CH1, PAL_MODE_ALTERNATE(1));
    palSetLineMode(PWM1_CH2, PAL_MODE_ALTERNATE(1));
    palSetLineMode(PWM1_CH3, PAL_MODE_ALTERNATE(1));
    palSetLineMode(PWM2_CH2, PAL_MODE_ALTERNATE(1));
    palSetLineMode(PWM2_CH3, PAL_MODE_ALTERNATE(1));

    pwmStart(&PWMD1, &pwm1conf);
    pwmStart(&PWMD2, &pwm2conf);
    pwmStart(&PWMD4, &pwm4conf);

    pwmDisableChannel(MOTOR_1_FW);
    pwmDisableChannel(MOTOR_1_BW);
    pwmDisableChannel(MOTOR_2_FW);
    pwmDisableChannel(MOTOR_2_BW);
    pwmDisableChannel(MOTOR_3_FW);
    pwmDisableChannel(MOTOR_3_BW);

    isInitialized = true;
}

/**
 * @brief               Set power for motor
 * @note                Changing raw values of pwm dutycycle
 * @param   pwmWidth    Motor power value [0 10000]
 *          direction   Motor rotation direction
 *                      [clockwise rotation           -> 1]
 *                      [counterclockwise rotation    -> 0]
 *          motor_num   Motor number
 */
void lldControlSetRawMotorPower(int64_t pwmWidth, bool direction, uint8_t motor_num)
{
    pwmWidth = ValLimit(pwmWidth, 0, pwmper);
    switch(motor_num)
    {
        case 1:
            if (direction == 0)
            {
                pwmDisableChannel(MOTOR_1_FW);
                pwmEnableChannel(MOTOR_1_BW, pwmWidth);
            }
            else
            {
                pwmEnableChannel(MOTOR_1_FW, pwmWidth);
                pwmDisableChannel(MOTOR_1_BW);
            }
            break;
        case 2:
            if (direction == 0)
            {
                pwmDisableChannel(MOTOR_2_FW);
                pwmEnableChannel(MOTOR_2_BW, pwmWidth);
            }
            else
            {
                pwmEnableChannel(MOTOR_2_FW, pwmWidth);
                pwmDisableChannel(MOTOR_2_BW);
            }
            break;
        case 3:
            if (direction == 0)
            {
                pwmDisableChannel(MOTOR_3_FW);
                pwmEnableChannel(MOTOR_3_BW, pwmWidth);
            }
            else
            {
                pwmEnableChannel(MOTOR_3_FW, pwmWidth);
                pwmDisableChannel(MOTOR_3_BW);
            }
            break;
    }
}

/**
 * @brief                Set power for motor
 * @note                 Changing percent values of pwm dutycycle
 * @param   pwmPercent   Motor power value [-100 100]
 *          motor_num    Motor number
 */
void lldControlSetMotorPower(int8_t pwmPercent, uint8_t motor_num)
{
    pwmPercent = ValLimit(pwmPercent, -100, 100);
    switch(motor_num)
    {
        case 1:
            if (pwmPercent < 0)
            {
                pwmDisableChannel(MOTOR_1_FW);
                pwmEnableChannel(MOTOR_1_BW, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwmPercent*(-100)));
            }
            else
            {
                pwmEnableChannel(MOTOR_1_FW, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwmPercent*100));
                pwmDisableChannel(MOTOR_1_BW);
            }
            break;
        case 2:
            if (pwmPercent < 0)
            {
                pwmDisableChannel(MOTOR_2_FW);
                pwmEnableChannel(MOTOR_2_BW, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwmPercent*(-100)));
            }
            else
            {
                pwmEnableChannel(MOTOR_2_FW, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, pwmPercent*100));
                pwmDisableChannel(MOTOR_2_BW);
            }
            break;
        case 3:
            if (pwmPercent < 0)
            {
                pwmDisableChannel(MOTOR_3_FW);
                pwmEnableChannel(MOTOR_3_BW, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, pwmPercent*(-100)));
            }
            else
            {
                pwmEnableChannel(MOTOR_3_FW, PWM_PERCENTAGE_TO_WIDTH(&PWMD2, pwmPercent*100));
                pwmDisableChannel(MOTOR_3_BW);
            }
            break;
    }
}

#include <ch.h>
#include <hal.h>
#include <chprintf.h>

static PWMConfig pwmcfg = {
    .frequency = 70000,
    .period = 1000,
    .callback = NULL,
    .channels = {
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_COMPLEMENTARY_OUTPUT_ACTIVE_HIGH, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL}
    },
    .cr2 = 0,
    .dier = 0
};

static const SerialConfig sdcfg = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};

int main(void)
{
    char i = 0;
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();

    palSetPadMode(GPIOB, GPIOB_LED1, PAL_MODE_ALTERNATE(1));
    pwmStart(&PWMD1, &pwmcfg);

    sdStart(&SD7, &sdcfg);
    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));

    chprintf((BaseSequentialStream*)&SD7, "Sample text\r\n");

    while (true)
    {
        pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, i*1000));
        while (true)
        {
            pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, i*1000));
            chThdSleepMilliseconds(100);
            i++;
            chprintf((BaseSequentialStream*)&SD7, "%d\r\n", i*10);
            if(i >= 10)
            {
                i = 10;
                break;
            }
        }
        while (true)
        {
            pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, i*1000));
            chThdSleepMilliseconds(100);
            i--;
            chprintf((BaseSequentialStream*)&SD7, "%d\r\n", i*10);
            if(i <= 0)
            {
               i = 0;
               break;
            }
        }
    }
}

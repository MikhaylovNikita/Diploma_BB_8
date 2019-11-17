#include <ch.h>
#include <hal.h>
#include <chprintf.h>

uint32_t width = 0;

static void icucb(ICUDriver *icup)
{
  width = icuGetWidthX(icup);
  chprintf((BaseSequentialStream*)&SD7, "%d\r\n", width);
}

static PWMConfig pwmcfg = {
    .frequency = 10000,
    .period = 1000,
    .callback = NULL,
    .channels = {
        {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
        {.mode = PWM_OUTPUT_DISABLED, .callback = NULL},
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

static const ICUConfig icucfg = {
    .mode         = ICU_INPUT_ACTIVE_HIGH,
    .frequency    = 100000,
    .width_cb     = icucb,
    .period_cb    = NULL,
    .overflow_cb  = NULL,
    .channel      = ICU_CHANNEL_1,
    .dier         = 0
};

int main(void)
{
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chSysInit();

    pwmStart(&PWMD1, &pwmcfg);
    palSetPadMode(GPIOE, 9, PAL_MODE_ALTERNATE(1));

    sdStart(&SD7, &sdcfg);
    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));

    icuStart(&ICUD2, &icucfg);
    palSetPadMode(GPIOA, 0, PAL_MODE_ALTERNATE(1));
    icuStartCapture(&ICUD2);
    icuEnableNotifications(&ICUD2);

    char i = 0;

    while (true)
    {
        for (i = 1; i < 10; i++)
        {
            pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, i*1000));
            chThdSleepMilliseconds(100);
        }
    }
}

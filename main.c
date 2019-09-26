#include <ch.h>
#include <hal.h>

void gpt3cb(GPTDriver *gptp)
{
    palTogglePad(GPIOB, GPIOB_LED1);
    palTogglePad(GPIOB, GPIOB_LED2);
    palTogglePad(GPIOB, GPIOB_LED3);
}

GPTConfig gpt3conf =
{
  .frequency = 10000,
  .callback = gpt3cb,
  .cr2 = 0,
  .dier = 0
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

    palSetPad(GPIOB, GPIOB_LED1);
    chThdSleepMilliseconds(200);
    palClearPad(GPIOB, GPIOB_LED1);
    palSetPad(GPIOB, GPIOB_LED2);
    chThdSleepMilliseconds(200);
    palClearPad(GPIOB, GPIOB_LED2);
    palSetPad(GPIOB, GPIOB_LED3);
    chThdSleepMilliseconds(200);
    palClearPad(GPIOB, GPIOB_LED3);

    gptStart(&GPTD3, &gpt3conf);
    gptStartContinuous(&GPTD3, gpt3conf.frequency/4);

    while (true)
    {

    }
}

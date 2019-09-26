#include <ch.h>
#include <hal.h>

void gpt3cb(GPTDriver *gptp)
{
    palTogglePad(GPIOB, GPIOB_LED1);
}

static void extcbutton(EXTDriver *extp, expchannel_t channel)
{
    (void)extp;
    (void)channel;
    palTogglePad(GPIOB, GPIOB_LED2);
}

GPTConfig gpt3conf =
{
  .frequency = 10000,
  .callback = gpt3cb,
  .cr2 = 0,
  .dier = 0
};

static const EXTConfig extconf = {
  .channels =
  {
    [0]  = {EXT_CH_MODE_DISABLED, NULL},
    [1]  = {EXT_CH_MODE_DISABLED, NULL},
    [2]  = {EXT_CH_MODE_DISABLED, NULL},
    [3]  = {EXT_CH_MODE_DISABLED, NULL},
    [4]  = {EXT_CH_MODE_DISABLED, NULL},
    [5]  = {EXT_CH_MODE_DISABLED, NULL},
    [6]  = {EXT_CH_MODE_DISABLED, NULL},
    [7]  = {EXT_CH_MODE_DISABLED, NULL},
    [8]  = {EXT_CH_MODE_DISABLED, NULL},
    [9]  = {EXT_CH_MODE_DISABLED, NULL},
    [10] = {EXT_CH_MODE_DISABLED, NULL},
    [11] = {EXT_CH_MODE_DISABLED, NULL},
    [12] = {EXT_CH_MODE_DISABLED, NULL},
    [13] = {EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, extcbutton},
    [14] = {EXT_CH_MODE_DISABLED, NULL},
    [15] = {EXT_CH_MODE_DISABLED, NULL},
  }
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

    extStart (&EXTD1, &extconf);

    while (true)
    {

    }
}

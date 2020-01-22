#include <tests.h>
#include <chprintf.h>
#include <lld_encoder.h>

int32_t ticks_test = 0;
bool dir_test = 0;
int16_t revs_test = 0;

static bool serialInitialized = false;

static const SerialConfig sd7conf = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};

void serialEncoderInit(void)
{
    if (serialInitialized)
        return;

    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));
    sdStart(&SD7, &sd7conf);

    serialInitialized = true;
}

/**
 * @brief   Test encoder direction, revolutions and ticks counter value
 * @note    clockwise rotation           -> 1
 *          counterclockwise rotation    -> 0
 */
void lldTestEncoder(void)
{
    systime_t time = chVTGetSystemTime();
    lldEncoderInit();
    serialEncoderInit();
    while(true)
    {
        dir_test = lldEncoderGetDirection();
        revs_test = (int16_t)lldEncoderGetRevs();
        ticks_test = lldEncoderGetTicks();
        chprintf(((BaseSequentialStream *)&SD7), "D:%d R:%d T:%d\n\r",
                 dir_test, revs_test, ticks_test);
        time = chThdSleepUntilWindowed(time, time + MS2ST(100));
    }
}

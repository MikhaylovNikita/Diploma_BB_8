#include <tests.h>
#include <chprintf.h>
#include <lld_encoder.h>

int32_t ticks_test = 0;
bool dir_test = 0;
int16_t revs_test = 0;

void lldTestEncoder(void)
{
    systime_t time = chVTGetSystemTime();
    lldEncoderInit();
    serialStartInit();
    while(true)
    {
        dir_test = lldEncoderGetDirection();
        revs_test = (int)lldEncoderGetRevs();
        ticks_test = lldEncoderGetTicks();
        chprintf(((BaseSequentialStream *)&SD7), "D:%d R:%d T:%d\n\r", dir_test, revs_test, ticks_test);
        time = chThdSleepUntilWindowed(time, time + MS2ST(100));
    }
}

#include <ch.h>
#include <hal.h>
#include <chprintf.h>

uint32_t width_1 = 0;
uint32_t width_2 = 0;

thread_reference_t trp;

static void icucb1(ICUDriver *icup)
{
	// no need to put everything into Critical Zone 
	// better put only chThdResumeI()
    // chSysLockFromISR();
    // because you kind of interrupt the interrupt 
    // be careful with usage of Critical Zones 
    width_1 = icuGetWidthX(icup);
    chprintf((BaseSequentialStream*)&SD7, "PWM1 = %d    ", width_1);
    chSysLockFromISR();
    chThdResumeI(&trp, (msg_t)NULL);
    chSysUnlockFromISR();
}

static void icucb2(ICUDriver *icup)
{
	// here the same 
    // chSysLockFromISR();
    width_2 = icuGetWidthX(icup);
    chprintf((BaseSequentialStream*)&SD7, "PWM2 = %d\r\n", width_2);
    chSysLockFromISR();
    chThdResumeI(&trp, (msg_t)NULL);
    chSysUnlockFromISR();
}

static PWMConfig pwmcfg = {
    .frequency = 10000,
    .period = 1000,
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

static const SerialConfig sdcfg = {
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
};

static const ICUConfig icucfg1 = {
    .mode         = ICU_INPUT_ACTIVE_HIGH,
    .frequency    = 100000,
    .width_cb     = icucb1,
    .period_cb    = NULL,
    .overflow_cb  = NULL,
    .channel      = ICU_CHANNEL_1,
    .dier         = 0
};

static const ICUConfig icucfg2 = {
    .mode         = ICU_INPUT_ACTIVE_HIGH,
    .frequency    = 100000,
    .width_cb     = icucb2,
    .period_cb    = NULL,
    .overflow_cb  = NULL,
    .channel      = ICU_CHANNEL_1,
    .dier         = 0
};

// 128 - buffer size 
// if in the future you will miss data, 
// maybe you should increase the buffer size (256 || 512 etc.)
static THD_WORKING_AREA(MainThread, 128);
// it is easy to read code if working area of thread 
// and name of thread have the same part 
// for example, if thread name is MainThread, 
// working area of thread is waMainThread
static THD_FUNCTION(LED, arg)
{
	// you need to detect only resuming of callback 
	// so it is enough to put chThdSuspendTimeoutS 
	// into Critical Zone
    // chSysLock();
    (void)arg;
    msg_t msg;
    while (true)
    {
    	chSysLock();
        msg = chThdSuspendTimeoutS(&trp, MS2ST(50));
        chSysUnlock();
        if (msg == MSG_OK)
            palSetPad(GPIOB, GPIOB_LED3);
        else if (msg == MSG_TIMEOUT)
            palClearPad(GPIOB, GPIOB_LED3);
        // chSysUnlock();
    }
}

static bool isInitialized = false; 

void icuInit()
{
	// protection for repeated call of function 
	if( isInitialized )
		return;

	/*
		Add initialization of icu unit 
	*/

}

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
    palSetPadMode(GPIOE, 11, PAL_MODE_ALTERNATE(1));
    pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 3000));
    pwmEnableChannel(&PWMD1, 1, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 7000));

    sdStart(&SD7, &sdcfg);
    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));

    icuStart(&ICUD2, &icucfg1);
    palSetPadMode(GPIOA, 5, PAL_MODE_ALTERNATE(1));
    icuStartCapture(&ICUD2);
    icuEnableNotifications(&ICUD2);
    icuStart(&ICUD5, &icucfg2);
    palSetPadMode(GPIOA, 0, PAL_MODE_ALTERNATE(2));
    icuStartCapture(&ICUD5);
    icuEnableNotifications(&ICUD5);

    trp = chThdCreateStatic(MainThread, sizeof(MainThread), NORMALPRIO + 1, LED, NULL);

    while (true)
    {

    }
}

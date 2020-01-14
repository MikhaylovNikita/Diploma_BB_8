#include <ch.h>
#include <hal.h>
#include <chprintf.h>

#define ADC1_NUM_CHANNELS   1
#define ADC1_BUF_DEPTH      1

static adcsample_t samples1[ADC1_NUM_CHANNELS * ADC1_BUF_DEPTH];
static float cutoff = 0.5;
adcsample_t newsample;
adcsample_t bufsample = 0;

static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n)
{
    (void)adcp;
    (void)buffer;
    (void)n;
    chprintf((BaseSequentialStream*)&SD7, "%d\n", samples1[0]);
    newsample = bufsample * (1 - cutoff) + samples1[0] * cutoff;
    chprintf((BaseSequentialStream*)&SD7, "%d\n", newsample);
    bufsample = samples1[0];
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err)
{
    (void)adcp;
    (void)err;
    chprintf((BaseSequentialStream*)&SD7, "ERROR\r\n");
}

static const ADCConversionGroup adcgrpcfg1 =
{
    .circular     = true,                                           // working mode = looped
    .num_channels = ADC1_NUM_CHANNELS,
    .end_cb       = adccallback,
    .error_cb     = adcerrorcallback,
    .cr1          = 0,
    .cr2          = ADC_CR2_EXTEN_RISING | ADC_CR2_EXTSEL_SRC(0b1100),  // Commutated from GPT
    .smpr1        = ADC_SMPR1_SMP_AN10(ADC_SAMPLE_144),             // for AN10 - 144 samples
    .smpr2        = 0,
    .sqr1         = ADC_SQR1_NUM_CH(ADC1_NUM_CHANNELS),
    .sqr2         = 0,
    .sqr3         = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)
};

static GPTConfig gpt4cfg1 =
{
    .frequency = 100000,
    .callback  = NULL,
    .cr2       = TIM_CR2_MMS_1,
    .dier      = 0
};

static const SerialConfig sdcfg =
{
    .speed  = 115200,
    .cr1    = 0,
    .cr2    = 0,
    .cr3    = 0
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

    gptStart(&GPTD4, &gpt4cfg1);
    adcStart(&ADCD1, NULL);
    sdStart(&SD7, &sdcfg);
    palSetPadMode(GPIOE, 7, PAL_MODE_ALTERNATE(8));
    palSetPadMode(GPIOE, 8, PAL_MODE_ALTERNATE(8));
    palSetLineMode(LINE_ADC123_IN10, PAL_MODE_INPUT_ANALOG);

    adcStartConversion(&ADCD1, &adcgrpcfg1, samples1, ADC1_BUF_DEPTH);
    gptStartContinuous(&GPTD4, gpt4cfg1.frequency);

    while (true)
    {

    }
}

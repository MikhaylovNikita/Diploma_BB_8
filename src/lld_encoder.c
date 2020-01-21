#include <common.h>
#include <lld_encoder.h>

#define ENCODER_GREEN_LINE  PAL_LINE(GPIOD, 5)
#define ENCODER_WHITE_LINE  PAL_LINE(GPIOD, 4)
#define ENCODER_MAX_TICKS 360

int32_t enc_ticks = 0;
bool enc_dir = 0;
float enc_revs = 0;
static float rpm_revs = 0;
static float rpm_b = 0;
float rpm = 0;
static float tps_revs = 0;
static float tps_b = 0;
float tps = 0;
static virtual_timer_t rpm_vt;
static virtual_timer_t tps_vt;

/***    Encoder processing    ***/
static void extcb_enc(EXTDriver *extp, expchannel_t channel)
{
    (void)extp;
    (void)channel;

    /***    Count encoder ticks                     ***/
    /***    Define direction of encoder rotation:   ***/
    /***    counterclockwise -> 0                   ***/
    /***    clockwise        -> 1                   ***/
    if (palReadLine(ENCODER_GREEN_LINE) == 0)
    {
        enc_ticks --;
        enc_dir = 0;
    }
    else
    {
        enc_ticks ++;
        enc_dir = 1;
    }

    /***    Count encoder revolutions                         ***/
    /***    Reset counter when it reaches ENCODER_MAX_TICKS   ***/
    if(enc_ticks == (ENCODER_MAX_TICKS - 1))
    {
        enc_revs += 1;
        enc_ticks = 0;
    }
    else if(enc_ticks == (-ENCODER_MAX_TICKS + 1))
    {
        enc_revs -= 1;
        enc_ticks = 0;
    }
}
static bool encInitialized = false;

/**
 * @brief   Initialize periphery connected to encoder
 * @note    Stable for repeated calls
 */
void lldEncoderInit(void)
{
    if (encInitialized)
            return;

    EXTChannelConfig enc_conf = {
         .mode = EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOD,
         .cb = extcb_enc
    };

    extStartInit();
    extSetChannelMode(&EXTD1, 4, &enc_conf);

    encInitialized = true;
}

static bool rpmInitialized = false;

/**
 * @brief   Initialize virtual timer to count revolutions per minute
 * @note    Stable for repeated calls
 */
void RPMInit(void)
{
    if (rpmInitialized)
            return;

    chVTObjectInit(&rpm_vt);

    rpmInitialized = true;
}

static bool tpsInitialized = false;

/**
 * @brief   Initialize virtual timer to count ticks per second
 * @note    Stable for repeated calls
 */
void TPSInit(void)
{
    if (tpsInitialized)
        return;

    chVTObjectInit(&tps_vt);

    tpsInitialized = true;
}

/**
 * @brief   Get number of encoder ticks
 * @note    Max number of ticks is defined by ENCODER_MAX_TICKS
 * @return  Encoder ticks number depends on direction of rotation
 *          [0; ENCODER_MAX_TICKS]
 *          resets after ENCODER_MAX_TICKS
 */
int32_t lldEncoderGetTicks(void)
{
    return enc_ticks;
}

/**
 * @brief   Get direction of encoder rotation
 * @return  clockwise           -> 1
 *          counterclockwise    -> 0
 */
bool lldEncoderGetDirection(void)
{
    return enc_dir;
}

/**
 * @brief   Get number of encoder revolutions
 * @note    1 revolution = MAX_TICK_NUM ticks
 * @return  Encoder revolutions number depends on direction of rotation
 */
float lldEncoderGetRevs(void)
{
    return (enc_revs + enc_ticks / (float)ENCODER_MAX_TICKS);
}

/***    Count encoder revolutions per minute    ***/
void rpm_cb(void *r)
{
    (void)r;
    rpm_revs = lldEncoderGetRevs();
    rpm = (rpm_revs - rpm_b) * (float)600;
    rpm_b = lldEncoderGetRevs();
}

/***    Count encoder ticks per second    ***/
void tps_cb(void *t)
{
    (void)t;
    tps_revs = lldEncoderGetRevs();
    tps = (tps_revs - tps_b) * (float)ENCODER_MAX_TICKS * (float)10;
    tps_b = lldEncoderGetRevs();
}

/**
 * @brief   Get number of encoder revolutions per minute
 * @return  Encoder revolutions per minute depends on direction of rotation
 */
float lldEncoderGetRPM(void)
{
    chVTReset(&rpm_vt);
    chVTSet(&rpm_vt, MS2ST(100), rpm_cb, NULL);
    return rpm;
}

/**
 * @brief   Get number of encoder ticks per second
 * @return  Encoder ticks per second depends on direction of rotation
 */
float lldEncoderGetTPS(void)
{
    chVTReset(&tps_vt);
    chVTSet(&tps_vt, MS2ST(100), tps_cb, NULL);
    return tps;
}

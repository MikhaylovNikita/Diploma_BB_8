#include <common.h>
#include <lld_encoder.h>

#define ENCODER_GREEN_LINE  PAL_LINE(GPIOG, 2)
#define ENCODER_WHITE_LINE  PAL_LINE(GPIOG, 3)
#define ENCODER_MAX_TICKS 360

int32_t enc_ticks = 0;
bool enc_dir = 0;
float enc_revs = 0;

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

static bool isInitialized = false;

/**
 * @brief   Initialize periphery connected to encoder
 * @note    Stable for repeated calls
 */
void lldEncoderInit(void)
{
    if (isInitialized)
            return;

    EXTChannelConfig enc_conf = {
         .mode = EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOG,
         .cb = extcb_enc
    };

    extStartInit();
    extSetChannelMode(&EXTD1, 3, &enc_conf);

    isInitialized = true;
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

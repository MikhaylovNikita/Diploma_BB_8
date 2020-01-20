#include <common.h>
#include <lld_encoder.h>

#define ENCODER_GREEN_LINE  PAL_LINE(GPIOG, 2)
#define ENCODER_WHITE_LINE  PAL_LINE(GPIOG, 3)
#define ENCODER_MAX_TICKS 360

int32_t enc_ticks = 0;
bool enc_dir = 0;
float enc_revs = 0;

static void extcb_enc(EXTDriver *extp, expchannel_t channel)
{
    (void)extp;
    (void)channel;

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

int32_t lldEncoderGetTicks(void)
{
    return enc_ticks;
}

bool lldEncoderGetDirection(void)
{
    return enc_dir;
}

float lldEncoderGetRevs(void)
{
    return (enc_revs + enc_ticks / (float)ENCODER_MAX_TICKS);
}

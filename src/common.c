#include <common.h>

static bool extInitialized = false;

void extStartInit(void)
{
    if (extInitialized)
            return;

    static const EXTConfig extcfg = {
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
        [13] = {EXT_CH_MODE_DISABLED, NULL},
        [14] = {EXT_CH_MODE_DISABLED, NULL},
        [15] = {EXT_CH_MODE_DISABLED, NULL},
      }
    };
    extStart(&EXTD1, &extcfg);

    extInitialized = true;
}

/**
 * @brief          Limits input value
 * @param   val    Input value
 * @param   low    Lower limit
 * @param   high   Upper limit
 */
int64_t ValLimit(int64_t val, int64_t low, int64_t high)
{
    if (val > high)
        val = high;
    else if (val < low)
        val = low;
    return val;
}

#include <common.h>
#include <odometry.h>

static float RPP_revs = 0;
static float RPP_b = 0;
float RPP = 0;
float RPP_out = 0;
static virtual_timer_t odo_vt;

static bool odoInitialized = false;

/**
 * @brief   Initialize encoder and virtual timer to count encoder revolutions
 * @note    Stable for repeated calls
 */
void odometryInit(void)
{
    if (odoInitialized)
            return;

    chVTObjectInit(&odo_vt);
    lldEncoderInit();

    odoInitialized = true;
}

/***    Count encoder revolutions per virtual timer period    ***/
void odo_cb(void *r)
{
    (void)r;
    RPP_revs = lldEncoderGetRevs();
    RPP = (RPP_revs - RPP_b);
    RPP_b = lldEncoderGetRevs();
}

/**
 * @brief   Get number of encoder revolutions per virtual timer period
 * @return  Encoder revolutions per virtual timer period depends on
 *          direction of rotation
 */
float odometryGetMotorSpeed(odometrySpeedUnit_t unit)
{
    chVTReset(&odo_vt);
    chVTSet(&odo_vt, MS2ST(VT_PERIOD_MS), odo_cb, NULL);
    RPP_out = RPP * (float)unit;
    return RPP_out;
}

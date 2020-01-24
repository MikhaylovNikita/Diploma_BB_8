#ifndef INCLUDE_ODOMETRY_H_
#define INCLUDE_ODOMETRY_H_

#include <lld_encoder.h>

#define VT_PERIOD_MS 10

typedef enum {
    RPS = 1000 / VT_PERIOD_MS,
    RPM = 60000 / VT_PERIOD_MS
} odometrySpeedUnit_t;

/**
 * @brief   Initialize encoder and virtual timer to count encoder revolutions
 * @note    Stable for repeated calls
 */
void odometryInit(void);

/**
 * @brief   Get number of encoder revolutions per virtual timer period
 * @return  Encoder revolutions per virtual timer period depends on
 *          direction of rotation
 */
float odometryGetMotorSpeed(odometrySpeedUnit_t unit);

#endif /* INCLUDE_ODOMETRY_H_ */

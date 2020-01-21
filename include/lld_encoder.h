#ifndef INCLUDE_LLD_ENCODER_H_
#define INCLUDE_LLD_ENCODER_H_

/**
 * @brief   Initialize periphery connected to encoder
 * @note    Stable for repeated calls
 */
void lldEncoderInit(void);

/**
 * @brief   Initialize virtual timer to count revolutions per minute
 * @note    Stable for repeated calls
 */
void RPMInit(void);

/**
 * @brief   Initialize virtual timer to count ticks per second
 * @note    Stable for repeated calls
 */
void TPSInit(void);

/**
 * @brief   Get number of encoder ticks
 * @note    Max number of ticks is defined by ENCODER_MAX_TICKS
 * @return  Encoder ticks number depends on direction of rotation
 *          [0; ENCODER_MAX_TICKS]
 *          resets after ENCODER_MAX_TICKS
 */
int32_t lldEncoderGetTicks(void);

/**
 * @brief   Get direction of encoder rotation
 * @return  counterclockwise    -> 0
 *          clockwise           -> 1
 */
bool lldEncoderGetDirection(void);

/**
 * @brief   Get number of encoder revolutions
 * @note    1 revolution = MAX_TICK_NUM ticks
 * @return  Encoder revolutions number depends on direction of rotation
 */
float lldEncoderGetRevs(void);

/**
 * @brief   Get number of encoder revolutions per minute
 * @return  Encoder revolutions per minute depends on direction of rotation
 */
float lldEncoderGetRPM(void);

/**
 * @brief   Get number of encoder ticks per second
 * @return  Encoder ticks per second depends on direction of rotation
 */
float lldEncoderGetTPS(void);

#endif /* INCLUDE_LLD_ENCODER_H_ */

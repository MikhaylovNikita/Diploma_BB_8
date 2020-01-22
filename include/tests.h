#ifndef INCLUDE_TESTS_H_
#define INCLUDE_TESTS_H_

#include <common.h>

/**
 * @brief   Test motors direction
 */
void lldTestDirectionMotorPower(void);

/**
 * @brief   Test motors rotation speed
 * @note    Changing raw values of pwm dutycycle
 */
void lldTestRawMotorPower(void);

/**
 * @brief   Test motors rotation speed
 * @note    Changing percent values of pwm dutycycle
 */
void lldTestMotorPower(void);

/**
 * @brief   Test encoder direction, revolutions and ticks counter value
 * @note    clockwise rotation           -> 1
 *          counterclockwise rotation    -> 0
 */
void lldTestEncoder(void);

/**
 * @brief   Test motors rotation speed in revolutions per unit
 * @note    Revs value receives from encoder
 */
void odometryTestMotorSpeed(void);

#endif /* INCLUDE_TESTS_H_ */

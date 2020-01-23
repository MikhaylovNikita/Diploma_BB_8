#ifndef INCLUDE_TESTS_H_
#define INCLUDE_TESTS_H_

#include <common.h>

/**
 * @brief   Test motors direction
 * @param   motor_num   Motor number
 */
void lldTestDirectionMotorPower(uint8_t motor_num);

/**
 * @brief   Test motors rotation speed
 * @note    Changing raw values of pwm dutycycle
 * @param   motor_num   Motor number
 */
void lldTestRawMotorPower(uint8_t motor_num);

/**
 * @brief   Test motors rotation speed
 * @note    Changing percent values of pwm dutycycle
 * @param   motor_num   Motor number
 */
void lldTestMotorPower(uint8_t motor_num);

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

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

void lldTestEncoder(void);

#endif /* INCLUDE_TESTS_H_ */
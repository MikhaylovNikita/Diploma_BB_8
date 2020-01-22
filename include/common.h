#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <ch.h>
#include <hal.h>

#define MOTOR_DIR_TEST_ROUTINE 1
#define MOTOR_POWER_TEST_ROUTINE 2
#define MOTOR_RAW_POWER_TEST_ROUTINE 3
#define ENCODER_TEST_ROUTINE 4
#define ODOMETRY_TEST_ROUTINE 5

#define TEST_ROUTINE ODOMETRY_TEST_ROUTINE

/**
 * @brief   Initialize EXT driver
 * @note    Safe for repeated calls
 * @note    Must be called before configuring
 */
void extStartInit(void);

/**
 * @brief          Limits input value
 * @param   val    Input value
 * @param   low    Lower limit
 * @param   high   Upper limit
 */
int64_t ValLimit(int64_t val, int64_t low, int64_t high);

#endif /* INCLUDE_COMMON_H_ */

#ifndef INCLUDE_LLD_CONTROL_H_
#define INCLUDE_LLD_CONTROL_H_

#define pwmfreq 2000000
#define pwmper 10000

/**
 * @brief   Initialize periphery connected to driver control
 * @note    Stable for repeated calls
 */
void lldControlInit(void);

/**
 * @brief               Set power for motor
 * @note                Changing raw values of pwm dutycycle
 * @param   pwmWidth    Motor power value [-10000 10000]
 *          direction   Motor rotation direction
 *                      [clockwise rotation           -> 1]
 *                      [counterclockwise rotation    -> 0]
 *          motor_num   Motor number
 */
void lldControlSetRawMotorPower(int64_t pwmWidth, bool direction, uint8_t motor_num);

/**
 * @brief                Set power for motor
 * @note                 Changing percent values of pwm dutycycle
 * @param   pwmPercent   Motor power value [-100 100]
 *          motor_num    Motor number
 */
void lldControlSetMotorPower(int8_t pwmPercent, uint8_t motor_num);

#endif /* INCLUDE_LLD_CONTROL_H_ */

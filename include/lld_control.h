#ifndef INCLUDE_LLD_CONTROL_H_
#define INCLUDE_LLD_CONTROL_H_

#define pwmfreq 500000
#define pwmper 10000

/**
 * @brief          Limits input value
 * @param   val    Input value
 * @param   low    Lower limit
 * @param   high   Upper limit
 */
int64_t ValLimit(int64_t val, int64_t low, int64_t high);

/**
 * @brief   Initialize periphery connected to driver control
 * @note    Stable for repeated calls
 */
void lldControlInit(void);

/**
 * @brief              Set power for motor
 * @note               Changing raw values of pwm dutycycle
 * @param   pwmWidth   Motor power value [-10000 10000]
 */
void lldControlSetRawMotorPower(int64_t pwmWidth);

/**
 * @brief                Set power for motor
 * @note                 Changing percent values of pwm dutycycle
 * @param   pwmPercent   Motor power value [-100 100]
 */
void lldControlSetMotorPower(int8_t pwmPercent);

#endif /* INCLUDE_LLD_CONTROL_H_ */

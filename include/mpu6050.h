#ifndef INCLUDE_MPU6050_H_
#define INCLUDE_MPU6050_H_

/**
 * @brief   Initialize I2C and setup MPU6050 gyroscope
 * @note    Stable for repeated calls
 */
void MPU6050Init(void);

/**
 * @brief    Get values of angle, temperature and acceleration from MPU6050
 * @param    d   Data type
 *           0   -> x-axis angle
 *           1   -> y-axis angle
 *           2   -> z-axis angle
 *           3   -> temperature
 *           4   -> x-axis acceleration
 *           5   -> y-axis acceleration
 *           6   -> z-axis acceleration
 * @return   Raw value of chosen data
 */
int16_t MPU6050GetData(uint8_t d);

#endif /* INCLUDE_MPU6050_H_ */

#include <common.h>
#include <mpu6050.h>

#define MPU6050_ADDR 0x68

uint8_t i = 0;
uint8_t rxbuf[14];
uint8_t txbuf[14];
static int16_t mpu_data[7];

static const I2CConfig i2c1conf = {
  STM32_TIMINGR_PRESC(15U) |
  STM32_TIMINGR_SCLDEL(4U) | STM32_TIMINGR_SDADEL(2U) |
  STM32_TIMINGR_SCLH(15U)  | STM32_TIMINGR_SCLL(21U),
  0,
  0
};

static bool mpuInitialized = false;

/**
 * @brief   Initialize I2C and setup MPU6050 gyroscope
 * @note    Stable for repeated calls
 */
void MPU6050Init(void)
{
    if (mpuInitialized)
        return;

    i2cInit();
    i2cObjectInit(&I2CD1);
    i2cStart(&I2CD1, &i2c1conf);

    palSetLineMode(LINE_I2C1_SCL, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
    palSetLineMode(LINE_I2C1_SDA, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);

    /***    MPU6050 Setup    ***/
    txbuf[0] = 0x6B;    // Power Management 1;
    txbuf[1] = 0x00;    // Internal 8MHz
    i2cMasterTransmit(&I2CD1, MPU6050_ADDR, txbuf, 2, rxbuf, 0);

    txbuf[0] = 0x1B;    // Gyro Config;
    txbuf[1] = 0x00;    // 250 deg/s
    i2cMasterTransmit(&I2CD1, MPU6050_ADDR, txbuf, 2, rxbuf, 0);

    txbuf[0] = 0x1C;    // Accel Config;
    txbuf[1] = 0x00;    // 2g
    i2cMasterTransmit(&I2CD1, MPU6050_ADDR, txbuf, 2, rxbuf, 0);

    txbuf[0] = 0x19;    // Sample Rate Divider;
    txbuf[1] = 0x09;
    i2cMasterTransmit(&I2CD1, MPU6050_ADDR, txbuf, 2, rxbuf, 0);

    mpuInitialized = true;
}

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
int16_t MPU6050GetData(uint8_t d)
{
    txbuf[0] = 0x3B;
    for(i = 0; i < 13; i++) rxbuf[i] = 0;
    i2cMasterTransmit(&I2CD1, MPU6050_ADDR, txbuf, 1, rxbuf, 14);

    mpu_data[0] = (rxbuf[0] << 8) + rxbuf[1];
    mpu_data[1] = (rxbuf[2] << 8) + rxbuf[3];
    mpu_data[2] = (rxbuf[4] << 8) + rxbuf[5];
    mpu_data[3] = (rxbuf[6] << 8) + rxbuf[7];
    mpu_data[4] = (rxbuf[8] << 8) + rxbuf[9];
    mpu_data[5] = (rxbuf[10] << 8) + rxbuf[11];
    mpu_data[6] = (rxbuf[12] << 8) + rxbuf[13];

    return mpu_data[d];
}

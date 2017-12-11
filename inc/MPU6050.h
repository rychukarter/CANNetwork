/*
 * MPU6050.h
 *
 *  Created on: 1 mar 2016
 *      Author: Karol
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include <stdint.h>

#define MPU_WHO_AM_I        0x75
#define MPU_CONFIG          0x1A
#define MPU_USER_CTRL       0x6A
#define MPU_PWR_MGMT   	   	0x6B
#define MPU_SMPLRT_DIV	    0x19
#define MPU_GYRO_CONFIG     0x1B
#define MPU_ACCEL_CONFIG    0x1C
#define MPU_INT_PIN_CFG     0x37
#define MPU_ACCEL_XOUT_H    0x3B
#define MPU_ACCEL_XOUT_L    0x3C
#define MPU_ACCEL_YOUT_H    0x3D
#define MPU_ACCEL_YOUT_L    0x3E
#define MPU_ACCEL_ZOUT_H    0x3F
#define MPU_ACCEL_ZOUT_L    0x40
#define MPU_TEMP_OUT_H      0x41
#define MPU_TEMP_OUT_L      0x42
#define MPU_FIFO_EN			0x23
#define MPU_FIFO_R_W		0x74

extern void mpu_set_reg(uint8_t reg);//ustawianie adresu rejestru
extern void mpu_write(uint8_t reg, const void* data, int size);//zapis w trybie burst
extern void mpu_read(uint8_t reg, void* data, int size);//odczyt w trybie burst
extern void mpu_write_reg(uint8_t reg, uint8_t value);//zapis bajta, wygodne dla rejestrow
extern uint8_t mpu_read_reg(uint8_t reg);//odczyt bajta
extern int16_t mpu_read_value(uint8_t reg);//odczyt 2 bajtow - odczytow z czujnikow
extern void mpu_read_v(uint8_t reg, void* data, int size);//funkcja pomocnicza, aby odczytywac 2 bajty w odpowiedniej kolejnosci
extern int MCUConf(void);
#endif /* MPU6050_H_ */

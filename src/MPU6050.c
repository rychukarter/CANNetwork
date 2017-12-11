#include "stm32f10x.h"
#include "MPU6050.h"

#define MPU6050_ADDR ((0x68 & 0x7f)<<1)//adres urzadzenia przesuniety o bit w lewa

void mpu_set_reg(uint8_t reg) {
	I2C_GenerateSTART(I2C1, ENABLE); //sygnal start
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
		;

	I2C_Send7bitAddress(I2C1, MPU6050_ADDR, I2C_Direction_Transmitter); //ustawienie adresu urzadzenia i kierunku transmisji
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)
			!= SUCCESS)
		;

	I2C_SendData(I2C1, reg); //wyslanie adresu rejestru
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS)
		;
}

void mpu_write(uint8_t reg, const void* data, int size) {
	int i;
	const uint8_t* buffer = (uint8_t*) data;

	mpu_set_reg(reg); //ustawienie adresu rejestru
	/*
	 * wysylanie w trybie burst, kazdego kolejnego bajta
	 */
	for (i = 0; i < size; i++) {
		I2C_SendData(I2C1, buffer[i]);
		while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING)
				!= SUCCESS)
			;
	}

	I2C_GenerateSTOP(I2C1, ENABLE); //sygnal stop
}

void mpu_write_reg(uint8_t reg, uint8_t value) {
	mpu_write(reg, &value, sizeof(value));
}

void mpu_read(uint8_t reg, void* data, int size) {
	int i;
	uint8_t* buffer = (uint8_t*) data;

	mpu_set_reg(reg); //ustawienie adresu rejestru do odczytu

	I2C_GenerateSTART(I2C1, ENABLE); //sygnal start
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
		;
	I2C_AcknowledgeConfig(I2C1, ENABLE); //wysylanie komunikatow ACK

	I2C_Send7bitAddress(I2C1, MPU6050_ADDR, I2C_Direction_Receiver); //ustawienie adresu i kierunku transmisji
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)
			!= SUCCESS)
		;

	for (i = 0; i < size - 1; i++) {
		while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
			;
		buffer[i] = I2C_ReceiveData(I2C1); //odbior kolejnych bajtow z potwierdzeniem
	}
	I2C_AcknowledgeConfig(I2C1, DISABLE); //ostatni bajt, komunikat NACK
	I2C_GenerateSTOP(I2C1, ENABLE); //zadanie konca transmisji
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
		;
	buffer[i] = I2C_ReceiveData(I2C1); //odebranie ostatniej ramki(z NACK)
}

void mpu_read_v(uint8_t reg, void* data, int size) {

	uint8_t* buffer = (uint8_t*) data;

	mpu_set_reg(reg);

	I2C_GenerateSTART(I2C1, ENABLE);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
		;
	I2C_AcknowledgeConfig(I2C1, ENABLE);

	I2C_Send7bitAddress(I2C1, MPU6050_ADDR, I2C_Direction_Receiver);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)
			!= SUCCESS)
		;

	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
		;
	buffer[1] = I2C_ReceiveData(I2C1);

	I2C_AcknowledgeConfig(I2C1, DISABLE);
	I2C_GenerateSTOP(I2C1, ENABLE);
	while (I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
		;
	buffer[0] = I2C_ReceiveData(I2C1);
}

uint8_t mpu_read_reg(uint8_t reg) {
	uint8_t value = 0;
	mpu_read(reg, &value, sizeof(value));
	return value;
}

int16_t mpu_read_value(uint8_t reg) {
	int16_t value = 0;
	mpu_read_v(reg, &value, sizeof(value));
	return value;
}

int MCUConf(void) {
	I2C_InitTypeDef i2c;
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Mode = GPIO_Mode_AF_OD;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);

	I2C_StructInit(&i2c);
	i2c.I2C_Mode = I2C_Mode_I2C;
	i2c.I2C_ClockSpeed = 50000;
	I2C_Init(I2C1, &i2c);
	I2C_Cmd(I2C1, ENABLE);
	uint8_t who_am_i = 0;
	mpu_read(0x75, &who_am_i, sizeof(who_am_i));
	if (who_am_i != 0x68) {
		return -1;
	}
	mpu_write_reg(MPU_PWR_MGMT, 0x00);
	mpu_write_reg(MPU_USER_CTRL, 0x44);
	mpu_write_reg(MPU_SMPLRT_DIV, 0);
	mpu_write_reg(MPU_ACCEL_CONFIG, 0x00);
	mpu_write_reg(MPU_FIFO_EN, 0x80);
	return 0;

}

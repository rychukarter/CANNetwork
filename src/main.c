/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f10x.h"
#include "stm32f1xx_nucleo.h"
#include "SPI_MSD_Driver.h"
#include "MPU6050.h"
#include "ff.h"
#include "other.h"
#include "can.h"
#include "SD.h"
#include <stdio.h>
#include <string.h>

FATFS fs; /* Work area (file system object) for logical drive */
FIL fsrc; /* file objects */
FRESULT res;
UINT br;
volatile int mode = 0;

int main(void) {

	char sd_buff[100];
	int16_t temp_r, a_x, a_y, a_z;
	float temp, x, y, z;
	int i = 0;
	CanRxMsg r_message;
	r_message.StdId = 0x00;
	r_message.IDE = CAN_ID_STD;
	r_message.DLC = 8;
	while (i < 8) {
		r_message.Data[i] = 0x00;
		i++;
	}

	ClockConf();
	UartConf();
	CanConf();
	ButtonNvicConf();
	CanNvicConf();
	LedConf();

	while (1) {
		Delay(0x0000ff);
		if ((mode > 0) && CAN_MessagePending(CAN1, CAN_FIFO0) >= 1) {
			CAN_Receive(CAN1, CAN_FIFO0, &r_message);
			a_x = ((int16_t)r_message.Data[1] << 8) | r_message.Data[0];
			a_y = ((int16_t)r_message.Data[3] << 8) | r_message.Data[2];
			a_z = ((int16_t)r_message.Data[5] << 8) | r_message.Data[4];
			temp_r = ((int16_t)r_message.Data[7] << 8) | r_message.Data[6];

			temp = (temp_r / 340.00f) + 36.53f;
			x = a_x * 2.0f / 32678.0f;
			y = a_y * 2.0f / 32678.0f;
			z = a_z * 2.0f / 32678.0f;

			sprintf(sd_buff, "Temp = %0.2f,   X = %.2f   Y = %.2f   Z = %.2f\n", temp, x, y, z);
			printf("%s", sd_buff);
		}
		Delay(0x0000ff);
	}
}

void EXTI15_10_IRQHandler() {
	if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
		if (mode == 0)
			mode++;
		else
			mode = 0;
		if (mode == 0)
			printf("***Receiving OFF***\n");
		else if (mode == 1)
			printf("***Receiving ON***\n");
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}

void CAN1_RX1_IRQHandler(void) {
	CanRxMsg RxMessage;
	if (CAN_GetITStatus(CAN1, CAN_IT_FMP0)) {
		CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	}
}

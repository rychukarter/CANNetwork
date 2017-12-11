/*
 * other.h
 *
 *  Created on: 14 cze 2016
 *      Author: Karol
 */

#ifndef OTHER_H_
#define OTHER_H_

extern void UartConf(void);
extern void LedConf(void);
extern int ClockConf(void);
extern void send_char(char c);
extern void Delay(uint32_t nCount);
extern void ButtonNvicConf(void);
#endif /* OTHER_H_ */

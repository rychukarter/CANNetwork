/*
 * can.h
 *
 *  Created on: 14 cze 2016
 *      Author: Karol
 */

#ifndef CAN_H_
#define CAN_H_

extern void CanConf(void);
extern void CanNvicConf(void);
extern void CanSendMessage(CanTxMsg *message);
#endif /* CAN_H_ */

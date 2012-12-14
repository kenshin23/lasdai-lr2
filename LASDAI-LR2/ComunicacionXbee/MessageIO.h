/*
 * MessageIO.h
 *
 *  Created on: 06/12/2012
 *      Author: julian
 */

#ifndef MESSAGEIO_H_
#define MESSAGEIO_H_

#include <XBee.h>

int xbeeInput();

int MsgInit(const char *port, speed_t speed);

void MsgExit();

int MsgInput(Message msg);

int MsgOutput(Message msg);

float deSerializeFloat(uint8_t *buf);

void serializeFloat(uint8_t *buf, float value);

int deSerializeInt(uint8_t *buf);

void serializeInt(uint8_t *buf, int value);

short int deSerializeShort(uint8_t *buf);

void serializeShort(uint8_t *buf, short int value);

double deSerializeDouble(uint8_t *buf);

void serializeDouble(uint8_t *buf, double value);



#endif /* MESSAGEIO_H_ */

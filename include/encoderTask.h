/*
 * encoderTask.h
 *
 *  Created on: Feb 9, 2016
 *      Author: Aeites
 */

#ifndef ENCODERTASK_H_
#define ENCODERTASK_H_

#include <API.h>

Encoder encoders[4];
int DELAY_TIME = 10;
void setupEncoder(Encoder encoder, int channel);
void resetEncoders();
int getSensorValue(int channel);
void beginEncoderTask();

int leftEncoderSpeed = 0;
int rightEncoderSpeed = 0;

int getLeftSpeed();
int getRightSpeed();
void leftSpeedTask();
void rightSpeedTask();

TaskHandle speedHandleLeft;
TaskHandle speedHandleRight;

#endif /* ENCODERTASK_H_ */

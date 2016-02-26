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

float leftEncoderSpeed = 0;
float rightEncoderSpeed = 0;
float CONVERT_TO_RPM = 60*1000/360;
float getLeftSpeed();
float getRightSpeed();
void leftSpeedTask();
void rightSpeedTask();

TaskHandle speedHandleLeft;
TaskHandle speedHandleRight;

#endif /* ENCODERTASK_H_ */

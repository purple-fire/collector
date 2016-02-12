/*
 * encoderTask.c
 *
 *  Created on: Feb 9, 2016
 *      Author: Aeites
 */

#include "encoderTask.h"


void setupEncoder(Encoder encoder, int channel){
	encoders[channel-1] = encoder;
}

void resetEncoders(){
	for (int i = 0; i < 2; i++)
	{
		encoderReset(encoders[i]);
	}
}

void beginEncoderTask(){
	speedHandleLeft = taskRunLoop(leftSpeedTask, 10);
	speedHandleRight= taskRunLoop(rightSpeedTask, 10);
	print("Beginning Encoder Task");
}

int getLeftSpeed(){
	return abs(leftEncoderSpeed);
}
int getRightSpeed(){
	return abs(rightEncoderSpeed);
}

int getSensorValue(int channel){
	return encoderGet(encoders[channel-1]);
}

void leftSpeedTask(){
	encoderReset(encoders[0]);
	for (int i = 1; i < 500; i++){
		leftEncoderSpeed = getSensorValue(1) / i;
		delay(1);
	}
}

void rightSpeedTask(){
	encoderReset(encoders[1]);
	for (int i = 1; i < 500; i++){
		rightEncoderSpeed = getSensorValue(2) / i;
		delay(1);
	}
}

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

float getLeftSpeed(){
	return abs(leftEncoderSpeed);
}
float getRightSpeed(){
	return abs(rightEncoderSpeed);
}

int getSensorValue(int channel){
	return encoderGet(encoders[channel-1]);
}

//Encoder tick speed per 1ms
void leftSpeedTask(){
	encoderReset(encoders[0]);
	for (float i = 1; i < 250; i++){
		leftEncoderSpeed = (float) getSensorValue(1) / i * CONVERT_TO_RPM;
		delay(1);
	}
}

void rightSpeedTask(){
	encoderReset(encoders[1]);
	for (float i = 1; i < 250; i++){
		rightEncoderSpeed = (float) getSensorValue(2) / i * CONVERT_TO_RPM;
		delay(1);
	}
}

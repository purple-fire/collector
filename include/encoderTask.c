/*
 * encoderTask.c
 *
 *  Created on: Feb 9, 2016
 *      Author: Aeites
 */

#include "encoderTask.h"


void setupEncoder(Encoder encoder, int index){
	encoders[index] = encoder;
}

void resetEncoders(){
	for (int i = 0; i < 4; i++)
	{
		encoderReset(encoders[i]);
	}
}

void beginEncoderResetTask(){
	encoderResetTask = taskRunLoop(resetEncoders, 100);
}

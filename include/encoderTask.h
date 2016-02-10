/*
 * encoderTask.h
 *
 *  Created on: Feb 9, 2016
 *      Author: Aeites
 */

#ifndef ENCODERTASK_H_
#define ENCODERTASK_H_



#endif /* ENCODERTASK_H_ */
#include <API.h>

Encoder encoders[4];
void setupEncoder(Encoder encoder, int index);
void resetEncoders();
void beginEncoderResetTask();

TaskHandle encoderResetTask;


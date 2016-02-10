/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

//#include "main.h"
#include "init.c"
#include "motorControl.c"
#include <Math.h>
#include "encoderTask.c"

const int MAX_FLYWHEEL_SPEED = 127;
const int MAX_PICKUP_SPEED = 127;
const int MAX_RELEASE_SPEED = -127;

const int LEFT_UP_DRIVE = 2;
const int LEFT_DOWN_DRIVE = 3;

const int RIGHT_UP_DRIVE = 4;
const int RIGHT_DOWN_DRIVE = 5;

const int RIGHT_FLY_BOTTOM = 6;
const int RIGHT_FLY_TOP = 7;
const int LEFT_FLY_BOTTOM = 8;
const int LEFT_FLY_TOP = 9;

const int PICKUP_BELT = 10;

int modFlywheelSpeed;



// Debug mode for testing the accuracy of the encoders and their values
void debugMode(){
	bool switch3 = false;
	modFlywheelSpeed = MAX_FLYWHEEL_SPEED;

	setMotorReversed(LEFT_UP_DRIVE, true);
	setMotorReversed(LEFT_DOWN_DRIVE, true);

	setMotorReversed(LEFT_FLY_BOTTOM, true);
	setMotorReversed(RIGHT_FLY_TOP, true);

	setMotorToRamp(LEFT_FLY_TOP, true);
	setMotorToRamp(LEFT_FLY_BOTTOM, true);
	setMotorToRamp(RIGHT_FLY_TOP, true);
	setMotorToRamp(RIGHT_FLY_BOTTOM, true);

	setupEncoder(LFlywheel, 1);
	setupEncoder(RFlywheel, 2);

	beginRampMotorsTask();
	beginEncoderResetTask();

	while (1) {
		if (digitalRead(1) == LOW)
			modFlywheelSpeed = MAX_FLYWHEEL_SPEED;
		if (digitalRead(2) == LOW)
			modFlywheelSpeed = 65;

		// Flipping the value of switch bool
		if(digitalRead(3) == LOW)
			switch3 = !switch3;

		// If switch3 is active, turn flywheels, if not turn them off
		if (switch3)
			rampMotorsUp(modFlywheelSpeed);
		else
			rampMotorsDown(0);

		printf("%d \n", encoderGet(LFlywheel));
		printf("%d \n", encoderGet(RFlywheel));

		delay(20);
	}
}

// Original Operational control mode
void opMode(){
	modFlywheelSpeed = MAX_FLYWHEEL_SPEED;

	setMotorReversed(LEFT_UP_DRIVE, true);
	setMotorReversed(LEFT_DOWN_DRIVE, true);

	setMotorReversed(LEFT_FLY_BOTTOM, true);
	setMotorReversed(RIGHT_FLY_TOP, true);

	setMotorToRamp(LEFT_FLY_TOP, true);
	setMotorToRamp(LEFT_FLY_BOTTOM, true);
	setMotorToRamp(RIGHT_FLY_TOP, true);
	setMotorToRamp(RIGHT_FLY_BOTTOM, true);

	beginRampMotorsTask();

	while (1) {
		int button5U = joystickGetDigital(1,5,JOY_UP);
		int button6U = joystickGetDigital(1,6,JOY_UP);
		int button6D = joystickGetDigital(1,6,JOY_DOWN);

		int button7U = joystickGetDigital(1,7,JOY_UP);
		int button7D = joystickGetDigital(1,7,JOY_DOWN);

		int leftStick = joystickGetAnalog(1, 3);
		int rightStick = joystickGetAnalog(1, 2);

		setMotorSpeed(LEFT_UP_DRIVE, leftStick);
		setMotorSpeed(LEFT_DOWN_DRIVE, leftStick);

		setMotorSpeed(RIGHT_UP_DRIVE, rightStick);
		setMotorSpeed(RIGHT_DOWN_DRIVE, rightStick);

		if (button6U)
			setMotorSpeed(PICKUP_BELT, -MAX_PICKUP_SPEED);
		else if (button6D)
			setMotorSpeed(PICKUP_BELT, MAX_PICKUP_SPEED);
		else
			setMotorSpeed(PICKUP_BELT, 0);

		if (button7U)
			modFlywheelSpeed = MAX_FLYWHEEL_SPEED;
		if (button7D)
			modFlywheelSpeed = 65;

		if(button5U){
			digitalWrite(1, LOW);
			rampMotorsUp(modFlywheelSpeed);
		}
		else{
			rampMotorsDown(0);
		}

		delay(20);
	}
}

void operatorControl() {
	//debugMode();
	//opMode();
}


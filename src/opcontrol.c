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

#include "main.h"
#include "motorControl.c"
#include <Math.h>

//const int MAX_FLYWHEEL_SPEED = 127;
const int MAX_FLYWHEEL_SPEED = 10;
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
Encoder LFlywheel;
Encoder RFlywheel;

void initializeIO() {
	pinMode(1, INPUT);
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);
}

void initialize() {
	LFlywheel = encoderInit(5, 6, false);
	RFlywheel = encoderInit(7, 8, true);
	modFlywheelSpeed = 1250;

	setMotorReversed(LEFT_UP_DRIVE, true);
	setMotorReversed(LEFT_DOWN_DRIVE, true);

	setMotorReversed(LEFT_FLY_BOTTOM, true);
	setMotorReversed(RIGHT_FLY_TOP, true);

	setLeftFlywheelMotor(LEFT_FLY_TOP, true);
	setLeftFlywheelMotor(LEFT_FLY_BOTTOM, true);
	setRightFlywheelMotor(RIGHT_FLY_TOP, true);
	setRightFlywheelMotor(RIGHT_FLY_BOTTOM, true);
}

void opMode() {


	setupEncoder(LFlywheel, 1);
	setupEncoder(RFlywheel, 2);

	beginEncoderTask();
	beginFlywheelControlTask();

	while (1) {

		int button5U = joystickGetDigital(1, 5, JOY_UP);
		int button6U = joystickGetDigital(1, 6, JOY_UP);
		int button6D = joystickGetDigital(1, 6, JOY_DOWN);

		int button7U = joystickGetDigital(1, 7, JOY_UP);
		int button7D = joystickGetDigital(1, 7, JOY_DOWN);

		int leftStick = joystickGetAnalog(1, 3);
		int rightStick = joystickGetAnalog(1, 2);

		setMotorSpeed(LEFT_UP_DRIVE, leftStick);
		setMotorSpeed(LEFT_DOWN_DRIVE, leftStick);

		setMotorSpeed(RIGHT_UP_DRIVE, rightStick);
		setMotorSpeed(RIGHT_DOWN_DRIVE, rightStick);

		// If switch3 is active, turn flywheels, if not turn them off
		if (digitalRead(3) == LOW) {
			setFlywheelTarget(modFlywheelSpeed);
		} else
			stopFlywheels();

		// if both buttons on the front are pressed
		if (digitalRead(1) == LOW && digitalRead(2) == LOW)
			modFlywheelSpeed = 1000;

		if (button6U)
			setMotorSpeed(PICKUP_BELT, -MAX_PICKUP_SPEED);
		else if (button6D)
			setMotorSpeed(PICKUP_BELT, MAX_PICKUP_SPEED);
		else
			setMotorSpeed(PICKUP_BELT, 0);

		if (button7U)
			modFlywheelSpeed = 1650;
		if (button7D)
			modFlywheelSpeed = 1200;

		if (button5U)
			setFlywheelTarget(modFlywheelSpeed);
		else
			stopFlywheels();

		delay(10);
	}
}

void debugMode() {
	modFlywheelSpeed = 1250;

	setMotorReversed(LEFT_UP_DRIVE, true);
	setMotorReversed(LEFT_DOWN_DRIVE, true);

	setMotorReversed(LEFT_FLY_BOTTOM, true);
	setMotorReversed(RIGHT_FLY_TOP, true);

	setLeftFlywheelMotor(LEFT_FLY_TOP, true);
	setLeftFlywheelMotor(LEFT_FLY_BOTTOM, true);
	setRightFlywheelMotor(RIGHT_FLY_TOP, true);
	setRightFlywheelMotor(RIGHT_FLY_BOTTOM, true);

	setupEncoder(LFlywheel, 1);
	setupEncoder(RFlywheel, 2);

	beginEncoderTask();
	beginFlywheelControlTask();
	//beginEncoderResetTask();

	while (1) {

		// If switch3 is active, turn flywheels, if not turn them off
		if (digitalRead(3) == LOW) {
			setFlywheelTarget(modFlywheelSpeed);
		} else
			stopFlywheels();

		if (digitalRead(2) == LOW) {
			modFlywheelSpeed = 1500;
		} else {
			modFlywheelSpeed = 1250;
		}

		if (digitalRead(1) == LOW) {
			setMotorSpeed(PICKUP_BELT, -127);
			setFlywheelTarget(modFlywheelSpeed);
		} else {
			setMotorSpeed(PICKUP_BELT, 0);
			stopFlywheels();
		}

		printf("Encoder Left: %4.2f, Speed: %d\n\rEncoder Right: %4.2f, Speed: %d\n\r", getLeftSpeed(), leftSpeed, getRightSpeed(), rightSpeed);

		delay(10);
	}
}

void autonomous(){
	setupEncoder(LFlywheel, 1);
	setupEncoder(RFlywheel, 2);

	beginEncoderTask();
	beginFlywheelControlTask();

	setFlywheelTarget(1650);
	setMotorSpeed(PICKUP_BELT, MAX_PICKUP_SPEED);
	delay(20000);
}

void skills(){
	setupEncoder(LFlywheel, 1);
	setupEncoder(RFlywheel, 2);

	beginEncoderTask();
	beginFlywheelControlTask();

	setFlywheelTarget(1550);
	setMotorSpeed(10, -127);
}
void operatorControl() {
	//debugMode();
	driving();
}


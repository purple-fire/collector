#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <API.h>
#include "encoderTask.c"

//						     1  2  3  4  5  6  7  8  9  10 11 12
int motorReversed[] = 	   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int motorsToRamp[] =       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int motorLeftFlywheel[] =  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int motorRightFlywheel[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

bool rampingUp = false;
bool rampingDown = false;
int speedTarget = 0;
int lastSpeed = 0;

int rampUpDelay = 20;
int rampDownDelay = 20;

int flywheelTarget = 0;
int leftSpeed = 0;
int rightSpeed = 0;

void setMotorToRamp(unsigned char channel, bool ramp);
void setMotorReversed(unsigned char channel, bool isReversed);
void setRampUpDelay(int delay);
void setRampDownDelay(int delay);

void beginRampMotorsTask();
void stopRampMotorsTask();

void setMotorSpeed(unsigned char channel, int speed);

void rampMotorsUp(int speed);
void rampMotorsDown(int speed);
void rampMotors();

void beginFlywheelControlTask();
void setLeftFlywheelMotor(unsigned char channel, bool flywheel);
void setRightFlywheelMotor(unsigned char channel, bool flywheel);
void setFlywheelTarget(int target);
void flywheelRamp();

TaskHandle flywheelTask;
TaskHandle rampingTask;

#endif

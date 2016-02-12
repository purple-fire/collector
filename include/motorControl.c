// motorControl.c
#include "motorControl.h"

void setMotorToRamp(unsigned char channel, bool ramp){
	motorsToRamp[channel-1] = ramp;
}

void setMotorReversed(unsigned char channel, bool isReversed){
	motorReversed[channel-1] = isReversed;
}

void setRampUpDelay(int delay){
	rampUpDelay = delay;
}

void setRampDownDelay(int delay){
	rampDownDelay = delay;
}

void beginRampMotorsTask(){
	rampingTask = taskRunLoop(rampMotors, 10);
}

void stopRampMotorsTask(){
	taskSuspend(rampingTask);
}

void setMotorSpeed(unsigned char channel, int speed)
{
	if (motorReversed[channel-1] == 1)
		speed *= -1;

	motorSet(channel, speed);
}

void rampMotorsUp(int speed){
	rampingUp = true;
	speedTarget = speed;
}

void rampMotorsDown(int speed){
	rampingDown = true;
	speedTarget = speed;
}

void rampMotors(){
	if (rampingUp || rampingDown){
		if (speedTarget > lastSpeed){
			digitalWrite(1, LOW);
			for (int i = lastSpeed; i < speedTarget; i++){
				lastSpeed = i;
				for (int j = 1; j <= 12; j++){
					if (motorsToRamp[j-1])
						setMotorSpeed(j, i);
				}

				delay(rampUpDelay);
			}
			rampingUp = false;
		}

		if (speedTarget < lastSpeed){
			for (int i = lastSpeed; i > speedTarget; i--){
				lastSpeed = i;

				for (int j = 1; j <= 12; j++){
					if (motorsToRamp[j-1])
						setMotorSpeed(j, i);
				}

				delay(rampDownDelay);
			}
			rampingDown = false;
		}
	}
}

void setLeftFlywheelMotor(unsigned char channel, bool flywheel){
	motorLeftFlywheel[channel-1] = flywheel;
}

void setRightFlywheelMotor(unsigned char channel, bool flywheel){
	motorRightFlywheel[channel-1] = flywheel;
}

void setFlywheelTarget(int target){
	flywheelTarget = target;
}

void stopFlywheels(){
	flywheelTarget = 0;
}

void beginFlywheelControlTask(){
	flywheelTask = taskRunLoop(flywheelRamp, 10);
}
void flywheelRamp(){
	int leftEncoder = getLeftSpeed();
	int rightEncoder = getRightSpeed();

	if (leftEncoder < flywheelTarget && abs(flywheelTarget - leftEncoder) > 1){
		if (++leftSpeed > 127) leftSpeed = 127;

		for (int i = 0; i < 12; i++)
			if (motorLeftFlywheel[i])
				setMotorSpeed(i, leftSpeed);
	}
	else if (leftEncoder > flywheelTarget && abs(flywheelTarget - leftEncoder) > 1){
		if (--leftSpeed < 0) leftSpeed = 0;

		for (int i = 0; i < 12; i++)
			if (motorLeftFlywheel[i])
				setMotorSpeed(i, leftSpeed);
	}
	else{
		for (int i = 0; i < 12; i++)
			if (motorLeftFlywheel[i])
				setMotorSpeed(i, leftSpeed);
	}



	if (rightEncoder < flywheelTarget && abs(flywheelTarget - rightEncoder) > 1){
		if (++rightSpeed > 127) rightSpeed = 127;

		for (int i = 0; i < 12; i++)
			if (motorRightFlywheel[i])
				setMotorSpeed(i, rightSpeed);
	}
	else if(rightEncoder > flywheelTarget && abs(flywheelTarget - rightEncoder) > 1){
		if (--rightSpeed < 0) rightSpeed = 0;
		printf("Right Speed is: %d", rightSpeed);

		for (int i = 0; i < 12; i++)
			if (motorRightFlywheel[i])
				setMotorSpeed(i, rightSpeed);
	}
	else{
		for (int i = 0; i < 12; i++)
			if (motorRightFlywheel[i])
				setMotorSpeed(i, rightSpeed);
	}
}


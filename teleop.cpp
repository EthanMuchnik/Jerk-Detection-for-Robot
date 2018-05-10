/*
 * teleop.cpp
 *
 *  Created on: May 9, 2018
 *      Author: zbreit
 */



#include <iostream>
#include <TimedRobot.h>
#include "Robot.h"

void Robot::RumbleOn(double leftVal, double rightVal)
{
	void GenericHID::SetRumble(RumbleType kLeftRumble, double leftVal);
	void GenericHID::SetRumble(RumbleType kRightRumble, double rightVal);
};


void Robot::TeleopInit()
{

}

void Robot::TeleopPeriodic()
{
	double speedVal = 0;
	double turnVal = 0;

	// Different Drive Schemes
	if(DriveController.GetAButton())
	{
		speedVal = DriveController.GetY(GenericHID::JoystickHand::kLeftHand);
		turnVal = DriveController.GetX(GenericHID::JoystickHand::kLeftHand);
	}
	else if(DriveController.GetBumper(GenericHID::JoystickHand::kLeftHand))
	{
		speedVal = DriveController.GetY(GenericHID::JoystickHand::kLeftHand);
		turnVal = DriveController.GetX(GenericHID::JoystickHand::kRightHand);
	}
	else if(DriveController.GetBumper(GenericHID::JoystickHand::kRightHand))
	{
		speedVal = DriveController.GetY(GenericHID::JoystickHand::kRightHand);
		turnVal = DriveController.GetX(GenericHID::JoystickHand::kLeftHand);
	}

	DriveTrain.ArcadeDrive(speedVal, turnVal);
	AccelOld = AccelNew;
	AccelNew = ahrs.GetWorldLinearAccelX();
	if(AccelOld-AccelNew > 10)
	{
		RumbleOn(1, 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		RumbleOn(0, 0);
	}

}

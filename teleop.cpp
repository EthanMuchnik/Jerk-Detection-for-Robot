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
	DriveController.SetRumble(GenericHID::RumbleType::kLeftRumble, leftVal);
	DriveController.SetRumble(GenericHID::RumbleType::kRightRumble, leftVal);
}


void Robot::TeleopInit()
{
	JerkTimer.Start();
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

	SmartDashboard::PutNumber("Jerk", (AccelOld-AccelNew) / JerkTimer.Get());

	if((AccelOld - AccelNew) / JerkTimer.Get() > 50)
	{
		JerkShakeTimer.Start();
		RumbleOn(1, 1);

	}
	if(JerkShakeTimer.HasPeriodPassed(1)){
		RumbleOn(0, 0);
		JerkShakeTimer.Stop();
		JerkShakeTimer.Reset();
	}

	JerkTimer.Reset();

}

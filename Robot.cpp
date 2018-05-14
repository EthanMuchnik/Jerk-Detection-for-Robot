/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <TimedRobot.h>
#include <Timer.h>
#include "Robot.h"


// - When you have class members that are objects, you need to initialize them using an
//   initializer list, which can be seen below.
// - For every member object, you just call the associated constructor and pass in any
//   necessary inputs

Robot::Robot() :
	FrontLeftMotor(1),
	BackLeftMotor(2),
	FrontRightMotor(3),
	BackRightMotor(4),
	LeftMotors(FrontLeftMotor, BackLeftMotor),
	RightMotors(FrontRightMotor, BackRightMotor),
	DriveController(0),
	DriveTrain(LeftMotors, RightMotors),
	ahrs(SPI::Port::kMXP),
	AccelOld(0),
	AccelNew(0),
	JerkShakeTimer(),
	JerkTimer()
{

}


void Robot::RobotInit()
{

}


START_ROBOT_CLASS(Robot);

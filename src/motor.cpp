#ifndef MOTOR
#define MOTOR

#include "Arduino.h"

struct Motor
{
	int DelayTimes, Direction;
	double CircleCounts;
	int StepPinId, DirPinId;
	static constexpr double Circles = 3;
	/*
	DelayTime is used in the microseconds in the function Rotate. 
	CircleCounts is used to record how many circles the motor has rotate.
	*/
	Motor()
	{
		DelayTimes = 500;
		CircleCounts = 0;
		Direction = 1;
	}

  Motor& operator=(const Motor& m) {
    DelayTimes = m.DelayTimes;
    Direction = m.Direction;
    CircleCounts = m.CircleCounts;
    StepPinId = m.StepPinId;
    DirPinId = m.DirPinId;
    return *this;
  }

	void InitPin(int StepPin, int DirPin)
	{
		StepPinId = StepPin, DirPinId = DirPin;
		pinMode(StepPinId, OUTPUT);
		pinMode(DirPinId, OUTPUT);
	}
	//Initalize the Pin Id.

	void SetDirection(int Dir)
	{
		Direction = Dir;
		if (Dir == 1)
			digitalWrite(DirPinId, HIGH);
		else if (Dir == -1)
			digitalWrite(DirPinId, LOW);
	}
	//The Dir can only be 1 or -1, 1 for positive side, while -1 for negative side.

	void SetRotateSpeed(int DelayTime)
	{
		DelayTimes = DelayTime;
	}
	//Set the delay time to contron speed.

	void Rotate()
	{
		digitalWrite(StepPinId, HIGH), delayMicroseconds(DelayTimes);
		digitalWrite(StepPinId, LOW), delayMicroseconds(DelayTimes);
	}
	//Rotate a plaus

	void Rotate(double Circle)
	{
		int Circles = (int)(Circle * 200.0);
		for (int i = 1; i <= Circles; ++i)
			Rotate();
		CircleCounts += Circle * (double)Direction;
	}
	/*
	200 pulses can make a full rotation.
	This function can also be used to record how many circles the motor rotate.
	*/

	// in our robot, move the mass block to given fraction of the pod
	void MoveToFraction(double frac)
	{
		frac *= Circles;
		if (frac < CircleCounts)
    {
      SetDirection(-1);
      Rotate(CircleCounts - frac);
      SetDirection(1);
    }
		else
		{
			Rotate(frac - CircleCounts);
		}
	}
};

#endif

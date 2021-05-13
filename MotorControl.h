struct Motor{
	int DelayTimes,Direction;
	double CircleCounts;
	int StepPinId,DirPinId;
/*
	DelayTime is used in the microseconds in the function Rotate. 
	CircleCounts is used to record how many circles the motor has rotate.
*/ 
	Motor(){
		DelayTimes=500;
		CircleCounts=0;
		Direction=1;
	}

	void InitPin(int StepPin,int DirPin){
		StepPinId=StepPin,DirPinId=DirPin;
		pinMode(StepPinId,OUTPUT); 
		pinMode(DirPinId,OUTPUT);
	}
//Initalize the Pin Id.

	void SetDirection(int Dir){
		Direction=Dir;
		if(Dir==1) digitalWrite(DirPinId,HIGH);
		else if(Dir==-1) digitalWrite(DirPinId,LOW);
	}
//The Dir can only be 1 or -1, 1 for positive side, while -1 for negative side.

	void SetRotateSpeed(int DelayTime){
		DelayTimes=DelayTime;
	}
//Set the delay time to contron speed.

	void Rotate(){
		digitalWrite(StepPinId,HIGH),delayMicroseconds(DelayTimes);
		digitalWrite(StepPinId,LOW),delayMicroseconds(DelayTimes);
	}
//Rotate a plaus

	void Rotate(double Circle){
		int Circles=(int)(Circle*200.0);
		for(int i=1;i<=Circles;++i) Rotate();
		CircleCounts+=Circle*(double)Direction;
	}
/*
	200 pulses can make a full rotation.
	This function can also be used to record how many circles the motor rotate.
*/
} Motor1;

//Code below are for Arduino.
void setup(){
	Motor1.InitPin(3,4);
}

void loop(){
	Motor1.SetDirection(1);
	Motor1.Rotate(1);
	delay(500);
	Motor1.SetDirection(-1);
	Motor1.Rotate(1);
	delay(500);
}

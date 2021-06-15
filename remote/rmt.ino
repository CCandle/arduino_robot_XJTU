#define pinX  A0
#define pinY  A1
#define pinK  2

#include <SoftwareSerial.h> 

SoftwareSerial BT(10, 11); 
char val;

int X;
int Y;
int K;
String info;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;

void setup()
{
  pinMode(pinK, INPUT);
  Serial.begin(9600);
  info.reserve(200);
  BT.begin(9600);
}

void loop()
{
  X = analogRead(pinX);
  Y = analogRead(pinY);
  K = digitalRead(pinK);
  X /= 4;
  X++;
  Y /= 4;
  Y++;
  info[0] = X;
  info[1] = Y;
  info[2] = K;
  info[3] = 0;
  BT.println(info);
  Serial.println(info);
  int tmp = info[0];
  while(tmp)
  {
    Serial.print(tmp%10+'0');
    tmp /= 10;
  }

  if (BT.available()) {
    while(BT.available())
    {
      Serial.print((char)BT.read());
      delay(1);
    }
    Serial.println();
  }
  delay(1);
}
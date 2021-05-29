#include "driver.h"
#include "motor.h"
#include "sensor.h"

Motor motor1, motor2, motor3, motor4;
Sensor sensor;
RobotDriver driver;

void setup() {
  // initialize pin ids
  motor1.InitPin(1, 2);
  motor2.InitPin(3, 4);
  motor3.InitPin(5, 6);
  motor4.InitPin(7, 8);
  sensor.InitPin(9, 10);
  // initialize the driver
  driver.Init(motor1, motor2, motor3, motor4, sensor);
}

void loop() {
  driver.move_north();
}

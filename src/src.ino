#include "driver.cpp"
#include "motor.cpp"
#include "sensor.cpp"

Motor motor1, motor2, motor3, motor4;
Sensor sensor;
RobotDriver driver;

void setup()
{
    // initialize pin ids
    motor2.InitPin(3, 4);
    motor1.InitPin(5, 6);
    motor3.InitPin(9, 10);
    motor4.InitPin(11, 12);
    sensor.InitPin(7, 8);
    // initialize the driver
    driver.Init(motor1, motor2, motor3, motor4, sensor);
}

void loop()
{
    driver.move_north();
}

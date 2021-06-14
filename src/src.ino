#include "driver.cpp"
#include "motor.cpp"
#include "sensor.cpp"

typedef struct Motor Motor;
typedef struct Sensor Sensor;
typedef struct RobotDriver RobotDriver;

Motor motor1, motor2, motor3, motor4;
Sensor sensor;
RobotDriver driver;

void setup()
{
    // initialize pin ids
    motor1.InitPin(3, 4);
    motor2.InitPin(5, 6);
    motor3.InitPin(9, 10);
    motor4.InitPin(11, 12);
    // sensor.InitPin(7, 8);
    // initialize the driver
    Serial.begin(9600); 
    driver.Init(motor1, motor2, motor3, motor4, sensor);
}
int lstf(0);
void loop()
{
    driver.move_north();
    delay(50);
    Serial.println("------Loop Ended------");
    Serial.print('(');
    Serial.print(driver.curr_theta);
    Serial.print(',');
    Serial.print(driver.curr_phi);
    Serial.print(')');
    Serial.print(driver.motor_pos_frac[0], 5);
    Serial.print(' ');
    Serial.print(driver.motor_pos_frac[1], 5);
    Serial.print(' ');
    Serial.print(driver.motor_pos_frac[2], 5);
    Serial.print(' ');
    Serial.print(driver.motor_pos_frac[3], 5);
    Serial.print('\n');
}

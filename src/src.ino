#include "driver.cpp"
#include "motor.cpp"
#include "sensor.cpp"

typedef struct Motor Motor;
typedef struct Sensor Sensor;
typedef struct RobotDriver RobotDriver;

Motor motor1, motor2, motor3, motor4;
Sensor sensor;
RobotDriver driver;

String inputString = "";
boolean stringComplete = false;

void setup()
{
    // initialize pin ids
    motor1.InitPin(3, 4);
    motor2.InitPin(5, 6);
    motor3.InitPin(9, 10);
    motor4.InitPin(11, 12);
    // sensor.InitPin(7, 8);
    // initialize the driver
    driver.Init(motor1, motor2, motor3, motor4, sensor);

    // initialize serial
    Serial.begin(9600); 
    inputString.reserve(10);
}

void loop()
{
    delay(100);
    driver.move_x_y(0., 1.);
    /*if (stringComplete) {
        int x = (inputString[0] - 64), y = (inputString[1] - 64);
        if (inputString[3]) {
            // move to init state
            driver.initialize_robot_pos();
            delay(100);
        } else {
            driver.move_x_y(x / 64., y / 64.);
        }
        inputString = "";
        stringComplete = false;
        
        Serial.println("------Cmd Received------");
        Serial.print(x);
        Serial.print(',');
        Serial.print(y);
        Serial.print(';');
        Serial.println(inputString[3]);
        Serial.println("------Curr State------");
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
        Serial.println("------Loop Ended------");
    }*/
}

void serialEvent() {
    while (Serial.available()) {    // read serial
        char inChar = (char)Serial.read();
        inputString += inChar;
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
}

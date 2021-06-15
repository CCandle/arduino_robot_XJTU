#ifndef DRIVER
#define DRIVER

#include "Arduino.h"
#include "motor.cpp"
#include "sensor.cpp"

#include <math.h>
#include <string.h>

#define R_0 (1.)     // radius of the sphere
#define r_0 (.3)     // logically fixed eccentricity
#define U_BOUND (1.) // mass block boundary
#define L_BOUND (0.) // mass block boundary
#define MID_FRAC ((U_BOUND + L_BOUND) / 2);

const double dir_vecs[4][3] = {
    {0, 0, R_0},
    {2. / 3 * sqrt(2) * R_0, 0, -1. / 3 * R_0},
    {-sqrt(2) / 3 * R_0, sqrt(6) / 3 * R_0, -R_0 / 3},
    {-sqrt(2) / 3 * R_0, -sqrt(6) / 3 * R_0, -R_0 / 3}};

struct RobotDriver
{
    static void polar_to_orthogonal(double v[], double rho, double theta, double phi)
    {
        v[0] = rho * sin(phi) * cos(theta);
        v[1] = rho * sin(phi) * sin(theta);
        v[2] = rho * cos(phi);
    }

    double moving_step_length;   // moving pase, defined by fraction of pi
    double curr_theta, curr_phi; // cuurent position, defined by radius

    Motor driven_motor[4];
    double motor_pos_frac[4]; // from 0-1
    Sensor dir_sensor;

    double Det3(const double** M) {
      return M[0][0] * M[1][1] * M[2][2]
          + M[0][1] * M[1][2] * M[2][0]
          + M[0][2] * M[1][0] * M[2][1]
          - M[0][2] * M[1][1] * M[2][0]
          - M[0][1] * M[1][0] * M[2][2]
          - M[0][0] * M[1][2] * M[2][1];
    }

    void solve_fill(int m0, int m1, int m2, int mx, const double d[])
    {
        double MatAT[3][3];
        for (int i = 0; i < 3; ++i)
        {
            MatAT[i][0] = dir_vecs[m0][i];
            MatAT[i][1] = dir_vecs[m1][i];
            MatAT[i][2] = dir_vecs[m2][i];
        }

        const double *MatA[3] = {MatAT[0], MatAT[1], MatAT[2]};
        double D = Det3(MatA);

        MatA[0] = d;
        motor_pos_frac[m0] += Det3(MatA) / D;
        MatA[0] = MatAT[0];

        MatA[1] = d;
        motor_pos_frac[m1] += Det3(MatA) / D;
        MatA[1] = MatAT[1];

        MatA[2] = d;
        motor_pos_frac[m2] += Det3(MatA) / D;
        MatA[2] = MatAT[2];

        motor_pos_frac[mx] += MID_FRAC;
    }

    void calc_frac(double theta, double phi)
    {
        double dvec[3];
        polar_to_orthogonal(dvec, r_0, theta, phi);
        Serial.print(dvec[0], 5);
        Serial.print(' ');
        Serial.print(dvec[1], 5);
        Serial.print(' ');
        Serial.println(dvec[2], 5);
        for (int i = 0; i < 4; ++i)
            motor_pos_frac[i] = 0.;
        solve_fill(0, 1, 2, 3, dvec);
        solve_fill(0, 1, 3, 2, dvec);
        solve_fill(0, 2, 3, 1, dvec);
        solve_fill(1, 2, 3, 0, dvec);
        for (int i = 0; i < 4; ++i)
            motor_pos_frac[i] /= 4.;
    }

    void Init(Motor motor1, Motor motor2, Motor motor3, Motor motor4, Sensor sensor)
    {
        driven_motor[0] = motor1;
        driven_motor[1] = motor2;
        driven_motor[2] = motor3;
        driven_motor[3] = motor4;
        dir_sensor = sensor;

        moving_step_length = 0.05;
        curr_theta = 0;
        curr_phi = 0;
    }

    void set_step_rate(double v)
    {
        moving_step_length = v;
    }

    void initialize_robot_pos() {
        move_motor_to_frac();
    }

    void move_motor_to_frac()
    {
        for (int i = 0; i < 4; ++i)
        {
            driven_motor[i].MoveToFraction(motor_pos_frac[i]);
        }
    }

    void move_north()
    {
        curr_phi += moving_step_length * M_PI;
        if (curr_phi > 2*M_PI) curr_phi -= 2*M_PI;
        calc_frac(curr_theta, curr_phi);
        move_motor_to_frac();
    }

    void move_south()
    {
        curr_phi -= moving_step_length * M_PI;
        if (curr_phi < 0) curr_phi += 2*M_PI;
        calc_frac(curr_theta, curr_phi);
        move_motor_to_frac();
    }

    void move_east()
    {
        curr_theta += moving_step_length * M_PI;
        if (curr_theta > 2*M_PI) curr_theta -= 2*M_PI;
        calc_frac(curr_theta, curr_phi);
        move_motor_to_frac();
    }

    void move_west()
    {
        curr_theta -= moving_step_length * M_PI;
        if (curr_theta < 0) curr_theta += 2*M_PI;
        calc_frac(curr_theta, curr_phi);
        move_motor_to_frac();
    }
};

#endif

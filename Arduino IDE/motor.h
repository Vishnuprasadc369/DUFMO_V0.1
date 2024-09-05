#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

// Declare motor pin constants
extern const int IN1;
extern const int IN2;
extern const int IN3;
extern const int IN4;

// Function prototypes
void MOTORinit();
void MOTORforward(byte OUT1speed, byte OUT2speed);
void MOTORbackward(byte OUT1speed, byte OUT2speed);
void MOTORright(byte OUT1speed, byte OUT2speed);
void MOTORleft(byte OUT1speed, byte OUT2speed);

#endif // MOTOR_H
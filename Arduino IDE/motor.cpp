#include "motor.h"

// Define motor pin constants
const int IN1 = 13;
const int IN2 = 12;
const int IN3 = 14;
const int IN4 = 27;

void MOTORinit(){

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}
void MOTORforward(byte OUT1speed, byte OUT2speed) {

  analogWrite(IN1, OUT1speed);
  analogWrite(IN2, LOW);
  analogWrite(IN3, LOW);
  analogWrite(IN4, OUT2speed);
}

void MOTORbackward(byte OUT1speed, byte OUT2speed) {


  analogWrite(IN1, LOW);
  analogWrite(IN2, OUT1speed);
  analogWrite(IN3, OUT2speed);
  analogWrite(IN4, LOW);
}

void MOTORright(byte OUT1speed, byte OUT2speed) {


    analogWrite(IN1, LOW);
    analogWrite(IN2, OUT1speed);
    analogWrite(IN3, LOW);
    analogWrite(IN4, OUT2speed);
}

void MOTORleft(byte OUT1speed, byte OUT2speed) {

    
    analogWrite(IN1, OUT1speed);
    analogWrite(IN2, LOW);
    analogWrite(IN3, OUT2speed);
    analogWrite(IN4, LOW);
}

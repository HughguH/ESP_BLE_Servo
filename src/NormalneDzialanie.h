#ifndef NORMALNEDZIALANIE_H
#define NORMALNEDZIALANIE_H

#include <Arduino.h>
#include <numeric>
#include <vector>
#include <ESP32Servo.h> 
#include "Regulacje.h"


void normalneDzialanie();
int readSmoothedAnalog(int pin, int samples);

extern Servo myservo[servoNums];

constexpr const int minAngle = 0;
constexpr const int maxAngle = 180;

#endif
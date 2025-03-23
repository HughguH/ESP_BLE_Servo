#include "NormalneDzialanie.h"

Servo myservo[servoNums];

void normalneDzialanie() {
    for (int a = 0; a < servoNums; a++) {
        int adcValue = readSmoothedAnalog(analogSensorInputs[a], 32);
        int minADC = std::min(arr[a][0], arr[a][1]);
        int maxADC = std::max(arr[a][0], arr[a][1]);
        int angle = map(adcValue, minADC, maxADC, minAngle, maxAngle);
        angle = constrain(angle, minAngle, maxAngle);
        myservo[a].write(angle);
    }
}
int readSmoothedAnalog(int pin, int samples = 32 ) {
    long sum = 0;
    for (int i = 0; i < samples; i++) {
        sum += analogRead(pin);
        delay(2);  // Krótka przerwa między odczytami
    }
    return sum / samples;
}
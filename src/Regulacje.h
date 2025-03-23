#ifndef REGULACJE_H
#define REGULACJE_H

#include <Arduino.h>
#include <numeric>
#include <vector>
#include "BLEHandler.h"

static constexpr int servoNums = 6;

extern int i;
extern bool czyWyslanoOrozpoczeciu;
extern int licznik;
extern int arr[servoNums][2];
extern int analogSensorInputs[servoNums] ;

class Regulacje : public sendMessage {
private:

    bool czyNapiety;
    BLECharacteristic* characteristic;
    int sum;
    int pomiar();

public:
    Regulacje(BLECharacteristic* characteristic);
    void cyklAll();
};

#endif
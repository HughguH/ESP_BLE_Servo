#ifndef BLEHandler_H
#define BLEHandler_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

constexpr char  BLE_SERVICE_UUID[]= "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
constexpr char BLE_CHARACTERISTIC_UUID[] = "beb5483e-36e1-4688-b7f5-ea07361b26a8";


class sendMessage{
    public:
     void BLEsendMessage(BLECharacteristic *pCharacteristic, const std::string &message);
  };

  class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) override ;
};

class BLEcreateandstart{
    private:
    bool bleAktywne;
    BLEServer *bleServer;
    BLECharacteristic *characteristic;
    public:
        void BLEStart();
        void BLEstop();
        BLECharacteristic* getCharacteristic();

  };
#endif 


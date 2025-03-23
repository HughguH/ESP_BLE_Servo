#include "BLEHandler.h"

void sendMessage::BLEsendMessage(BLECharacteristic *pCharacteristic, const std::string &message){
    if (pCharacteristic) {
        pCharacteristic->setValue(message);
        pCharacteristic->notify();
    }
}
void MyCallbacks::onWrite(BLECharacteristic *characteristic){
    std::string value = characteristic->getValue();
}
void BLEcreateandstart::BLEStart(){
    {
        if (bleAktywne) return;
    
        // Zwolnij poprzednią instancję BLE, jeśli istnieje
        if (bleServer != nullptr) {
            BLEDevice::deinit();
            bleServer = nullptr;
        }
    
        // Inicjalizacja BLE
        BLEDevice::init("ESP32 BLE");
        bleServer = BLEDevice::createServer();

    
        BLEService *service = bleServer->createService(BLE_SERVICE_UUID);

    
        characteristic = service->createCharacteristic(
            BLE_CHARACTERISTIC_UUID,
            BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE |
            BLECharacteristic::PROPERTY_NOTIFY);
    

    
        characteristic->addDescriptor(new BLE2902());
        characteristic->setCallbacks(new MyCallbacks());
        characteristic->setValue("Czy chcesz zrobić regulacje?");
    
        service->start();
        BLEAdvertising *advertising = BLEDevice::getAdvertising();
        advertising->addServiceUUID(BLE_SERVICE_UUID);
        advertising->start();
    
        bleAktywne = true;
      }
}
void BLEcreateandstart::BLEstop(){
    if (!bleAktywne) return;
  
      // Zatrzymaj reklamowanie i zwolnij zasoby
      BLEDevice::getAdvertising()->stop();
      BLEDevice::deinit();
  
      characteristic = nullptr;
      bleServer = nullptr;
      bleAktywne = false;
}
BLECharacteristic* BLEcreateandstart::getCharacteristic() {
    return characteristic;
}

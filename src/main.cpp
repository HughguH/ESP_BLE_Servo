#include <Arduino.h>
#include <ESP32Servo.h> 
#include "BLEHandler.h"
#include "Regulacje.h"
#include "NormalneDzialanie.h"

constexpr int BUTTON_PIN = 8;

BLEcreateandstart blestartstop;

bool cyklall = false;


bool stanPrzyciskuTeraz;
bool stanPrzyciskuPoprzedni;
void normalneDzialanie();
int readSmoothedAnalog(int pin, int samples);
void wyswietlArr();

static int servoOutputs[servoNums] = {13, 14, 17, 18, 19, 21};


Regulacje regulacjeServ(blestartstop.getCharacteristic());


void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    stanPrzyciskuPoprzedni = digitalRead(BUTTON_PIN);
    for (int j = 0; j < servoNums; j++) {
        myservo[j].attach(servoOutputs[j]);
    }
    Serial.println("System start! Początkowe wartości arr:");
    wyswietlArr();
}
void loop() {
    // Odczytaj stan przycisku
    stanPrzyciskuTeraz = digitalRead(BUTTON_PIN);

    // Obsługa przycisku (uruchomienie BLE)
    if (stanPrzyciskuPoprzedni == HIGH && stanPrzyciskuTeraz == LOW) {
        blestartstop.BLEStart();
    }

    // Sprawdź, czy BLE jest aktywne i czy otrzymano komendę "all"
    BLECharacteristic* characteristic = blestartstop.getCharacteristic();
    if (characteristic != nullptr) {
        std::string value = characteristic->getValue();
        if (value == "all" && !cyklall) {
            cyklall = true; // Rozpocznij cykl regulacji
            Serial.println("Rozpoczęto cykl regulacji");
        }
    }

    // Wykonaj cykl regulacji, jeśli jest aktywny
    if (cyklall) {
        if (i < servoNums) {
            regulacjeServ.cyklAll(); // Wykonaj kolejny krok regulacji
            wyswietlArr(); // Wyświetl zawartość tablicy arr
        } else {
            // Zakończ cykl regulacji
            blestartstop.BLEstop();
            cyklall = false;
            if (characteristic != nullptr) {
                characteristic->setValue(""); // Resetuj wartość BLE
            }
            czyWyslanoOrozpoczeciu = false;
            i = 0; // Resetuj indeks serwa
            licznik = 0; // Resetuj licznik kroków cyklu
            Serial.println("Zakończono cykl regulacji");
        }
    }

    // Normalne działanie, gdy BLE nie jest aktywne
    if (!cyklall && !blestartstop.getCharacteristic()) {
        normalneDzialanie();
        wyswietlArr();
    }

    // Zapamiętaj stan przycisku na następny cykl
    stanPrzyciskuPoprzedni = stanPrzyciskuTeraz;

    // Krótkie opóźnienie, aby uniknąć zbyt szybkiego odczytu przycisku
    delay(100);
}

void wyswietlArr() {
    Serial.println("===== Zawartość tablicy arr =====");
    for (int j = 0; j < servoNums; j++) {
        Serial.print("Serwo ");
        Serial.print(j);
        Serial.print(": minADC = ");
        Serial.print(arr[j][0]);
        Serial.print(", maxADC = ");
        Serial.println(arr[j][1]);
    }
    Serial.println("=================================");
}

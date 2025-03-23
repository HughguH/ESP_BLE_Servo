#include "Regulacje.h"

int arr[servoNums][2] = {{0, 4095}, {0, 4095}, {0, 4095}, {0, 4095}, {0, 4095}, {0, 4095}};
int analogSensorInputs[servoNums] = {4, 5, 6, 7, 15, 16};
int i = 0;
bool czyWyslanoOrozpoczeciu = false;
int licznik = 0;

Regulacje::Regulacje(BLECharacteristic* characteristic) {
    this->characteristic = characteristic;
    this->czyNapiety = false;
    this->sum = 0;

    // Inicjalizacja tablicy arr
    for (int j = 0; j < servoNums; j++) {
        arr[j][0] = 0;
        arr[j][1] = 4095;
    }
}

int Regulacje::pomiar() {
    std::vector<int> vektor_z_pomiarami;
    int czasNapiety = (czyNapiety) ? 80 : 140;
    int liczbaPomiarow = (czyNapiety) ? 75 : 25;
    sum = 0;

    for (int p = 0; p < liczbaPomiarow; p++) {
        vektor_z_pomiarami.push_back(analogRead(analogSensorInputs[i]));
        delay(czasNapiety);
    }

    sum = std::accumulate(vektor_z_pomiarami.begin(), vektor_z_pomiarami.end(), 0);
    return sum / liczbaPomiarow;
}

void Regulacje::cyklAll() {
    switch (licznik) {
        case 0:
            if (!czyWyslanoOrozpoczeciu) {
                BLEsendMessage(characteristic, "Zaczynamy 😁");
                czyWyslanoOrozpoczeciu = true;
            }
            break;
        case 1:
            BLEsendMessage(characteristic, "Rozluźnij " + std::to_string(i));
            czyNapiety = true;
            break;
        case 2:
            arr[i][0] = pomiar();
            break;
        case 3:
            BLEsendMessage(characteristic, "Napnij " + std::to_string(i));
            czyNapiety = false;
            break;
        case 4:
            arr[i][1] = pomiar();
            licznik = -1;
            i++;
            break;
    }
    licznik++;
    delay(1000);
}
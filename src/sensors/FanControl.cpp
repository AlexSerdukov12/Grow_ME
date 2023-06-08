#include "FanControl.h"
#include <Arduino.h>

FanControl::FanControl(int ina1, int inb1, int ina2, int inb2)
  : INA1(ina1), INB1(inb1), INA2(ina2), INB2(inb2)
{}

void FanControl::begin() {
  pinMode(INA1, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB2, OUTPUT);
}

void FanControl::update(float temperature) {
  if (temperature > 28) {
    digitalWrite(INA1, LOW);
    digitalWrite(INB1, HIGH);
    digitalWrite(INA2, HIGH);
    digitalWrite(INB2, LOW);
    Serial.println("Fans : 1");
  } else {
    digitalWrite(INA1, LOW);
    digitalWrite(INB1, LOW);
    digitalWrite(INA2, LOW);
    digitalWrite(INB2, LOW);
    Serial.println("Fans : 0");
  }
}
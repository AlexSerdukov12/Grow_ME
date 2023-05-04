#include "WaterLevelSensor.h"

WaterLevelSensor::WaterLevelSensor(int analogPin) : _analogPin(analogPin) {
  pinMode(_analogPin, INPUT);
  _sensorValue = 0;
  _error = false;
  _currentLevel = 0.0;
}

void WaterLevelSensor::begin() {
  pinMode(_analogPin, INPUT);
}

void WaterLevelSensor::update() {
  _sensorValue = analogRead(_analogPin);
  if (_sensorValue == 0 || _sensorValue == 1023) {
    _error = true;
  } else {
    _error = false;
    _currentLevel = map(_sensorValue, 0, 1023, 0, 65);
  }
}

bool WaterLevelSensor::isError() {
  return _error;
}

void WaterLevelSensor::getCurrentLevel() {

  if (_sensorValue >= 480 && _sensorValue < 530) {
  Serial.println("Water level: 11%");
} else if (_sensorValue >= 530 && _sensorValue < 615) {
  Serial.println("Water level: 22%");
} else if (_sensorValue >= 615 && _sensorValue < 660) {
  Serial.println("Water level: 33%");
} else if (_sensorValue >= 660 && _sensorValue < 680) {
  Serial.println("Water level: 44%");
} else if (_sensorValue >= 680 && _sensorValue < 690) {
  Serial.println("Water level: 55%");
} else if (_sensorValue >= 690 && _sensorValue < 700) {
  Serial.println("Water level: 66%");
} else if (_sensorValue >= 700 && _sensorValue < 705) {
  Serial.println("Water level: 77%");
} else if (_sensorValue >= 705 && _sensorValue < 710) {
  Serial.println("Water level: 88%");
} else if (_sensorValue >= 710) {
  Serial.println("Water level: 99%");
} else {
  Serial.println("Water level: 0%");
}
}
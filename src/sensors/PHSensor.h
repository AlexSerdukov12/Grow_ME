#ifndef PHSENSOR_H
#define PHSENSOR_H

#include <Arduino.h>

class PHSensor {
public:
  PHSensor(int sensorPin, float calibrationValue);
  float getPHValue();

private:
  int _sensorPin;
  float _calibrationValue;
};

#endif
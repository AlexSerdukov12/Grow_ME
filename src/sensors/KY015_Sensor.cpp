#include "KY015_Sensor.h"

KY015_Sensor::KY015_Sensor(uint8_t pin) {
  dht = new DHT(pin, DHT11);
  _pin = pin;
  dht->begin();
  isErrorFlag = false;
}

float KY015_Sensor::getTemperature() {
  float temperature = dht->readTemperature();
  if (isnan(temperature)) {
    isErrorFlag = true;
  } else {
    isErrorFlag = false;
  }
  return temperature;
}

float KY015_Sensor::getHumidity() {
  float humidity = dht->readHumidity();
  if (isnan(humidity)) {
    isErrorFlag = true;
  } else {
    isErrorFlag = false;
  }
  return humidity;
}

bool KY015_Sensor::isError() {
  return isErrorFlag;
}
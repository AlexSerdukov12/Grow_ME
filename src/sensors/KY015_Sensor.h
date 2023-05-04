#ifndef KY015_SENSOR_H
#define KY015_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

class KY015_Sensor {
  public:
    KY015_Sensor(uint8_t pin);
    float getTemperature();
    float getHumidity();
    bool isError();
  private:
    DHT* dht;
    uint8_t _pin;
    bool isErrorFlag;
};

#endif
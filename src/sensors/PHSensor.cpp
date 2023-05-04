#include "PHSensor.h"

PHSensor::PHSensor(int sensorPin, float calibrationValue) {
  _sensorPin = sensorPin;
  _calibrationValue = calibrationValue;
}

float PHSensor::getPHValue() {
  int buffer_arr[10],temp;
  unsigned long int avgval;
  float ph_act;
  
  for(int i=0;i<10;i++) { 
    buffer_arr[i] = analogRead(_sensorPin);
    delay(30);
  }

  for(int i=0;i<9;i++) {
    for(int j=i+1;j<10;j++) {
      if(buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }

  avgval = 0;
  for(int i=2;i<8;i++)
    avgval += buffer_arr[i];

  float volt = (float)avgval * 5.0 / 1024 / 6; 
  ph_act = -5.5 * volt + _calibrationValue;
  if(ph_act>12 || ph_act<1 ) return 0;
  return ph_act;
}
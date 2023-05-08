  #include <sensors/KY015_Sensor.h>
  #include <sensors/FanControl.h>
  #include <sensors/WaterLevelSensor.h>
  #include <sensors/PHSensor.h>
  #include <time.h>

  ////PINS
  const int LDRInput = A0; //Set Analog Input A0 for LDR.
  const int PH_SENSOR_PIN = A1;
  const int LED = 2;
  const int WATER_SENSOR_PIN = A5;

  //// some variables
  float PH_CALIBRATION_VALUE = 21.34 - 0.7;

  // Set the hours of operation for the relay
  const int ON_HOUR = 6; // set the on hour
const int OFF_HOUR = 19; // set the off hour

  ////// objects
  KY015_Sensor ky015Sensor(10);
  FanControl fanControl(9, 8, 7, 6);
  WaterLevelSensor waterLevelSensor(WATER_SENSOR_PIN);
  PHSensor phSensor(PH_SENSOR_PIN, PH_CALIBRATION_VALUE);
  ///////


  void setup() {
    Serial.begin(9600);
    fanControl.begin();
    pinMode(LDRInput, INPUT);
    pinMode(LED, OUTPUT);
    waterLevelSensor.begin();


  }

  void loop() {

    ///// TEMP and Humidity
    float temperature = ky015Sensor.getTemperature();
    float humidity = ky015Sensor.getHumidity();
    if (ky015Sensor.isError()) {
      Serial.println("Error: KY015 Sensor not found.");
      fanControl.update(0);
    } else {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println("°C");
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.println("%");
      fanControl.update(temperature);
    }

  
  /////////////////////WATER SENSOR

    waterLevelSensor.update();
    if (waterLevelSensor.isError()) {
      Serial.println("Error: Water level sensor not working.");
    } else {
      waterLevelSensor.getCurrentLevel();
    }

    ///////////////////////////////// LDR + RELAY FOR LEDS
  time_t now = time(NULL); // get the current time
  struct tm *currentTime = localtime(&now);
  int currentHour = currentTime->tm_hour; // get the current hour

  if (currentHour >= ON_HOUR && currentHour < OFF_HOUR) {
    int value = analogRead(LDRInput); //Reads the Value of LDR(light).
    if (value >= 0 && value <= 1023) {
      Serial.print("LDR value is: ");
      Serial.println(value);
      if (value < 300) {
        digitalWrite(LED, HIGH); //The LED turns ON in Dark.
        Serial.println("Turning on relay LED.");
      } else {
        digitalWrite(LED, LOW); //The LED turns OFF in Light.
        Serial.println("Turning off relay LED.");
      }
    } else {
      Serial.println("Error: LDR sensor not working properly.");
    }
  } else {
    digitalWrite(LED, LOW); //The LED turns OFF when it's not between on hour and off hour.
  }


  ////////////////////////////////PH SENSOR
    if(phSensor.getPHValue()<2||phSensor.getPHValue()>12 ) {    Serial.println("Error: PH sensor not working properly.");
    }
    else{Serial.print("PH value:");
    Serial.println(phSensor.getPHValue());
    }

  ///////////////////////////////////////////////
    Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    delay(2000);
  }
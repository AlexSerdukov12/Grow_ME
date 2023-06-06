  #include <sensors/KY015_Sensor.h>
  #include <sensors/FanControl.h>
  #include <sensors/WaterLevelSensor.h>
  #include <sensors/PHSensor.h>
  #include <time.h>
  ////PINS
  #define POWER_PIN  3  // water
  #define SIGNAL_PIN A5 // water
  #define SENSOR_MIN 0 // water
  #define SENSOR_MAX 610 // water

  const int LDRInput = A0; //Set Analog Input A0 for LDR.
  const int PH_SENSOR_PIN = A3;
  const int LED = 2;
  const int WATER_SENSOR_PIN = A4;

  //// some variables
  float PH_CALIBRATION_VALUE = 21.34 - 0.7;

  int value = 0; // variable to store the water sensor value
  int level = 0; // variable to store the water level

  // Set the hours of operation for the relay
  const int ON_HOUR = 6; // set the on hour
  const int OFF_HOUR = 22; // set the off hour

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
    pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT WATER SENSOR 
   digitalWrite(POWER_PIN, LOW); // turn the sensor OFF WATER SENSOR


  }

  void loop() {

    ///// TEMP and Humidity
    float temperature = ky015Sensor.getTemperature();
    float humidity = ky015Sensor.getHumidity();
   
     
    ///////////////////////////////// LDR + RELAY FOR LEDS



  ////////////////////////////////PH SENSOR
  

  /////////////////////WATER SENSOR
  digitalWrite(POWER_PIN, HIGH);   // turn the sensor ON
  delay(10);                       // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN);  // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);    // turn the sensor OFF

 
  
  ///////////////////////////////////////////////
  

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
    fanControl.update(temperature);
    int waterLevel = map(value, SENSOR_MIN, SENSOR_MAX, 0, 100); // map the value to a percentage (0-100)
    Serial.print("Water level : ");
    Serial.print(waterLevel);
    Serial.println("%");
    
    if (true) {
      int value = analogRead(LDRInput); //Reads the Value of LDR(light).
      if (value >= 0 && value <= 1023)
      {
        Serial.print("LDR value is: ");
        Serial.println(value);
        if (value < 300) {
          digitalWrite(LED, HIGH); //The LED turns ON in Dark.
          Serial.println("LED : ON");
        } else {
          digitalWrite(LED, LOW); //The LED turns OFF in Light.
          Serial.println("LED : OFF");
        }
      } 
    } else {
      digitalWrite(LED, LOW); //The LED turns OFF when it's not between on hour and off hour.
    }
    Serial.print("PH value:");
    Serial.println(phSensor.getPHValue());
      



    delay(10000);
  }
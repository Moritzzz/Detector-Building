/*
This code is an adaptation of the example code given by SparkFun for use with the Tmp36 sensor.

This code has been made for help with calibration and use for the Science Olympiad "Detector Building" event. Detector Building involves the building and
programming of a digital temperature sensor, and the calibration of the sensor to accurately measure water temperature.

TODO: Include a link to the circuit diagram

Created By: Joaquin
*/

float voltage = 0;
float totalVolt = 0; // total voltage during measuring time
float avgVolt = 0;
float degreesC = 0;
float totalC = 0; // total temperature during measuring time
float avgC = 0;

bool takeAvg = false;
int takeAvgTime = 0;
int startTime = 0;
int tests = 0; // number of times the temperature was measured and added to total

// temperature ranges for led lights
float redRange[] = {0, 20};   
float greenRange[] = {20, 25};
float blueRange[] = {25, 75};

void setup() {
  Serial.begin(9600);
}

void loop() {
  
  voltage = analogRead(A0) * 0.004882814; //convert the analog reading, which varies from 0 to 1023, back to a voltage value from 0-5 volts
  degreesC = (voltage - 0.5) * 100; //convert the voltage to a temperature in degrees Celsius

  if (Serial.available() > 0) {
      int numIn = Serial.parseInt(); 

      if (numIn != 0) {
        takeAvgTime = numIn * 1000; // comvert time to take to millis
        startTime = millis();
        takeAvg = true;
        tests = 0; // reset times measured
      }
  }

  if (takeAvg) {
      totalVolt += voltage;
      totalC += degreesC;
      tests ++;
      
      if (millis >= startTime + takeAvgTime) {
        takeAvg = false;

        // get and print average voltage over given time
        avgVolt = totalVolt/tests;
        Serial.print("Avg voltage over last ");
        Serial.print(takeAvgTime/1000);
        Serial.print(" Seconds: ");
        Serial.println(avgVolt);

        // get and print average temp over given time
        avgC = totalC/tests;
        Serial.print("Avg temperature over last ");
        Serial.print(takeAvgTime/1000);
        Serial.print(" Seconds: ");
        Serial.println(avgC);
      }
  }

  if (degreesC >= redRange[0] && degreesC < redRange[1]) {
       digitalWrite(11, HIGH);
       digitalWrite(12, LOW);
       digitalWrite(13, LOW);
  } else if (degreesC >= greenRange[0] && degreesC < greenRange[1]) {
       digitalWrite(12, HIGH);
       digitalWrite(11, LOW);
       digitalWrite(13, LOW);
  } else if (degreesC >= blueRange[0] && degreesC < blueRange[1]) {
       digitalWrite(13, HIGH);
       digitalWrite(11, LOW);
       digitalWrite(12, LOW);
  } 
}

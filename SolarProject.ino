#include <Servo.h>
Servo servo1; // create servo object to control a servo
int analogValues[4];
float solarReading;
float solarVoltage;

float lightSensorDiff;
int LIGHT_SENSOR_THRESHOLD = 20;
int curr_angle = -1;

int counter = 0;
float sumVoltage = 0;;
float averageVoltage;

void setup() {
  Serial.begin(9600);
  servo1.attach(9);
}

void loop() {
  delay(100);
  
  // get light sensor input
  analogValues[0] = analogRead(A0); // right side
  analogValues[1] = analogRead(A1); // left side  
  
  // get motor rotation angle
  curr_angle = servo1.read();
  
  // get solar panel voltage
  solarReading = analogRead(A4);
  solarVoltage = solarReading * 5.0 / 1024.0;// map(solarReading, 0, 1023, 0, 5);
  
  lightSensorDiff = analogValues[1] - analogValues[0]; // left - right
  
  if (lightSensorDiff > LIGHT_SENSOR_THRESHOLD && ((curr_angle + 2) <= 160)){
    // move servo one direction by 2 degrees
    curr_angle = curr_angle + 2;
    servo1.write(curr_angle);
  }
  else if (lightSensorDiff < - LIGHT_SENSOR_THRESHOLD && ((curr_angle - 2) >= 10)){
    // move servo other direction by 2 degrees
    curr_angle = curr_angle - 2;
    servo1.write(curr_angle);
  }
  counter ++;
  sumVoltage += solarVoltage;
  averageVoltage = sumVoltage / counter;
  Serial.print("Avg Voltage: ");
  Serial.println(averageVoltage);
  Serial.println("");
}

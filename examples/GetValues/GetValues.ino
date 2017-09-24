#include "sonar.h"

unsigned int leftRawValue;
unsigned int *leftValues;
unsigned int leftReading;
byte leftSonarPin = 3;

Sonar leftSonar;

void setup() { 
  Serial.begin(9600);
  leftSonar.begin(leftSonarPin);
}

void loop() {
  leftRawValue = leftSonar.raw(); // one ping sample
  leftValues = leftSonar.samples(); // 5 ping samples
  leftReading = leftSonar.read(); // median or mode
  
  Serial.print("instant mm, avg mm, avg inches:  ");
  Serial.print(leftRawValue);
  Serial.print(",");
  Serial.print(leftReading);
  Serial.print(",");
  Serial.print(mmToInch(leftReading), 2);
  Serial.println("");

  Serial.print("instant samples:                 ");
  for (byte i = 0; i < 5; i++) {
    Serial.print(leftValues[i]);
    if (i < 4) Serial.print(",");
  }
  Serial.println("");
  
  delay(100);
}

float mmToInch(unsigned int mm) {
  return (float)mm / 25.4;
}
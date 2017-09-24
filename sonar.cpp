/*
  sonar.cpp - Filtered sonar distance pings.
  Sept 11, 2017
*/
#include "Arduino.h"
#include "./sonar.h"


Sonar::Sonar() {}

void Sonar::begin(byte pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
  arraySize = 5; // samples to average (mode or median)
  sampleArray[arraySize];
  sampleDelay = 10;  
  // unitRatio = 1;
}

unsigned int Sonar::raw() {
  unsigned int ping;
  ping = pulseIn(_pin, HIGH);
  
  return ping;
}

unsigned int * Sonar::samples() {
  sensorRead();
  sortArray(sampleArray, arraySize);
  
  return sampleArray;
}

unsigned int Sonar::read() {
  unsigned int filteredRead;

  sensorRead();
  sortArray(sampleArray, arraySize);
  filteredRead = filterArray(sampleArray, arraySize);

  return filteredRead;
}

void Sonar::sensorRead() {
  unsigned int ping;
  
  for(int i = 0; i < arraySize; i++) { 
		ping = raw();
		//sampleArray[i] = ping/unitRatio; // convert each array element units beforehand
    sampleArray[i] = ping;
    if (sampleDelay > 0) delay(sampleDelay);
	}
}

unsigned int * Sonar::sortArray(unsigned int *a, byte n) {
  for (int i = 1; i < n; ++i) {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--) {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }

  return a;
}

unsigned int Sonar::filterArray(unsigned int *a, byte n) {
  unsigned int filter = 0;
  byte i = 0;
  byte count = 0;
  byte maxCount = 0;
  byte median;
  byte prevCount = 0;

  while (i < (n-1)) {
    prevCount = count;
    count = 0;
    while (a[i] == a[i+1]) {
      count++;
      i++;
    }
    if (count > prevCount && count > maxCount) {
      filter = a[i];
      maxCount = count;
      median = 0;
    }
    if (count == 0) i++;
    if (count == maxCount) median = 1;
    if (filter == 0 || median == 1) filter = a[(n/2)];

    return filter;
  } 
}

/*
  sonar.h - Filtered sonar distance pings.
  Sept 11, 2017
  
  sortArray - http://forum.arduino.cc/index.php?topic=49059.msg350709#msg350709
  filterArray - http://forum.arduino.cc/index.php?topic=20920.msg154939#msg154939
  
*/
#ifndef Sonar_h
#define Sonar_h

#include "Arduino.h"

class Sonar {
  public:
    Sonar();

    void begin(byte pin);
    unsigned int raw();
    unsigned int read();
    unsigned int * samples();
    byte arraySize;
    unsigned int sampleDelay;
    // unsigned int unitRatio;

  private:
    void sensorRead();
    unsigned int * sortArray(unsigned int *a, byte n);
    unsigned int filterArray(unsigned int *a, byte n);
    unsigned int sampleArray[9];
    byte _pin;
};

#endif
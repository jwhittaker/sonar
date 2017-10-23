# sonar
Maxbotix pwm sonar library for arduino

Takes 5 ping samples and returns the median value. Arduino syntax highlighting and example file included.
Developed with this part: https://www.maxbotix.com/Ultrasonic_Sensors/MB7334.htm

Return one single ping as an unsigned int (32bit)

`mySonar.raw();`

Return an array (need a pointer var) of the pings sampled.

`mySonar.samples();`

Return the median or mode of the samples as 32-bit unsigned int.

`mySonar.read();`

There is a delay used between pings of 10ms.

Example setup and parameter changes:
```
byte mySonarPin = 3;
unsigned int sonarData;
Sonar mySonar;

mySonar.begin(mySonarPin);
mySonar.sampleDelay = 12;
mySonar.arraySize = 9;

sonarData = mySonar.read();
```

Array functions used from:
  sortArray - http://forum.arduino.cc/index.php?topic=49059.msg350709#msg350709
  filterArray - http://forum.arduino.cc/index.php?topic=20920.msg154939#msg154939

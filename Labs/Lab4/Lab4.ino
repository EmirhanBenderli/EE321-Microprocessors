#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <ZumoMotors.h>


#define LED_PIN 13
#define MZ80_PIN 6
#define NUM_SENSORS 6

//Pushbutton button(ZUMO_BUTTON);
ZumoReflectanceSensorArray reflectanceSensors;
ZumoMotors motors;

// Define an array for holding sensor values.
unsigned int sensorValues[NUM_SENSORS];
unsigned int positionVal = 0;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  // --------------------------- Start Of The Calibration -------------------------
  reflectanceSensors.init();
  unsigned long startTime = millis();
  while (millis() - startTime < 5000)  // make the calibration take 10 seconds
  {
    reflectanceSensors.calibrate();
  }
  // ------------------- End Of The Calibration -----------------------
}

unsigned int mostLeftSensor() {
  if (sensorValues[0] < 600)
    return 1;
  else
    return 0;
}

unsigned int leftSensor() {
  if (sensorValues[1] < 600)
    return 1;
  else
    return 0;
}

unsigned int midLeftSensor() {
  if (sensorValues[2] < 600)
    return 1;
  else
    return 0;
}

unsigned int midRightSensor() {
  if (sensorValues[3] < 600)
    return 1;
  else
    return 0;
}

unsigned int rightSensor() {
  if (sensorValues[4] < 600)
    return 1;
  else
    return 0;
}

unsigned int mostRightSensor() {
  if (sensorValues[5] < 600)
    return 1;
  else
    return 0;
}

void turnRight(int i, int j) {
  motors.setSpeeds(i, -j);
}

void go() {
  motors.setSpeeds(350, 350);
}

void loop() {
  positionVal = reflectanceSensors.readLine(sensorValues);
  if (mostLeftSensor() == 1) {
    motors.setSpeeds(-430, -450);
    delay(70);
    turnRight(260, -260);
  } else {
    go();
  }
  while (!digitalRead(MZ80_PIN)) {
    turnRight(200,-200);
    delay(60);

  }
  while (digitalRead(MZ80_PIN)) {
    go();
    
  }
  
}

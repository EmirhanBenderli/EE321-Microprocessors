#include <ZumoShield.h>

#define LED_PIN 13
#define MZ80_PIN 6
#define NUM_SENSORS 6
#define BLINK_DELAY 1000

unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
ZumoMotors motors;
ZumoBuzzer buzzer;

#define QTR_THRESHOLD 1500
#define REVERSE_SPEED 200
#define TURN_SPEED 155
#define FORWARD_SPEED 200
#define KNOCK_DOWN_SPEED 180    // for speed to knock down objects

#define STOP_DURATION 100
#define REVERSE_DURATION 320
#define TURN_DURATION 300
#define KNOCK_DOWN_DELAY 900  // for delay after knocking down an object

#define RIGHT 1
#define LEFT -1

int objectCount = 0;
unsigned long firstObjectDetectionTime = 0;
unsigned long lastObjectDetectionTime = 0;
unsigned long lastTurnTime = 0;

bool objectDetected = false;
bool turnDirection = RIGHT;  // Variable to alternate turn direction for slalom

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  buzzer.playMode(PLAY_AUTOMATIC);
  pinMode(MZ80_PIN, INPUT);
  sensors.init();
  unsigned long calibrationTime = millis();
  while (millis() - calibrationTime < 5000) {
    sensors.calibrate();
  }
}

void loop() {
  sensors.read(sensor_values);

  // Always check for border detection first
  if (sensor_values[0] < QTR_THRESHOLD || sensor_values[5] < QTR_THRESHOLD) {
    handleBorderDetection();
  } else if (!digitalRead(MZ80_PIN)) {
    handleObjectDetection();
  } else {
    scanForObjects();
  }

  // Check if maximum exploration time has passed 45sec now
  if (firstObjectDetectionTime > 0 && millis() - firstObjectDetectionTime >= 45000) {
    motors.setSpeeds(0, 0);
    blinkLED(objectCount);
    while (true)
      ;  // Stop the robot after blinking
  }
}

void handleObjectDetection() {
  unsigned long currentTime = millis();

  // Debounce object detection to prevent multiple counts within a short period
  if (currentTime - lastObjectDetectionTime < 50) {
    return;
  }
  if (firstObjectDetectionTime == 0) {
    firstObjectDetectionTime = millis();
  }

  motors.setSpeeds(0, 0);
  delay(STOP_DURATION);
  motors.setSpeeds(KNOCK_DOWN_SPEED, KNOCK_DOWN_SPEED);
  delay(500);  // Approach the object to knock it down

  objectCount++;
  buzzer.playNote(NOTE_G(5), 100, 12);
  lastObjectDetectionTime = millis();
  delay(KNOCK_DOWN_DELAY);  // Delay to stabilize after knocking down an object
  motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
  delay(KNOCK_DOWN_DELAY);
}

void scanForObjects() {
  static int turnCount = 0;                  //  variable to keep track of turn count
  static bool forwardMoveCompleted = false;  // variable to track if the forward move is completed

  unsigned long currentTime = millis();

  if (currentTime - lastTurnTime >= 500) {
    // Alternate turn direction for 360 effect
    if (turnDirection == RIGHT) {
      if (sensor_values[0] < QTR_THRESHOLD || sensor_values[5] < QTR_THRESHOLD) {
        handleBorderDetection();
      }
      turn(LEFT, false);
      turnDirection = LEFT;
    } else {
      if (sensor_values[0] < QTR_THRESHOLD || sensor_values[5] < QTR_THRESHOLD) {
        handleBorderDetection();
      }
      turn(RIGHT, false);
      turnDirection = RIGHT;
    }
    lastTurnTime = currentTime;
    delay(120);

    turnCount++;

    // Check if the robot has completed 9-10 turns (360 degrees)
    if (turnCount >= 9) {
      turnCount = 0;
      forwardMoveCompleted = false;
    }
  }

  // Move forward a little bit after every 360-degree turn
  if (!forwardMoveCompleted && turnCount == 0) {
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(500);  // Adjust this delay to control the forward movement distance
    motors.setSpeeds(0, 0);
    forwardMoveCompleted = true;
  }
}

void handleBorderDetection() {
  motors.setSpeeds(0, 0);
  if (sensor_values[0] < QTR_THRESHOLD) {
    turn(RIGHT, true);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(500);
  } else if (sensor_values[5] < QTR_THRESHOLD) {
    turn(LEFT, true);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
    delay(500);
  }
}

void blinkLED(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_DELAY);
    digitalWrite(LED_PIN, LOW);
    delay(BLINK_DELAY);
  }
}

void turn(int direction, bool randomize) {
  static unsigned int duration_increment = TURN_DURATION / 4;

  motors.setSpeeds(0, 0);
  delay(STOP_DURATION);

  // Divide the turn into smaller steps with detection checks
  const int turnSteps = 5;  // Adjust this value to increase or decrease the number of steps
  const int turnDuration = randomize ? TURN_DURATION + (random(10) - 2) * duration_increment : TURN_DURATION;
  const int stepDuration = turnDuration / turnSteps;

  for (int i = 0; i < turnSteps; i++) {
    motors.setSpeeds(TURN_SPEED * direction, -TURN_SPEED * direction);
    delay(stepDuration);

    // Check for object detection during the turn
    if (!digitalRead(MZ80_PIN)) {
      handleObjectDetection();
      break;  // Exit the loop if an object is detected
    }
  }

  motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
}

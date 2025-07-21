const int leftBtn = 4;
const int rightBtn = 2;
const int leftLED = 13;
const int rightLED = 12;

unsigned long lastBlinkTime = 0;
unsigned long previousSchedulerTime = 0;

bool leftBlink = false;
bool rightBlink = false;
bool hazard = false;

bool leftLEDState = false;
bool rightLEDState = false;

unsigned long leftPressStart = 0;
unsigned long rightPressStart = 0;

void setup() {
  pinMode(leftBtn, INPUT_PULLUP);
  pinMode(rightBtn, INPUT_PULLUP);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);

  Serial.begin(9600);
  Serial.println("System Initialized");
}

void loop() {
  unsigned long currentMillis = millis();

  // 100 ms scheduler
  if (currentMillis - previousSchedulerTime >= 100) {
    previousSchedulerTime = currentMillis;
    runSchedulerTasks(currentMillis);
  }

  // Blinking logic (every 300 ms)
  if (currentMillis - lastBlinkTime >= 300) {
    lastBlinkTime = currentMillis;
    runBlinkLogic();
  }
}

void runSchedulerTasks(unsigned long currentMillis) {
  bool leftPressed = digitalRead(leftBtn) == HIGH;
  bool rightPressed = digitalRead(rightBtn) == HIGH;

  // Check for hazard mode
  if (leftPressed && rightPressed) {
    if (leftPressStart == 0 || rightPressStart == 0) {
      leftPressStart = currentMillis;
      rightPressStart = currentMillis;
    }

    if ((currentMillis - leftPressStart >= 1000) && (currentMillis - rightPressStart >= 1000)) {
      hazard = !hazard;
      leftBlink = false;
      rightBlink = false;
      Serial.println(hazard ? "Hazard ON" : "Hazard OFF");
      leftPressStart = 0;
      rightPressStart = 0;
    }
  } else {
    // Handle individual left button
    if (leftPressed) {
      if (leftPressStart == 0) leftPressStart = currentMillis;
      if (currentMillis - leftPressStart >= 1000 && !hazard) {
        leftBlink = !leftBlink;
        rightBlink = false;
        Serial.println(leftBlink ? "Left Indicator ON" : "Left Indicator OFF");
        leftPressStart = 0;
      }
    } else {
      leftPressStart = 0;
    }

    // Handle individual right button
    if (rightPressed) {
      if (rightPressStart == 0) rightPressStart = currentMillis;
      if (currentMillis - rightPressStart >= 1000 && !hazard) {
        rightBlink = !rightBlink;
        leftBlink = false;
        Serial.println(rightBlink ? "Right Indicator ON" : "Right Indicator OFF");
        rightPressStart = 0;
      }
    } else {
      rightPressStart = 0;
    }
  }
}

void runBlinkLogic() {
  if (hazard) {
    leftLEDState = !leftLEDState;
    rightLEDState = leftLEDState;
  } else if (leftBlink) {
    leftLEDState = !leftLEDState;
    rightLEDState = false;
  } else if (rightBlink) {
    rightLEDState = !rightLEDState;
    leftLEDState = false;
  } else {
    leftLEDState = false;
    rightLEDState = false;
  }

  digitalWrite(leftLED, leftLEDState);
  digitalWrite(rightLED, rightLEDState);

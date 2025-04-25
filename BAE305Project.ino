// DC Motor Pins
const int IN1 = 3;  // Motor A
const int IN2 = 5;

// Stepper Motor Pins
const int IN3 = 6;
const int IN4 = 7;

// Button Pins
const int buttonStepper = A0;
const int buttonRaise = A5;
const int buttonLower = A4;

void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Button pins
  pinMode(buttonStepper, INPUT_PULLUP);  // Use internal pull-up
  pinMode(buttonRaise, INPUT_PULLUP);
  pinMode(buttonLower, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // Read button states (LOW = pressed, because of pull-up)
  bool stepperPressed = digitalRead(buttonStepper) == LOW;
  bool raisePressed = digitalRead(buttonRaise) == LOW;
  bool lowerPressed = digitalRead(buttonLower) == LOW;

  if (stepperPressed) {
    Serial.println("Turning blinds (stepper)...");
    turnBlinds();
  } else if (raisePressed) {
    Serial.println("Raising blinds (DC motors clockwise)...");
    turnMotorsClockwise();
  } else if (lowerPressed) {
    Serial.println("Lowering blinds (DC motors counterclockwise)...");
    turnMotorsCounterClockwise();
  } else {
    stopMotors();
  }

  delay(100);  // debounce delay
}

// Stepper motor: 4 turns = 2048 * 4 steps
void turnBlinds() {
  for (int i = 0; i < 2048 * 4; i++) {
    stepStepper(i % 4);
    delay(2);
  }
}

// DC Motor control functions
void turnMotorsClockwise() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void turnMotorsCounterClockwise() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// Basic 4-step control for a unipolar stepper motor
void stepStepper(int step) {
  switch (step) {
    case 0:
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      break;
    case 1:
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      break;
    case 2:
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      break;
    case 3:
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
      break;
  }
}


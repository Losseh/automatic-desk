#define LED_OFF 0x1
#define LED_ON  0x0
#define MAX_PWM 255

// leds

enum LedType : uint8_t {
  YELLOW, RED, BUILTIN, COUNT
};

const int ledPins[] = {6, 7, LED_BUILTIN};
uint8_t ledState[] = {LED_OFF, LED_OFF, LED_OFF};

// buttons
struct ButtonsPins {
  int up;
  int down;
  int callibrate;
};
const ButtonsPins buttonsPins = {3, 4, 9};

struct ButtonsState {
 int up;
 int down;
 int callibrate;
};
ButtonsState buttonsState = {LOW, LOW, LOW};

// current sensor
struct CurrentSensor {
  int pin;
  int zeroValue;
  int samples;
};
const CurrentSensor currentSensor = {A0, 537, 5};

int currentValue = 0;

// motor
struct MotorPins {
  int pwm;
  int dir;
};
const MotorPins motorPins = {11, 12};

struct MotorConstants {
  int maxChange;
};

const MotorConstants motorConstants = {10};

struct MotorState {
  int actual;
  int expected;
};
MotorState motorState = {0, 0};

// position
int position = 0;

// response
String response;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize motor pins
  pinMode(motorPins.pwm, OUTPUT);
  pinMode(motorPins.dir, OUTPUT);

  // initialize LED pins
  for (uint8_t led = 0; led < LedType::COUNT; led++) {
    pinMode(ledPins[led], OUTPUT);
    digitalWrite(ledPins[led], LED_OFF);
  }

  // initialize buttons
  pinMode(buttonsPins.up, INPUT_PULLUP);
  pinMode(buttonsPins.down, INPUT_PULLUP);
  pinMode(buttonsPins.callibrate, INPUT_PULLUP);

  Serial.begin(9600);
}

void measureCurrent() {
  currentValue = 0;
  for (int i = 0; i < currentSensor.samples; i++) {
    currentValue += analogRead(currentSensor.pin);
  }
  currentValue = currentValue / currentSensor.samples - currentSensor.zeroValue;
}

void setMotorRaw(int motorValue) {
  uint8_t dir = motorValue < 0 ? 0 : 1;
  uint8_t pwm = abs(motorValue);
  analogWrite(motorPins.pwm, pwm);
  digitalWrite(motorPins.dir, dir);

  Serial.write("dir=");
  Serial.print(dir);
  Serial.write(" ");
  Serial.write("pwm=");
  Serial.print(pwm);
  Serial.write("\n");
}

void updateMotor() {
  int diff = motorState.expected - motorState.actual;
  if (diff != 0) {

    if (abs(diff) <= motorConstants.maxChange) {
      motorState.actual = motorState.expected;
    } else {
      motorState.actual += (diff > 0)
        ? motorConstants.maxChange
        : -motorConstants.maxChange;

      motorState.actual = constrain(motorState.actual, -MAX_PWM, MAX_PWM);
    }

    Serial.write("motor exp=");
    Serial.print(motorState.expected);
    Serial.write(" act=");
    Serial.print(motorState.actual);
    Serial.write("\n");

    setMotorRaw(motorState.actual);
  }
}

void setLedOff(int ledPin) {
  digitalWrite(ledPin, HIGH);
}

void setLed(LedType led, uint8_t value) {
  if (ledState[led] != value) {
    ledState[led] = value;
    digitalWrite(ledPins[led], value);
  }
}

void setLedOn(int ledPin) {
  digitalWrite(ledPin, LOW);
}

void readButtons() {
  buttonsState.up = digitalRead(buttonsPins.up);
  buttonsState.down = digitalRead(buttonsPins.down);
  buttonsState.callibrate = digitalRead(buttonsPins.callibrate);
}

void callibrate() {
  if (position != 0) {
    position = 0;
    Serial.write("cal=0");
  }
}

// the loop function runs over and over again forever
void loop() {

  readButtons();

  if (buttonsState.callibrate == LOW) {
    callibrate();
  }

  setLed(LedType::RED, buttonsState.down);
  setLed(LedType::YELLOW, buttonsState.up);

  measureCurrent();
  updateMotor();

  if (Serial.available()) {
    int inByte = Serial.read();

    uint8_t ledState = (inByte == '0') ? LOW : HIGH;
    digitalWrite(LED_BUILTIN, ledState);

    if (inByte == '0') {
      motorState.expected = 0;
    } else if (inByte == '1') {
      motorState.expected = 50;
    } else if (inByte == '2') {
      motorState.expected = 150;
    } else if (inByte == '3') {
      motorState.expected = 255;
    } else if (inByte == '4') {
      motorState.expected = -50;
    } else if (inByte == '5') {
      motorState.expected = -150;
    } else if (inByte == '6') {
      motorState.expected = -255;
    }

    // yellow led
    if (inByte == 'a') {
      setLed(LedType::YELLOW, LED_ON);
    } else if (inByte == 'z') {
      setLed(LedType::YELLOW, LED_OFF);
    }

    // red pin
    if (inByte == 's') {
      setLed(LedType::RED, LED_ON);
    } else if (inByte == 'x') {
      setLed(LedType::RED, LED_OFF);
    }

  }
}

// leds constants
struct LedPins {
  int yellow;
  int red;
  int builtIn;
};
const LedPins ledPins = {6, 7, LED_BUILTIN};

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

// motor pins
struct MotorPins {
  int pwm;
  int dir;
};
const MotorPins motorPins = {11, 12};


String response;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize motor pins
  pinMode(motorPins.pwm, OUTPUT);
  pinMode(motorPins.dir, OUTPUT);

  // initialize LED pins
  pinMode(ledPins.builtIn, OUTPUT);
  pinMode(ledPins.yellow, OUTPUT);
  pinMode(ledPins.red, OUTPUT);

  setLedOff(ledPins.builtIn);
  setLedOff(ledPins.yellow);
  setLedOff(ledPins.red);

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

void setMotor(int dir, int pwm) {
  analogWrite(motorPins.pwm, pwm);
  digitalWrite(motorPins.dir, dir);
}

void setLedOff(int ledPin) {
  digitalWrite(ledPin, HIGH);
}

void setLedOn(int ledPin) {
  digitalWrite(ledPin, LOW);
}

void readButtons() {
  buttonsState.up = digitalRead(buttonsPins.up);
  buttonsState.down = digitalRead(buttonsPins.down);
  buttonsState.callibrate = digitalRead(buttonsPins.callibrate);
}

// the loop function runs over and over again forever
void loop() {

  readButtons();

  if (buttonsState.down == HIGH) {
    setLedOff(ledPins.red);
  } else {
    setLedOn(ledPins.red);
  }

  if (buttonsState.up == HIGH) {
    setLedOff(ledPins.yellow);
  } else {
    setLedOn(ledPins.yellow);
  }

  measureCurrent();
  // Serial.println(currentValue);

  // delay(50);

  if (Serial.available()) {
    int inByte = Serial.read();

    uint8_t ledState = (inByte == '0') ? LOW : HIGH;
    digitalWrite(LED_BUILTIN, ledState);

    // int motorDir;
    // int motorPwm;
    // if (inByte == '0') {
    //   motorDir = 0;
    //   motorPwm = 0;
    // } else if (inByte == '1') {
    //   motorDir = 0;
    //   motorPwm = 50;
    // } else if (inByte == '2') {
    //   motorDir = 0;
    //   motorPwm = 150;
    // } else if (inByte == '3') {
    //   motorDir = 0;
    //   motorPwm = 250;
    // } else if (inByte == '4') {
    //   motorDir = 1;
    //   motorPwm = 50;
    // } else if (inByte == '5') {
    //   motorDir = 1;
    //   motorPwm = 150;
    // } else if (inByte == '6') {
    //   motorDir = 1;
    //   motorPwm = 250;
    // }
    // setMotor(motorDir, motorPwm);

    // yellow led
    if (inByte == 'a') {
      setLedOn(ledPins.yellow);
    } else if (inByte == 'z') {
      setLedOff(ledPins.yellow);
    }

    // red pin
    if (inByte == 's') {
      setLedOn(ledPins.red);
    } else if (inByte == 'x') {
      setLedOff(ledPins.red);
    }

    delay(50);
  }
}

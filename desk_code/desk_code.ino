#include "button.h"
#include "led.h"
#include "motor.h"
#include "current_sensor.h"
#include "limit_switch.h"

// leds
const Led* yellowLed = new Led(6);
const Led* redLed = new Led(7);
const Led* builtInLed = new Led(LED_BUILTIN);

// buttons
const Button* upBtn = new Button(3);
const Button* downBtn = new Button(4);
const Button* calBtn = new Button(9);

struct ButtonsState {
 int up;
 int down;
 int callibrate;
};
ButtonsState buttonsState = {LOW, LOW, LOW};

// limit switch
const LimitSwitch* lowerLimitSwitch = new LimitSwitch(10);

// current sensor
CurrentSensor *const currentSensor = new CurrentSensor(A0, {537, 3, 5});

// motor
const MotorPins motorPins = {11, 12};
const MotorConstants motorConstants = {10};
Motor *const motor = new Motor(motorPins, motorConstants);

struct MotorState {
  int actual;
  int expected;
};
MotorState motorState = {0, 0};

// position
int position = 0;

// loop counter
uint8_t loopCounter = 0;

// response
String response;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize motor
  motor->begin();

  // initialize LEDs
  yellowLed->begin();
  redLed->begin();
  builtInLed->begin();

  // initialize buttons
  upBtn->begin();
  downBtn->begin();
  calBtn->begin();

  // initialize limit switch
  lowerLimitSwitch->begin();

  Serial.begin(9600);
}

void readButtons() {
  buttonsState.up = upBtn->isPressed();
  buttonsState.down = downBtn->isPressed();
  buttonsState.callibrate = calBtn->isPressed();
}

void callibrate() {
  if (position != 0) {
    position = 0;
    Serial.write("cal=0");
  }
}

// the loop function runs over and over again forever
void loop() {

  if (motor->isMovingDown() && lowerLimitSwitch->isPressed()) {
    motor->forceStop();
  }

  readButtons();

  if (buttonsState.callibrate == LOW) {
    callibrate();
  }

  redLed->set(!buttonsState.down);
  yellowLed->set(!buttonsState.up);

  currentSensor->measure();
  motor->update();

  // if (loopCounter == 0) {
  //   Serial.write("current ma=");
  //   Serial.print(currentSensor->movingAverage());
  //   Serial.write("\ncurrent prev=");
  //   Serial.print(currentSensor->previous());
  //   Serial.write("\n");
  // }

  if (Serial.available() && loopCounter == 0) {
    int inByte = Serial.read();

    if (inByte == '0') {
      motor->setSpeed(0);
    } else if (inByte == '1') {
      motor->setSpeed(50);
    } else if (inByte == '2') {
      motor->setSpeed(150);
    } else if (inByte == '3') {
      motor->setSpeed(255);
    } else if (inByte == '4') {
      motor->setSpeed(-50);
    } else if (inByte == '5') {
      motor->setSpeed(-150);
    } else if (inByte == '6') {
      motor->setSpeed(-255);
    }

    // yellow led
    if (inByte == 'a') {
      yellowLed->switchOn();
    } else if (inByte == 'z') {
      yellowLed->switchOff();
    }

    // red pin
    if (inByte == 's') {
      redLed->switchOn();
    } else if (inByte == 'x') {
      redLed->switchOff();
    }

  }

  if (loopCounter > 300) {
  } else {
    loopCounter++;
  }
}

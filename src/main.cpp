#include "button.h"
#include "led.h"
#include "motor.h"
#include "current_sensor.h"
#include "limit_switch.h"
#include "components.h"
#include "position.h"
#include "state/command_controller.h"
#include "Arduino.h"

// leds
Led yellowLed(6);
Led redLed(7);
Led builtInLed(LED_BUILTIN);

// buttons
Button upBtn(3);
Button downBtn(4);
Button calBtn(9);

// limit switch
LimitSwitch lowerLimitSwitch(10);

// current sensor
// TODO aszymanski: 600 as the max value is arbitrary. we need to measure first what current
// does the motor consume in case of a short-circuit mode work and adjust the value accordingly
// normal work up = ~44
// normal work down = ~29
// blocked = ~304
CurrentSensor currentSensor(A0, {527, 200, 3, 5});

// motor
MotorPins motorPins = {11, 12};
MotorConstants motorConstants = {10};
Motor motor(motorPins, motorConstants);

// encoder
const int encoderPin = 2;
constexpr unsigned long MIN_PULSE_INTERVAL_US = 1000;

volatile unsigned long lastPulse = 0;
volatile long encoderPulses = 0;

Position position;

void onEncoderPulse() {
    unsigned long now = micros();

    if (now - lastPulse >= MIN_PULSE_INTERVAL_US) {
        encoderPulses++;
        lastPulse = now;
    }
}

// command state controller
Components components = {
  upBtn,
  downBtn,
  motor,
  lowerLimitSwitch,
  currentSensor
};
CommandController controller(components);

// loop counter
uint8_t loopCounter = 0;

// response
String response;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize motor
  motor.begin();

  // initialize LEDs
  yellowLed.begin();
  redLed.begin();
  builtInLed.begin();

  // initialize buttons
  upBtn.begin();
  downBtn.begin();
  calBtn.begin();

  // initialize limit switch
  lowerLimitSwitch.begin();

  // initialize encoder interrupt
  pinMode(encoderPin, INPUT_PULLUP);
  attachInterrupt(
    digitalPinToInterrupt(encoderPin),
    onEncoderPulse,
    RISING
  );

  Serial.begin(9600);
}

void updateButtons() {
  upBtn.update();
  downBtn.update();
  calBtn.update();
}

void updatePosition() {
  noInterrupts();
  long pulses = encoderPulses;
  encoderPulses = 0;
  interrupts();

  if (pulses > 0) {
      position.update(pulses, motor.getDirection());
  }
}

// the loop function runs over and over again forever
void loop() {

  bool lowerLimitActive = lowerLimitSwitch.isPressed();

  if (motor.getDirection() == Direction::DOWN && lowerLimitActive) {
    motor.stopInstant();
  }

  updateButtons();

  controller.update();

  // TODO aszymanski: what information should those diodes present?
  // redLed.set(!downBtn.isPressed());
  // yellowLed.set(!upBtn.isPressed());

  currentSensor.measure();
  motor.update();
  updatePosition();

  // if (Serial.available() && loopCounter == 0) {
  //   int inByte = Serial.read();

  //   if (inByte == '0') {
  //     motor.setSpeed(0);
  //   } else if (inByte == '1') {
  //     motor.setSpeed(50);
  //   } else if (inByte == '2') {
  //     motor.setSpeed(150);
  //   } else if (inByte == '3') {
  //     motor.setSpeed(255);
  //   } else if (inByte == '4') {
  //     motor.setSpeed(-50);
  //   } else if (inByte == '5') {
  //     motor.setSpeed(-150);
  //   } else if (inByte == '6') {
  //     motor.setSpeed(-255);
  //   }

  //   // yellow led
  //   if (inByte == 'a') {
  //     yellowLed.switchOn();
  //   } else if (inByte == 'z') {
  //     yellowLed.switchOff();
  //   }

  //   // red pin
  //   if (inByte == 's') {
  //     redLed.switchOn();
  //   } else if (inByte == 'x') {
  //     redLed.switchOff();
  //   }

  // }

  // if (loopCounter == 255) {
  //   loopCounter = 0;
  //   Serial.print("position = ");
  //   Serial.print(position.getPosition());
  //   Serial.print("\n");

  // Serial.print("crnt raw=");
  // Serial.print(currentSensor.previous());
  // Serial.print(" ma=");
  // Serial.print(currentSensor.movingAverage());
  // Serial.print("\n");
  // } else {
  //   loopCounter++;
  // }

}

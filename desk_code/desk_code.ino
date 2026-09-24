/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

// current sensor constants
int currentSensorPin = A0;
int currentZero = 537;
int currentValue = 0;
int currentSamples = 5;

// motor outputs
int motorPwmPin = 11;
int motorDirPin = 12;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motorPwmPin, OUTPUT);
  pinMode(motorDirPin, OUTPUT);

  Serial.begin(9600);
}

void measureCurrent() {
  currentValue = 0;
  for (int i = 0; i < currentSamples; i++) {
    currentValue += analogRead(currentSensorPin);
  }
  currentValue = currentValue / currentSamples - currentZero;
}

void setMotor(int dir, int pwm) {
  analogWrite(motorPwmPin, pwm);
  digitalWrite(motorDirPin, dir);
}

// the loop function runs over and over again forever
void loop() {
  // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                      // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(1000);                      // wait for a second

  String response;

  measureCurrent();
  // Serial.println(currentValue);

  delay(100);

  if (Serial.available()) {
    int inByte = Serial.read();

    uint8_t ledState = (inByte == '0') ? LOW : HIGH;
    digitalWrite(LED_BUILTIN, ledState);

    int motorDir;
    int motorPwm;
    if (inByte == '0') {
      motorDir = 0;
      motorPwm = 0;
    } else if (inByte == '1') {
      motorDir = 0;
      motorPwm = 50;
    } else if (inByte == '2') {
      motorDir = 0;
      motorPwm = 150;
    } else if (inByte == '3') {
      motorDir = 0;
      motorPwm = 250;
    } else if (inByte == '4') {
      motorDir = 1;
      motorPwm = 50;
    } else if (inByte == '5') {
      motorDir = 1;
      motorPwm = 150;
    } else if (inByte == '6') {
      motorDir = 1;
      motorPwm = 250;
    }
    setMotor(motorDir, motorPwm);
  }
}

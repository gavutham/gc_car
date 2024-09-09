#include <SoftwareSerial.h>

#define rxPin 13
#define txPin 12

#define motorpin1 10
#define motorpin2 9
#define motorpin3 8
#define motorpin4 7

#define speedControlA 11
#define speedControlB 6

#define monitorBaudRate 9600
#define hc05BaudRate 38400

SoftwareSerial bluetooth(txPin, rxPin);
int command = 0;

void forward () {
  digitalWrite(motorpin1, LOW);
	digitalWrite(motorpin2, HIGH);
	digitalWrite(motorpin3, LOW);
	digitalWrite(motorpin4, HIGH);
}
void backward () {
  digitalWrite(motorpin1, HIGH);
	digitalWrite(motorpin2, LOW);
	digitalWrite(motorpin3, HIGH);
	digitalWrite(motorpin4, LOW);
}
void left () {
  digitalWrite(motorpin1, LOW);
	digitalWrite(motorpin2, HIGH);
	digitalWrite(motorpin3, HIGH);
	digitalWrite(motorpin4, LOW);
}
void right () {
  digitalWrite(motorpin1, HIGH);
	digitalWrite(motorpin2, LOW);
	digitalWrite(motorpin3, LOW);
	digitalWrite(motorpin4, HIGH);
}

void stop () {
  digitalWrite(motorpin1, LOW);
	digitalWrite(motorpin2, LOW);
	digitalWrite(motorpin3, LOW);
	digitalWrite(motorpin4, LOW);
}

void setSpeed(int speed) {
  Serial.println(speed);
  analogWrite(speedControlA, speed);
  analogWrite(speedControlB, speed);
}

void setup() {
  Serial.begin(monitorBaudRate);
  while (!Serial) { }
  bluetooth.begin(hc05BaudRate);

	pinMode(motorpin1, OUTPUT);
	pinMode(motorpin2, OUTPUT);
	pinMode(motorpin3, OUTPUT);
	pinMode(motorpin4, OUTPUT);
  pinMode(speedControlA, OUTPUT);
  pinMode(speedControlB, OUTPUT);
  stop();
  setSpeed(0);
}


void loop() { // run over and over
  if (bluetooth.available()) {
    command = bluetooth.read();
    Serial.println(command);
  }

  if ( command >= 1 && command <= 60 ) {
    setSpeed(map(command, 1, 60, 1, 255));
    forward();
  } else if ( command >= 61 && command <= 120 ) {
    setSpeed(map(command, 61, 120, 1, 255));
    backward();
  }

  if ( command >= 121 && command <= 180 ) {
    setSpeed(map(command, 121, 180, 1, 255));
    right();
  } else if ( command >= 181 && command <= 240 ) {
    setSpeed(map(command, 181, 240, 1, 255));
    left();
  }

  if( command == 0 ) {
    setSpeed(0);
    stop();
  }

}

//0023:09:01314A slave id

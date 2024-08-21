#include <SoftwareSerial.h>

#define rxPin 8
#define txPin 9

#define motorpin1 2
#define motorpin2 3
#define motorpin3 4
#define motorpin4 5

#define monitorBaudRate 9600
#define hc05BaudRate 38400

SoftwareSerial bluetooth(txPin, rxPin);
char command = 's';

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
void right () {
  digitalWrite(motorpin1, LOW);
	digitalWrite(motorpin2, HIGH);
	digitalWrite(motorpin3, HIGH);
	digitalWrite(motorpin4, LOW);
}
void left () {
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

void setup() {
  Serial.begin(monitorBaudRate);
  while (!Serial) { }
  bluetooth.begin(hc05BaudRate);

	pinMode(motorpin1, OUTPUT);
	pinMode(motorpin2, OUTPUT);
	pinMode(motorpin3, OUTPUT);
	pinMode(motorpin4, OUTPUT);
  stop();
}


void loop() { // run over and over
  if (bluetooth.available()) {
    command = bluetooth.read();
    Serial.println(command);
  }

  switch (command) {
    case 'f': 
      forward();
      break;
    
    case 'b':
      backward();
      break;

    case 'r': 
      right();
      break;

    case 'l':
      left();
      break;

    case 's':
      stop();
      break;
  }
}

//0023:09:01314A slave id

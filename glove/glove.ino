#include "Wire.h"
#include <MPU6050_light.h>
#include <SoftwareSerial.h>

#define txPin 5
#define rxPin 4

#define monitorBaudRate 9600
#define bluetoothBaudRate 38400

SoftwareSerial bluetooth(txPin, rxPin);
MPU6050 mpu(Wire); //scl@a5, sda@a4
unsigned long timer = 0;

float x = 0, y = 0;
int value = 0;

void send(int command) {
  bluetooth.write(command);
}

void setup() {
  Serial.begin(monitorBaudRate);
  bluetooth.begin(bluetoothBaudRate);

  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) { } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done\n");
}

void loop() {
  mpu.update();

  if ((millis() - timer) > 10) { // print data every 10ms
    x = mpu.getAngleX();
    y = mpu.getAngleY();
    timer = millis();

    if (x > 25) {
      //forward motion - 1 to 60
      if (x > 70) value = 60;
      else value = map(x, 25, 70, 1, 60);
    }
    else if (x < -40) {
      //backward motion - 61 to 120
      Serial.println(x);
      if ( x < -80 ) value = 120;
      else value = map(x, -40, -80, 61, 120);
    }
    if (y > 40) {
      //turn right - 121 to 180
      if ( y > 80 ) value = 180;
      else value = map(y, 40, 80, 121, 180);
    }
    else if (y < -25) {
      //turn left - 181 to 240
      if ( y < -55 ) value = 240;
      else value = map(y, -25, -55, 181, 240);
    }

    if (!(x > 25 || x < -40 || y > 40 || y < -25)) value = 0; //stop

    Serial.println(value);

    send(value);
  }
}
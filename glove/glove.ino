#include "Wire.h"
#include <MPU6050_light.h>
#include <SoftwareSerial.h>

#define txPin 5
#define rxPin 4

#define monitorBaudRate 9600
#define bluetoothBaudRate 38400

SoftwareSerial bluetooth(txPin, rxPin);
MPU6050 mpu(Wire); //scl@a5, sca@a4
unsigned long timer = 0;

float x = 0, y = 0;

void send(char command) {
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
    if (x > 30) send('f');
    else if (x < -40) send('b');
    if (y > 40) send('r');
    else if (y < -40) send('l'); 
    if (!(x > 30 || x < -40 || y > 40 || y < -40)) send('s');
  }
}
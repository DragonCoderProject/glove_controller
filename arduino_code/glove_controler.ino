#include<Wire.h>

const int MPU_ADDRESSE = 0x68;  // I2C address of the MPU-6050
int16_t accelerometer_x [2] = {10000,0}, accelerometer_y[2] = {10000,0}, accelerometer_z[2] = {10000,0};

const int convoluteMotorRight = 8;
const int convoluteMotorLeft = 9;
const int moveMotorForwared = 10;
const int moveMotorBack = 11;

const int firstFinger = 4;
const int secondFinger = 5;
const int thirdFinger = 6;
const int fourthFinger = 7;

int firstFingerStatus = 0;
int secondFingerStatus = 0;
int thirdFingerStatus = 0;
int fourthFingerStatus = 0;
int motorSpeed = 0;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_ADDRESSE);
  Wire.write(0x6B);
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);

  pinMode(firstFinger, INPUT_PULLUP);
  pinMode(secondFinger, INPUT_PULLUP);
  pinMode(thirdFinger, INPUT_PULLUP);
  pinMode(fourthFinger, INPUT_PULLUP);

  /*pinMode(convoluteMotorRight, OUTPUT);
  pinMode(convoluteMotorLeft, OUTPUT);
  pinMode(moveMotorForwared, OUTPUT);
  pinMode(moveMotorBack, OUTPUT);*/
}
void loop(){
firstFingerStatus = digitalRead(firstFinger);
secondFingerStatus = digitalRead(secondFinger);
thirdFingerStatus = digitalRead(thirdFinger);
fourthFingerStatus = digitalRead(fourthFinger);
  
  Wire.beginTransmission(MPU_ADDRESSE);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDRESSE,6,true);  // rquest on 6 register (0x
  accelerometer_x [1] = (Wire.read() << 8 | Wire.read()); // X-axis value
  accelerometer_y [1] = (Wire.read() << 8 | Wire.read()); // Y-axis value
  accelerometer_z [1] = (Wire.read() << 8 | Wire.read()); // Z-axis value
  /*Serial.print(" | ayX = "); Serial.print(accelerometer_x [1]);
  Serial.print(" | ayY = "); Serial.print(accelerometer_y [1]);
  Serial.print(" | ayZ = "); Serial.println(accelerometer_z [1]);*/
  if (firstFingerStatus == HIGH) {
    accelerometer_x [0] = accelerometer_x [1];
    accelerometer_y [0] = accelerometer_y [1];
    accelerometer_z [0] = accelerometer_z [1];
    delay (500);
  }
  if (secondFingerStatus == HIGH) {
    motorSpeed = motorSpeed + 51;
    /*analogWrite (convoluteMotorRight, motorSpeed);
    analogWrite (convoluteMotorLeft, motorSpeed);
    analogWrite (moveMotorForwared, motorSpeed);
    analogWrite (convoluteMotorLeft, motorSpeed);*/
    delay (500);
  }
  if (fourthFingerStatus == HIGH) {
    digitalWrite(convoluteMotorRight, LOW);
    digitalWrite(convoluteMotorRight, LOW);
    digitalWrite(moveMotorForwared, LOW);
    digitalWrite(moveMotorBack, LOW);
    delay (500);
  }
  
  
  Serial.print(" | finger1 = "); Serial.println(firstFingerStatus);
  Serial.print(" | ayX = "); Serial.print(accelerometer_x [0]);
  Serial.print(" | ayY = "); Serial.print(accelerometer_y [0]);
  Serial.print(" | ayZ = "); Serial.println(accelerometer_z [0]);
  
  if(accelerometer_y[1] < (accelerometer_y [0] - 3000)) {
    digitalWrite(convoluteMotorRight, HIGH);
  } else {
      digitalWrite(convoluteMotorRight, LOW);
  }
    
  if (accelerometer_y[1] > (accelerometer_y [0] + 3000)) {
    digitalWrite(convoluteMotorLeft, HIGH);
  } else {
      digitalWrite(convoluteMotorLeft, LOW);
  }

  if(accelerometer_z[1] < (accelerometer_z [0] - 3000)) {
    digitalWrite(moveMotorBack, HIGH);
  } else {
      digitalWrite(moveMotorBack, LOW);
  }
    
  if (accelerometer_z[1] > (accelerometer_z [0] + 3000)) {
    digitalWrite(moveMotorForwared, HIGH);
  } else {
      digitalWrite(moveMotorForwared, LOW);
  }
}


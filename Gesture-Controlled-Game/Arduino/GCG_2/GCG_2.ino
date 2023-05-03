/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;
float angle_threshold= 30;
float x,y,z;

void setup() {
  //initlize serial port
  Serial.begin(9600);
  //initilize I2C
  Wire.begin();

  //initilize MPU
  byte status = mpu.begin();

  delay(500);

  //calibrate MPU
  mpu.calcOffsets();
 

}

void loop() {
  // read raw values and update angles
  mpu.update();
  //use non blocking timer
  if((millis()-timer)>200){ // print data every 100ms
  x= mpu.getAccAngleX(); //get pitch angle
  y= mpu.getAccAngleY(); //get roll angle
  //pitch down
  if(x > angle_threshold-10)
  {
    Serial.println("S");
  }
  //pitch up
  else if (x < - angle_threshold)
  {
    Serial.println("W");
  }
  //roll left
  else if(y > angle_threshold)
  {
    Serial.println("A");
  }
  //roll right
  else if (y < - angle_threshold)
  {
    Serial.println("D");
  }
  //update timer
  timer = millis();  
  }
}

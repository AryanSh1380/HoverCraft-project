


/* Get tilt angles on X and Y, and rotation angle on Z
    Angles are given in degrees
 License: MIT
 */
 //#include "Wire.h"
 #include <MPU6050_light.h>
 #include <Servo.h>

 MPU6050 mpu(Wire);
 unsigned long timer = 0;
Servo myservo; 
#define LED 13

 void setup() {
   Serial.begin(9600);
   Wire.begin();

  myservo.attach(9); 

 byte status = mpu.begin();
   Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while (status != 0) { } // stop everything if could not connect to MPU6050
 Serial.println(F("Calculating offsets, do not move MPU6050"));
   delay(1000);
   mpu.calcOffsets(); // gyro and accelero
   Serial.println("Done!\n");
 }
 void loop() {
   mpu.update();
 if ((millis() - timer) > 10) { // print data every 10ms
     Serial.print("X : ");
     Serial.print(mpu.getAngleX());
     Serial.print("\tY : ");
     Serial.print(mpu.getAngleY());
     Serial.print("\tZ : ");
     Serial.println(mpu.getAngleZ());
     timer = millis();
   }

  if (mpu.getAngleZ() <= 90 || mpu.getAngleZ() >= -90){
    myservo.write(mpu.getAngleZ());      
    delay(15);
  }
  else{
    digitalWrite(LED, HIGH);
  }   

 }

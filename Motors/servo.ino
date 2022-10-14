

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
#define D3 11

float x;

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
    Serial.print(mpu.getAngleZ());
    Serial.print("tX acc : ");
    Serial.print(mpu.getAccX());
     Serial.print("\tY acc : ");
     Serial.print(mpu.getAccY());
     Serial.print("\tZ acc : ");
     Serial.println(mpu.getAccZ());
     timer = millis();
   }
  
 myservo.write(-(mpu.getAngleZ()-90));
  
  if(-(mpu.getAngleZ())>=90 || (-mpu.getAngleZ())<=-90){
    digitalWrite(LED, HIGH);
  } 
  else{digitalWrite(LED, LOW);
  } 

  if(  abs(mpu.getAccX()) < 0.01) {
    analogWrite(D3, 255);
  } else if( abs(mpu.getAccX()) > 1) {
    analogWrite(D3, 0);
  } else if(mpu.getAccX()>=-1 && mpu.getAccX()<=-0.01) {
    x=257.57*mpu.getAccX()+257.57;
    analogWrite(D3,x);    
  } else if(mpu.getAccX()>=0.01 && mpu.getAccX()<=1) {
    x=-257.57*mpu.getAccX()+257.57;
    analogWrite(D3,x);    
  }
  
}

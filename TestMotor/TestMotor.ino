#include<Servo.h>
#include<Wire.h>
 
Servo Motor;
bool begin = false;
//const int motorPin = 4;
 
void setup() {
  Serial.begin(9600);
  Wire.begin();
//pinMode(motorPin, OUTPUT); //GPIO-pinn för motorn
 
  Motor.attach(D7,1000,2000);
  delay(1000);
  Motor.write(0);
  Serial.println("writing 0 for 3 seconds");
  delay(3000);
  //Motor.write(1000);
  //delay(200);
  //Motor.write(10);
  //delay(2000);

 
}
 
void loop() {
  Serial.println("Startar Motor");
  Motor.write(100); //starta motorn
  delay(10000);
  
//delay(10000);
//digitalWrite(motorPin, LOW); //Stoppa motorn
//delay(10000);
}

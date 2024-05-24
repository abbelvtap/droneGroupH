/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.10 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.13.11 or later version;
     - for iOS 1.10.3 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG    

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP8266WIFI_LIB_POINT

#include <ESP8266WiFi.h>

#include<Servo.h>
#include<Wire.h>
 
Servo Motor1;
Servo Motor2;
Servo Motor3;
Servo Motor4;

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "ABB_gym_IOT"
#define REMOTEXY_WIFI_PASSWORD "Welcome2abb"
#define REMOTEXY_SERVER_PORT 6377


#include <RemoteXY.h>

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 80 bytes
  { 255,6,0,0,0,73,0,17,0,0,0,31,2,106,200,200,84,1,1,4,
  0,5,252,17,143,143,126,8,60,60,0,133,26,29,5,210,26,143,143,19,
  7,60,60,0,133,26,31,4,47,28,7,86,93,8,14,36,0,133,26,2,
  42,124,23,52,80,57,37,18,0,137,26,31,31,79,78,0,79,70,70,0 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_02_x; // from -100 to 100
  int8_t joystick_02_y; // from -100 to 100
  int8_t joystick_01_x; // from -100 to 100
  int8_t joystick_01_y; // from -100 to 100
  int8_t slider_01; // from 0 to 100
  uint8_t switch_01; // =1 if switch ON and =0 if OFF

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_01 13

void setup() 
{
  RemoteXY_Init();
  Wire.begin();
  Motor1.attach(D7,1000,2000);
  Motor2.attach(D6,1000,2000);
  Motor3.attach(D5,1000,2000);
  Motor4.attach(D4,1000,2000);
  // pinMode(PIN_BUTTON_01, OUTPUT);
  // pinMode(motor1, OUTPUT);
  // pinMode(motor2, OUTPUT);
  // pinMode(motor3, OUTPUT);
  delay(1000);
  Motor.write(0);
  Serial.begin(115200); // Initialize serial communication for debugging 
 
  // TODO: you setup code
}

void loop() 
{ 
  RemoteXY_Handler();

  digitalWrite(PIN_BUTTON_01, (RemoteXY.switch_01 == 0) ? LOW : HIGH);
   
  // Read joystick values
  int8_t joy_x1 = RemoteXY.joystick_01_x;
  int8_t joy_y1 = RemoteXY.joystick_01_y;

  int8_t joy_x2 = RemoteXY.joystick_02_x;
  int8_t joy_y2 = RemoteXY.joystick_02_y;

  int8_t slider = RemoteXY.slider_01;
  
  // Print joystick values to serial monitor for debugging
 //Serial.print("Joystick 1 X: ");
 //Serial.print(joy_x1);
 //Serial.print(" Y: ");
 // Serial.println(joy_y1);

  Serial.print("Joystick 2 X: ");
  Serial.print(joy_x2);
  Serial.print(" Y: ");
  Serial.println(joy_y2);

  Serial.print("Slider: ");
  Serial.println(slider);

  
  
  // Example usage of joystick and slider values
  // TODO: Add your logic to control motors based on joystick and slider values

  // For example:
  Motor1.write(map(slider, 0, 100, 0, 255)); // max värde?
  Motor2.write(map(slider, 0, 100, 0, 255));
  Motor3.write(map(slider, 0, 100, 0, 255));
  Motor4.write(map(slider, 0, 100, 0, 255));


  if (joy_x2 < 0){
    Motor3.write(map(slider, 0, 100, 0, 255)-map(-joy_x2, -100, 100, 0, 255));
    Motor4.write(map(slider, 0, 100, 0, 255)-map(-joy_x2, -100, 100, 0, 255));
  }
  else if (joy_x2 > 0){
    Motor1.write(map(slider, 0, 100, 0, 255)-map(joy_x2, -100, 100, 0, 255));
    Motor2.write(map(slider, 0, 100, 0, 255)-map(joy_x2, .100, 100, 0, 255));
  }
  else {
    Motor1.write(map(slider, 0, 100, 0, 255)); // max värde?
    Motor2.write(map(slider, 0, 100, 0, 255));
    Motor3.write(map(slider, 0, 100, 0, 255));
    Motor4.write(map(slider, 0, 100, 0, 255));
  }

  if (joy_y1 < 0){
    Motor2.write(map(slider, 0, 100, 0, 255)-map(-joy_y1, -100, 100, 0, 255));
    Motor4.write(map(slider, 0, 100, 0, 255)-map(-joy_y1, -100, 100, 0, 255));
  }
  else if (joy_y1 > 0){
    Motor1.write(map(slider, 0, 100, 0, 255)-map(joy_y1, -100, 100, 0, 255));
    Motor3.write(map(slider, 0, 100, 0, 255)-map(joy_y1, .100, 100, 0, 255));
  }
  else {
    Motor1.write(map(slider, 0, 100, 0, 255)); // max värde?
    Motor2.write(map(slider, 0, 100, 0, 255));
    Motor3.write(map(slider, 0, 100, 0, 255));
    Motor4.write(map(slider, 0, 100, 0, 255));
  }

  // TODO: you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 
}

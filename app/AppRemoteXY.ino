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

#include <ESP8266WiFi.h>;

// RemoteXY connection settings 
#define REMOTEXY_WIFI_SSID "ABB_gym_IOT"
#define REMOTEXY_WIFI_PASSWORD "Welcome2abb"
#define REMOTEXY_SERVER_PORT 6377


#include <RemoteXY.h>;

#define PIN_LED 12

// RemoteXY GUI configuration  
#pragma pack(push, 1)  
uint8_t RemoteXY_CONF[] =   // 47 bytes
  { 255,3,0,0,0,40,0,17,0,0,0,31,2,106,200,200,84,1,1,2,
  0,1,20,27,69,69,88,11,29,29,0,134,31,0,5,19,124,60,60,80,
  52,25,25,0,2,26,31 };
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  uint8_t button_01; // =1 if button pressed, else =0
  int8_t joystick_01_x; // from -100 to 100
  int8_t joystick_01_y; // from -100 to 100

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
  RemoteXY_Init ();
  pinMode (PIN_BUTTON_01, OUTPUT);
  pinMode (PIN_LED, OUTPUT);

  Serial.begin(115200); // Initialize serial communication for debugging 
 
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_BUTTON_01, (RemoteXY.button_01==0)?LOW:HIGH);
   // Read joystick values
  int8_t joy_x = RemoteXY.joystick_01_x;
  int8_t joy_y = RemoteXY.joystick_01_y;

  int8_t joy_x2 = RemoteXY.joystick_02_x;
  int8_t joy_y2 = RemoteXY.joystick_02_y;

  int8_t slider = RemoteXY.slider_01;
  
  
  // Print joystick values to serial monitor for debugging
  Serial.print("Joystick X: ");
  Serial.print(joy_x);
  Serial.print(" Y: ");
  Serial.println(joy_y);

  Serial.print("Joystick X2: ");
  Serial.print(joy_x2);
  Serial.print(" Y2: ");
  Serial.println(joy_y2);

  Serial.print(" slider: ");
  Serial.println(slider);
  

  // Control LED brightness based on joystick Y position
  int led_brightness = map(joy_y, -100, 100, 0, 255);
  analogWrite(PIN_LED, led_brightness);

  
  // TODO you loop code
  // use the RemoteXY structure for data transfer
  // do not call delay(), use instead RemoteXY_delay() 


}

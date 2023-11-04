/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial



#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "AUTH_TOKEN";


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASSWORD";

int leftCurtain;
int rightCurtain;


BLYNK_WRITE(V0)
{
  leftCurtain = param.asInt(); // assigning incoming value from pin V0 to a variable
  
  if(leftCurtain == 2)
  {
    // Serial.println("Open left curtain!"); //DO NOT UNCOMMENT UNLESS YOU ARE DIRECTLY CONNECTED TO THE WIFI MODULE
                                             //UNCOMMENTED, THE ARDUINO WOULD RECEIVE THE STRINGS, AND THE PROGRAM MISBEHAVE
                                              
    Serial.flush();
    Serial.print(leftCurtain); //flush and not println to avoid sending extra data to serial
    
  }
    
  else if(leftCurtain == 1)
  {
    //Serial.println("Close left curtain!");  //DO NOT UNCOMMENT UNLESS YOU ARE DIRECTLY CONNECTED TO THE WIFI MODULE
    Serial.flush();
    Serial.print(leftCurtain); //flush and not println to avoid sending extra data to serial

  }

}

BLYNK_WRITE(V1)
{
  rightCurtain = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if(rightCurtain == 4)
  {
    //Serial.println("Open right curtain"); //DO NOT UNCOMMENT UNLESS YOU ARE DIRECTLY CONNECTED TO THE WIFI MODULE

    Serial.flush();
    Serial.print(rightCurtain);
  }
  else if(rightCurtain == 3)
  {
    //Serial.println("Close right curtain!"); //DO NOT UNCOMMENT UNLESS YOU ARE DIRECTLY CONNECTED TO THE WIFI MODULE

    Serial.flush();
    Serial.print(rightCurtain);
  }

 
}



void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  Serial.flush();
}

void loop()
{
  Blynk.run();

  Serial.flush();

}

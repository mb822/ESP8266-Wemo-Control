# Control WeMo Smart Switch with an ESP8266 

Working implmentation of [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient) and [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) used to get and control the state of your WeMo Smart Light Switch<br/>



Steps: 
 - 1.) Add librarys in Arduino (Sketch -> Include Library -> Add .ZIP Library...)
 - 2.) Create new sketch
 - 3.) Include libraries in stetch<br/>
 ```cpp
 #include <ESP8266WiFi.h>
 #include <ESP8266HTTPClient.h>
 ```
 
 - 4.) Connect to WiFi in setup
 ```cpp
 void setup{
     WiFi.mode(WIFI_STA);
     WiFi.begin(ssid, password);
     while (WiFi.status() != WL_CONNECTED) {
         delay(500);
         Serial.print(".");
     }
 }
 ```
 &nsbp;&nsbp;&nsbp;&nsbp;***(where 'ssid' and 'passowrd' are replaced with that of your network)***
 - 4.) use the folloing functions to get and control the state of your WeMo Light Switch

  ...
 

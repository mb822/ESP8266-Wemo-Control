# Control WeMo Smart Switch with an ESP8266 

Working implmentation of [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient) and [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) used to get and control the state of your WeMo Smart Light Switch<br/>



Steps: 
 - 1.) Add librarys in Arduino (Sketch -> Include Library -> Add .ZIP Library...)
 - 2.) Create new sketch
 - 3.) Include librarys in stetch<br/>
 ```cpp
 #include <ESP8266WiFi.h>```<br/>```#include <ESP8266HTTPClient.h>
 ```
 
 - 4.) Connect to WiFi in setup<br>```void setup {```<br/>    ```Serial.begin(115200)```<br/>    ```Serial.print("connecting to wifi");```<br/>    ```    WiFi.mode(WIFI_STA);```<br/>        ```WiFi.begin(ssid, password);```<br/>        ```while (WiFi.status() != WL_CONNECTED) {```<br/>        ```delay(500);```<br/>        ```Serial.print(".");```<br/>```    }```<br/>```}```
 - 4.) use the folloing functions to get and control the state of your WeMo Light Switch

  ...
 

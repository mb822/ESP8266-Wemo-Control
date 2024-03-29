# Control WeMo Smart Switch with an ESP8266 

## Implementation of [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient) and [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi) used to get and control the state of your WeMo Smart Light Switch<br/><br/>

Steps: 
 - 1.) Add libraries in Arduino (Sketch -> Include Library -> Add .ZIP Library...)
 - 2.) Create new sketch
 - 3.) Include libraries in sketch<br/>
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
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;***(where 'ssid' and 'password' are replaced with that of your network)***
 - 4.) use the following functions to get and control the state of your WeMo Light Switch
```cpp
int getState(String deviceIP){
    HTTPClient http;
    http.begin("http://" + deviceIP + ":49153/upnp/control/basicevent1");
    http.addHeader("Accept-Encoding", "identity");
    http.addHeader("Content-Length", "306");
    http.addHeader("Content-Type", "text/xml");
    http.addHeader("SOAPACTION", "\"urn:Belkin:service:basicevent:1#GetBinaryState\"");
    http.POST("<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><u:GetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"></u:GetBinaryState></s:Body></s:Envelope>");
    return http.getString().substring(216,217).toInt();
}
```
```cpp
void setState(String deviceIP, int state){
    HTTPClient http;
    http.begin("http://" + deviceIP + ":49153/upnp/control/basicevent1");
    http.addHeader("Content-Type", "text/xml");
    http.addHeader("SOAPACTION", "\"urn:Belkin:service:basicevent:1#SetBinaryState\"");
    http.POST("<?xml version=\"1.0\" encoding=\"utf-8\"?> <s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"><BinaryState>" + String(state) +"</BinaryState></u:SetBinaryState></s:Body></s:Envelope>");
    http.end();
}
```
```cpp
void toggleState(String deviceIP){
    HTTPClient http;
    http.begin("http://" + deviceIP + ":49153/upnp/control/basicevent1");
    http.addHeader("Content-Type", "text/xml");
    http.addHeader("SOAPACTION", "\"urn:Belkin:service:basicevent:1#SetBinaryState\"");
    http.POST("<?xml version=\"1.0\" encoding=\"utf-8\"?> <s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"><BinaryState>" + String(abs(getState(deviceIP)-1)) +"</BinaryState></u:SetBinaryState></s:Body></s:Envelope>");
    http.end();
}
```

***Note: if device ip address is unknown, you can run [find_wemo_ip.py](https://github.com/mb822/esp8266WemoExample/blob/main/find_wemo_ip.py) to find it***



<br/><br/>
### Sample Use:<br/>
## &nbsp;&nbsp;&nbsp;&nbsp;[Wireless WeMo Light Switch Remote](https://github.com/mb822/esp8266WemoExample/blob/main/esp8266_wemo_remote.cpp)


<div style="display: inline-block">
  <img width="45%" min-width="350px" style="min-width: 350px !important" alt="na" src="https://user-images.githubusercontent.com/70653539/130304906-9a8e7300-9da2-462f-bbe3-63a2fef1d22e.png">
  <img width="45%" min-width="350px" style="min-width: 350px !important" alt="na" src="https://raw.githubusercontent.com/mb822/esp8266WemoExample/main/esp8266_wemo_remote_drawing.png">
</div>

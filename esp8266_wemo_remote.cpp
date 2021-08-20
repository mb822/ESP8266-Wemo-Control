#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "OneButton.h"

//simple esp8266 remote that toggles a WeMo Smart Light Switch.

//      momentary push button completes circuit
//      upon startup, esp8266 powers relay which permanently completes circuit such that the push button can be released
//      esp8266 uses POST requests to get and toggle and state of the WeMo Light Switch
//      upon toggle completion, the esp8266 turns the relay off, turning itself off

//since the esp8266 is completely off most of the time, this remote can preform well nearly 2000 toggles on a 200 mAh battery (on average)
//unfortuanly the ESP8266WiFi library is quite slow - which means that reconnecting to WiFi does take a few seconds - about 5 - although this disadvantage comes with the advantage of no standy current draw

//scehamtic provided in github repo 


const char* ssid = "ssid";                        //change to your ssid
const char* password = "password";                //change to your password


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);                   //set built in LED pin as output
  digitalWrite(LED_BUILTIN, LOW);                 //turn built in LED on when remote is active

  pinMode(15, OUTPUT);                            //set relay pin as output
  digitalWrite(15, HIGH);                         //turn on relay
  
  Serial.begin(115200);

  Serial.print("connecting to network");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);                     //connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop() {
  HTTPClient http;
  //getState
  http.begin("http://10.0.0.15:49153/upnp/control/basicevent1");          //replace ip with your device's ip
  http.addHeader("Accept-Encoding", "identity");
  http.addHeader("Content-Length", "306");
  http.addHeader("Content-Type", "text/xml");
  http.addHeader("SOAPACTION", "\"urn:Belkin:service:basicevent:1#GetBinaryState\"");
  http.POST("<?xml version=\"1.0\" encoding=\"utf-8\"?><s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\"><s:Body><u:GetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"></u:GetBinaryState></s:Body></s:Envelope>");
  //invert currect state
  http.begin("http://10.0.0.15:49153/upnp/control/basicevent1");          //replace ip with your device's ip
  http.addHeader("Content-Type", "text/xml");
  http.addHeader("SOAPACTION", "\"urn:Belkin:service:basicevent:1#SetBinaryState\"");
  http.POST("<?xml version=\"1.0\" encoding=\"utf-8\"?> <s:Envelope xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"><s:Body><u:SetBinaryState xmlns:u=\"urn:Belkin:service:basicevent:1\"><BinaryState>" + String(abs(ttp.getString().substring(216,217).toInt()-1)) +"</BinaryState></u:SetBinaryState></s:Body></s:Envelope>");
  http.end();

  digitalWrite(15, LOW);                        //turn relay off (turn esp8266 off)
}
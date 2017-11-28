#include <ESP8266WiFi.h>
#include "EmonLib.h"
#include <Wire.h>
#include <SPI.h>
EnergyMonitor emon1;
const char* server = "Domoticz_IP";
const char* url;
//WIFI credentials go here
const char* ssid     = "Wifi_SSID";
const char* password = "SSID_Password";
WiFiClient client;

void setup() {
Serial.begin(115200);//sets the baud rate
delay(10);
// We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  emon1.current(A0, 30);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(60000);
  double Irms = emon1.calcIrms(1480);
  Serial.println("Test");
  if (client.connect(server,3434)) {  //   "184.106.153.149" or api.thingspeak.com
     //Serial.println("Connect");
     client.print("GET /json.htm?type=command&param=udevice&idx=257&nvalue=0&svalue=");
     client.print(Irms*232.0);
     client.print(";");
     // add *232.0 to test
     client.print(Irms*232.0);
     client.print(" HTTP/1.1\r\n"); 
     client.print("Host: www.local.lan\r\n"); 
     client.print("Connection: keep-alive\r\n"); 
     client.print("Accept: */*\r\n\r\n"); 
  }
client.stop();
}

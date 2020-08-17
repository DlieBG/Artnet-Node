#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "Schwering Software Artnet Node"
#define APPSK  "Schwering Software"
#endif

const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

void setup() {
  delay(1000);
  Serial.begin(9600);
  
  WiFi.softAP(ssid, password);
  
  server.on("/", []() {
    server.send(200, "text/html", index());
  });
  server.on("/script.js", []() {
    server.send(200, "text/javascript", script());
  });
  server.on("/style.css", []() {
    server.send(200, "text/css", style());
  });
  server.on("/set", []() {
    Serial.println(server.arg(server.argName(0)));
    server.send(200, "text/css", server.arg(server.argName(0)));
  });
  
  
  server.begin();
}

void loop() {
  server.handleClient();
}

#include "ESP8266v1.h"

#define RX_PIN 2
#define TX_PIN 3
#define LED   13

ESP8266v1 esp(RX_PIN, TX_PIN);

String wifiName = "TigonCoffee2",
       wifiPass = "tigon2136",
       staIP = "192.168.1.119";
       
String html = "<html>"
              "<head>"
              "<title>"
              "TestESP"
              "</title>"
              "</head>"
              "<body>"
              "<form method=\"GET\">"
              "<button type=\"submit\" name=\"led\" value=\"on\">Turn ON</button>"
              "<button type=\"submit\" name=\"led\" value=\"off\">Turn OFF</button>"
              "</form>"
              "</body>"
              "</html>";
              
String resp = "";
            
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  esp.init();
  esp.joinAP(wifiName, wifiPass);
  esp.setIP(staIP);
  Serial.println(esp.getIP());
  esp.startServer();
}

void loop() {
  esp.getFromServer(resp, html);
  if(resp.indexOf("led=on") != -1){
    digitalWrite(13, HIGH);
  }
  else if(resp.indexOf("led=off") != -1){
    digitalWrite(13, LOW);
  }
}

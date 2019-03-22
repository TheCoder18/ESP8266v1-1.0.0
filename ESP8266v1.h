/************************************************************************
*************************************************************************
******* Library for using ESP8266v01 with Arduino - Version 1.0.0 *******
******* Created by: Minh Luong on June 27 2018 **************************
*************************************************************************
*************************************************************************/

#include <Arduino.h>
#include <SoftwareSerial.h>

class ESP8266v1: public SoftwareSerial{
public:
  // constructor function
  // map RX pin and TX pin for Software Serial
  // default RX pin is 2 and default TX pin is 3
  ESP8266v1(int rxPin = 2, int txPin = 3);
  
  // initialize object ESP8266
  void init();
  
  // send a command to ESP8266 module through UART
  String sendCmd(String cmd, int timeout);
  
  // set access point name and password for ESP8266
  // ESP8266 as a server
  void setAP(String apName, String apPass);
  
  // set ESP8266 to join an available WiFi
  void joinAP(String apName, String apPass);
  
  // start server on ESP8266 module
  // default port is 80
  void startServer(int port = 80);
  
  // get station IP of ESP8266
  String getIP();
  
  // set station IP for ESP8266
  void setIP(String ip);
  
  // get data from server when a client access server
  void getFromServer(String& resp, String html1 = "", String html2 = "");
};
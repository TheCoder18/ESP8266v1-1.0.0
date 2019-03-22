/**************************************************************************
**************** Definition of methods in class ESP8266 *******************
***************************************************************************/

#include "ESP8266v1.h"

ESP8266v1::ESP8266v1(int rxPin = 2, int txPin = 3): SoftwareSerial(rxPin, txPin) {}

void ESP8266v1::init(){
  this->begin(9600);
  Serial.println(this->sendCmd("AT+RST\r\n", 4000));
  Serial.println(this->sendCmd("AT+CWMODE=3\r\n", 1500));
}

String ESP8266v1::sendCmd(String cmd, int timeout){
  this->flush();
  String resp = "";
  this->print(cmd);
  long long tmp = millis();
  while(millis() - tmp < timeout){
    if(this->available()){
      resp += (char) this->read();
    }
  }
  return resp;
}

void ESP8266v1::setAP(String apName, String apPass){
  String resp = "";
  do{
    resp = this->sendCmd(String("AT+CWSAP=\"") + apName + String("\",\"") + apPass + String("\",5,3\r\n"), 2000);
  }
  while(resp.indexOf("OK") == -1);
  Serial.println("Set as Access point successful!!\r\n");
}

void ESP8266v1::joinAP(String apName, String apPass){
  String resp = "";
  do{
    resp = this->sendCmd(String("AT+CWJAP=\"") + apName + String("\",\"") + apPass + String("\"\r\n"), 8000);
  }
  while(resp.indexOf("OK") == -1);
  Serial.println("Join Access point successful!!\r\n");
}

void ESP8266v1::startServer(int port){
  Serial.println(this->sendCmd("AT+CIPMUX=1\r\n", 1500));
  Serial.println(this->sendCmd(String("AT+CIPSERVER=1,") + port + String("\r\n"), 1500));
}

String ESP8266v1::getIP(){
  return this->sendCmd("AT+CIFSR\r\n", 1500);
}

void ESP8266v1::setIP(String ip){
  String resp = "";
  do{
    resp = this->sendCmd(String("AT+CIPSTA=\"") + ip + "\"\r\n", 1500);
  }
  while(resp.indexOf("OK") == -1);
  Serial.println(String("Changed STAIP into ") + ip + String("\r\n"));
}

void ESP8266v1::getFromServer(String& resp, String html1 = "", String html2 = ""){
  while(this->available()){
    char c = this->read();
    switch(c){
      case '\r':
        break;
      case '\n':
        if(resp.indexOf("+IPD,") != -1){
          char connId = resp[resp.indexOf("+IPD,") + 5];
          String cipSend = "AT+CIPSEND=";
          cipSend += connId;
          cipSend += ",";
          cipSend += (html1.length() + html2.length());
          cipSend += "\r\n";
          Serial.println(this->sendCmd(cipSend, 500));
          Serial.println(this->sendCmd(html1, 1000));
          Serial.println(this->sendCmd(html2, 1000));
        }
        resp = "";
        break;
      default:
        resp += c;
    }
  }
}

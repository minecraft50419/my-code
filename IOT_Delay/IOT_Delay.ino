#include <PubSubClient.h>
#include<ESP8266WiFi.h>

//WIFI Setting
const char* ssid = "";
const char* password = "";
//MQTT Server Setting
const char* mqttServer = "mqtt.mcs.mediatek.com" ;
const char* topicPubDis = "mcs/DrASoYYK/hpKCkEjK5wccEHUk/DelayDisplay";
const char* topicPubCtrl = "mcs/DrASoYYK/hpKCkEjK5wccEHUk/DelayControler";
const char* topicSubCtrl = "mcs/DrASoYYK/hpKCkEjK5wccEHUk/DelayControler";
//Define Function
WiFiClient espClient; //Define WiFiClint As espClient
PubSubClient client(espClient); //Define PubSubClient As client
//Sensor Setting
int DelayPin = 1;
String DelayV = "";
//Message Setting
String msgStr = "";


void setup() {
  
WiFi.begin(ssid,password);
client.setServer(mqttServer,1883); //connect to mqttServer

pinMode(DelayPin,OUTPUT);
}

void loop() {

DelayReceive();

}

void DelayReceive() {
  void callback(topicSubCtrl,,unsigned int length){
  
  }
  }

 void DelaySend() {
  if(digitalRead(DelayPin)==HIGH){
    DelayV ="1";
    }


  else if(digitalRead(DelayPin)==LOW){
    DelayV ="0";
    }
  //msg send
  msgStr="topicPubDis,"+DelayV;
  
  byte arrSize = msgStr.length() + 1;
  char msg;
  
  msgStr.toCharArray(msg,arrSize);
  client.publish(topicPubDis,msg);
  msgStr = "";
  }

 void MQTTConnect() {
  
 }

 


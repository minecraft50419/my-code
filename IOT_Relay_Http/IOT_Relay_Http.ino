#include<ESP8266WiFi.h>
#include<ArduinoJson.h>
#include<HttpClient.h>
#include<SPI.h>
//WIFI Setting
const char* ssid = "";
const char* password = "";
//Define Function
WiFiClient espClient;
HttpClient client(espClient);

//Data
String update_data;
int update_dataLength;
String get_data;

int relay_dis;
String relay_con;
int code;
//Senor Setting
int RelayPin ;
String DelayV ="";


void setup(){

WiFi.begin(ssid,password);
pinMode(RelayPin,OUTPUT);

}

void loop(){
    json_resolve();
    GET();
    if(relay_con=="1"){
        digitalWrite(RelayPin,LOW);
    }
    else if(relay_con=="0"){
        digitalWrite(RelayPin,HIGH);
    }

     if(digitalRead(RelayPin)==HIGH && DelayV !="0"){
         DelayV="0";
         Update_();
     } 
     else if(digitalRead(RelayPin)==LOW && DelayV !="1"){
         DelayV="1";
         Update_();
     }
}
void Update_(){
 if(DelayV=="0"){
     update_data="DelayDisplay,,0";
 }
 else if(DelayV=="1"){
     update_data="DelayDisplay,,1";
 }
 client.println("POST /mcs/v2/devices/DrASoYYK/datapoints.csv");
 client.println("Host: api.mediatek.com");
 client.println("deviceKey: hpKCkEjK5wccEHUk");
 client.println("appId:275570606367235");
 client.println("appSecret:bOiCDSjm3iTOWiW8GVM1JtDcs4hYEHiH");
 client.print("Content-Length: ");
 client.println(update_dataLength);
 client.println("Content-Type: text/csv");
 client.println("Connection: close");
 client.println();
 client.println(update_data);
}

void GET(){
 client.println("GET /mcs/v2/devices/DrASoYYK/datapoints");
 client.println("Host: api.mediatek.com");
 client.println("deviceKey: hpKCkEjK5wccEHUk");
 client.println("appId: 275570606367235");
 client.println("appSecret:bOiCDSjm3iTOWiW8GVM1JtDcs4hYEHiH");
 client.println("Content-Length: 222 ");
 client.println("Content-Type: /csv");
 client.println("Connection: close");
 client.println();
 client.println(get_data);
 
}

void json_resolve(){
  DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(get_data);
    relay_con=root["value"].as<String>();
}

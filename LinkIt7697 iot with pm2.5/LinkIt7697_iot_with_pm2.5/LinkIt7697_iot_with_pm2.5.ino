#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"
#include <DHT.h>
#include <LRemote.h>

//DHT setting
#define dhtPin 8      //DHT11 Data pin
#define dhtType DHT11 //type DHT11 
DHT dht(dhtPin, dhtType); 

int h,t;

//LED setting
int RLED;  //RLED pin
int GLED;  //GLED pin
int BLED;  //BLED pin

//PM2.5 setting
int samplingTime = 280;
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2; //Connect 3 led driver pins of dust sensor to Arduino D2int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
int PM;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

//WiFi setting
#define _SSID "HTC U11"
#define _KEY  "0970758296"

//MCS setting
MCSDevice mcs("your_device_id", "your_device_key");

MCSDisplayInteger PMvalue("pm25");
MCSDisplayInteger Tvalue("Tvalue");
MCSDisplayInteger Hvalue("Hvalue");

//Remote setting
LRemoteLabel HLabel;
LRemoteLabel TLabel;
LRemoteLabel PMLabel;

void setup(){

    Serial.begin(9600);
    dht.begin();

    pinMode(ledPower,OUTPUT);

    //RGB Pin
    pinMode(RLED,OUTPUT);
    pinMode(BLED,OUTPUT);
    pinMode(GLED,OUTPUT);

    //Setup Remote
    LRemote.setName("7697Sensor");
    LRemote.setOrientation(RC_PORTRAIT);
    LRemote.setGrid(2, 5);

    HLabel.setText("0 persent");
    HLabel.setPos(0,0);
    HLabel.setSize(2,1);
    HLabel.setColor(RC_ORANGE);
    LRemote.addControl(HLabel);

    TLabel.setText("0 C");
    TLabel.setPos(0,2);
    TLabel.setSize(2,1);
    TLabel.setColor(RC_BLUE);
    LRemote.addControl(TLabel);

    PMLabel.setText("0 ug/m3");
    PMLabel.setPos(0,4);
    PMLabel.setSize(2,1);
    PMLabel.setColor(RC_GREEN);
    LRemote.addControl(PMLabel);

}

void loop(){
    HTvalue();
    pm25();

    LEDcontrol();
    
    if(LRemote.connected()==true){
    LRemote.process();
    RemoteUpadte();       
    }
    if(WL_CONNECTED == WiFi.status()){
        UpdateMCS();
    }



}

void pm25(){
    digitalWrite(ledPower,LOW); // power on the LED
    delayMicroseconds(samplingTime);
  
    voMeasured = analogRead(measurePin); // read the dust value
  
    delayMicroseconds(deltaTime);
    digitalWrite(ledPower,HIGH); // turn the LED off
    delayMicroseconds(sleepTime);

    calcVoltage = voMeasured * (5.0 / 1024.0);
    dustDensity = 0.17 * calcVoltage - 0.1;

    PM=dustDensity*1000;
    
    delay(5000);

}

void HTvalue(){
    h = dht.readHumidity();//get humidity value
    t = dht.readTemperature();//get Temperature value
}

void LEDcontrol(){
    if(dustDensity<=1000){
        digitalWrite(GLED,HIGH);
        digitalWrite(RLED,LOW);
        digitalWrite(BLED,LOW);
    }
    if(dustDensity<=2000 && dustDensity>1000){
        digitalWrite(GLED,HIGH);
        digitalWrite(RLED,HIGH);
        digitalWrite(BLED,LOW);
    }
    if(dustDensity>2000){
        digitalWrite(GLED,LOW);
        digitalWrite(RLED,HIGH);
        digitalWrite(BLED,LOW);
    }
}

void UpdateMCS(){
    Hvalue.set(h);
    Tvalue.set(t);
    PMvalue.set(PM);
}

void RemoteUpadte(){
    String h1 (h," persent");
    String h2 (t," C");

    HLabel.updateText(h1);
    TLabel.updateText(h2);
    PMLabel.updateText(h3);
    delay(5000);
}

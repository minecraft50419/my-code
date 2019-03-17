#include<SPI.h>
#include<DHT.h>
#include<ESP8266WiFi.h>
#include<ThingerWifi.h>

#define dhtPin 8      //DHT11 Data pin
#define dhtType DHT11 //type DHT11  
#define RLED  //RLED pin
#define GLED  //GLED pin
#define BLED  //BLED pin

#define USERNAME "your_user_name"
#define DEVICE_ID "your_device_id"
#define DEVICE_CREDENTIAL "your_device_credential"

#define SSID "your_wifi_ssid"
#define SSID_PASSWORD "your_wifi_ssid_password"

ThingerWifi thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2
  
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
  
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float PM;

DHT dht(dhtPin, dhtType);

void setup(){
    dht.begin();//啟動DHT
    
    //RGB Setting
    pinMode(RLED,OUTPUT);
    pinMode(BLED,OUTPUT);
    pinMode(GLED,OUTPUT);

    //IOT Connect
    thing.add_wifi(SSID, SSID_PASSWORD);
}
void loop(){
    pm25();

    //get humidity Temperature value
    float h = dht.readHumidity();//get humidity value
    float t = dht.readTemperature();//get Temperature value
    
    Serial.printf(h,f,t,PM);

    
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
    
    delay(1000);

}


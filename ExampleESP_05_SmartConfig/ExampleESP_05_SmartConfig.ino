#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

void setup() {
  int cnt = 0;  

  // set for STA mode
  WiFi.mode(WIFI_STA);
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  // led status at pin16
  pinMode(16,OUTPUT);
  
  //configure pin0 
  pinMode(0, INPUT_PULLUP);

  // deplay for 2 sec for smartConfig
  Serial.println("2 sec before clear SmartConfig");
  delay(2000);
  
  // read pullup
  int isSmartConfig = digitalRead(0);
  if (isSmartConfig==0) {
    // bink for clear config
    blinkClearConfig();
    Serial.println("clear config");
    // reset default config
    WiFi.disconnect();

  }

  // if wifi cannot connect start smartconfig
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(cnt++ >= 15){
       WiFi.beginSmartConfig();
       while(1){
           delay(500);
           if(WiFi.smartConfigDone()){
             Serial.println("SmartConfig Success");
             blinkSmartConfig();
             break;
           }
       }
    }
  }

  Serial.println("");
  Serial.println("");
  
  WiFi.printDiag(Serial);

  // Print the IP address
  Serial.println(WiFi.localIP());

}


void blinkSmartConfig() {
    digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);              // wait for a second 
    digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
    delay(50);
}

void blinkClearConfig() {
  int i=0;
  while(i<=3) {
    digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);              // wait for a second 
    digitalWrite(16, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    i++;
  }
}

void blinkStartConfig() {
  pinMode(16,OUTPUT);
  int i=0;
    digitalWrite(16, HIGH);   // turn the LED on (HIGH is the voltage level)
}


void loop() {
 
  
}
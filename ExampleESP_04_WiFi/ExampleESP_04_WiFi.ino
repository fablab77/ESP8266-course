#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// #include <WiFiClientSecure.h> // Required for HTTPS connections

// Constants
const char *ssid =  "fablab";            // cannot be longer than 32 characters!
const char *pass =  "fablab77";       // WiFi password
const char* chat_server_endpoint = "http://nb3.me/chat/";

//Variables

void setup()
{
 
  Serial.begin(115200);                 //Serial connection
  WiFi.begin(ssid, pass);   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
} // setup

void loop()
{
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin(chat_server_endpoint);      //Specify request destination
   // http.addHeader("Content-Type", "text/plain");  //Specify content-type header
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
   int httpCode = http.POST("username=oleg_esp&chat=Hello,ESP8266!");

   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 } else{
  Serial.println("Error in WiFi connection");   
 }
 
  delay(30000);  //Send a request every 30 seconds
}

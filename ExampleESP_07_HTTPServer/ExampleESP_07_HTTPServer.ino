/*********
  Автор – Руи Сантос (Rui Santos)
  Более подробно о проекте на: http://randomnerdtutorials.com  
*********/
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
     
MDNSResponder mdns;
     
// впишите сюда данные, соответствующие вашей сети:
const char* ssid = "fab";
const char* password = "fablab77";

ESP8266WebServer server(80);	// Стандартный порт, иначе клиенту придётся его указывать явно
 
String webPage = "";
 
int gpio0_pin = 0;
int gpio2_pin = 2;
 
void setup(void){
  webPage += "<h1>ESP8266 Web Server</h1><p>Socket #1 <a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
  webPage += "<p>Socket #2 <a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";
 
  // подготавливаем GPIO-контакты:
  pinMode(gpio0_pin, OUTPUT);
  digitalWrite(gpio0_pin, LOW);
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
 
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Waiting for Wi-Fi connection");
 
  // ждем соединения:
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");  //  "Подключились к "
  Serial.println(ssid);
  Serial.print("IP address: ");  //  "IP-адрес: "
  Serial.println(WiFi.localIP());
 
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");   //  "Запущен MDNSresponder"
  }

  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, HIGH);
    delay(1000);
  });
  server.on("/socket1Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio0_pin, LOW);
    delay(1000);
  });
  server.on("/socket2On", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, HIGH);
    delay(1000);
  });
  server.on("/socket2Off", [](){
    server.send(200, "text/html", webPage);
    digitalWrite(gpio2_pin, LOW);
    delay(1000);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
/*
 * Project IOT Dinas Komunkasi Informasi dan persandian Banyuwangi
 * Nanda Teknik Banyuwangi
 * www.nandateknik.com
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define ARRAYLEN 5

const char* wifiName = "KOMINFO";
const char* wifiPass = "banyuwangiku";
String host = "http://backend.banyuwangikab.go.id/public/api/lampu/";
String group = "A";

static const uint8_t PIN_D0 = 16;
static const uint8_t PIN_D1 = 5;
static const uint8_t PIN_D2 = 4;
static const uint8_t PIN_D3 = 0;
static const uint8_t PIN_D4 = 2;
static const uint8_t PIN_D5 = 14;
static const uint8_t PIN_D6 = 12;
static const uint8_t PIN_D7 = 13;

uint8_t pinIn[ARRAYLEN] = {PIN_D1,PIN_D2,PIN_D5,PIN_D6,PIN_D7};
int pinStatus[ARRAYLEN] = {0,0,0,0,0};

HTTPClient http;    //Declare object of class HTTPClient
WiFiClient client;

void setup() {
  
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifiName);
  WiFi.begin(wifiName, wifiPass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   //You can get IP address assigned to ESP
  
  pinMode(PIN_D1, INPUT);
  pinMode(PIN_D2, INPUT);
  pinMode(PIN_D5, INPUT);
  pinMode(PIN_D6, INPUT);
  pinMode(PIN_D7, INPUT);

}

void postKondisi(int kondisi, int array){
  
  String serverPost = host + "update-kondisi/" + group;

  char json2[2000];        
  DynamicJsonDocument doc(1024); 
  JsonArray data = doc.createNestedArray("data");
  JsonObject data_0 = data.createNestedObject();
  data_0["pin"] = pinIn[array];
  data_0["kondisi"] = kondisi;

  serializeJson(doc, json2);
  Serial.println(json2);

   if ((WiFi.status() == WL_CONNECTED)) {
     
    Serial.print("[HTTP] begin...\n");
    http.begin(client, serverPost);  // HTTP
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    int httpCode = http.POST(json2);

  
    if (httpCode > 0) {
      
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
    const String& payload = http.getString();

    Serial.println("received payload:\n<<");
    Serial.println(payload);
    Serial.println(">>");
    Serial.print("Pin Arduino : ");
    Serial.println(pinIn[array]);
    Serial.print("Array Kondisi : ");
    Serial.println(kondisi);
    pinStatus[array] = kondisi;
    }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void loop() {
  //Cek Status Kondisi Lampu saat ini
   for(int i = 0; i < ARRAYLEN; i++ )
    {
      if(digitalRead(pinIn[i]) == HIGH && pinStatus[i] != 2){
         postKondisi(2,i);
         delay(2000);
      } else if(digitalRead(pinIn[i]) == LOW && pinStatus[i] != 1){
         postKondisi(1,i);
         delay(2000);
      }
    }
  delay(7000);
}
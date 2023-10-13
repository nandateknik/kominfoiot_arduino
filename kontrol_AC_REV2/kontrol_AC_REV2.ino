/*
 *  ESP8266 JSON Decode of server response
 *  -Manoj R. Thkuar
 *  https://circuits4you.com
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#define ARRAYLEN 4

const char* wifiName = "MANGGALAH BAWAH 2G";
const char* wifiPass = "banyuwangiku";
String host = "http://be.banyuwangikab.go.id/public/api/lampu/";
String group = "Z";

static const uint8_t PIN_D5 = 14;
static const uint8_t PIN_D6 = 12;
static const uint8_t PIN_D7 = 13;

int pinStatus = 0;
int pinStatus2 = 0;

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
  
  pinMode(PIN_D5, OUTPUT);
  pinMode(PIN_D6, OUTPUT);
  pinMode(PIN_D7, INPUT);

}

void getLampu(){

  String serverGet = host + "get-group/" + group;

  if(WiFi.status() == WL_CONNECTED){
 
    Serial.print("Request Link: ");
    Serial.println(serverGet);
    
    http.useHTTP10(true);
    http.begin(client,host);
    http.GET();
    String payload = http.getString();

    char json[2000];        
    payload.toCharArray(json, 2000);
    DynamicJsonDocument doc(2000);
    deserializeJson(doc, json);

      int status = doc["data"]["status"]; // 1
      if(status == 1 && pinStatus2 != 1 ) {
        digitalWrite(PIN_D5, HIGH);
        delay(1000);
        digitalWrite(PIN_D6, HIGH);
        pinStatus2 = 1;
        Serial.println(status);
      } else if(status == 2 && pinStatus2 != 2) {
        digitalWrite(PIN_D6, LOW);
        delay(1000);
        digitalWrite(PIN_D5, LOW);
        pinStatus2 = 2;
      }

    http.end();  //Close connection
    }

}

void postKondisi(int kondisi){
  
  String serverPost = host + "update-kondisi/" + group;

  char json2[2000];        
  DynamicJsonDocument doc(1024); 
  JsonObject data = doc.createNestedObject("data");
  data["pin"] = PIN_D7;
  data["status"] = kondisi;

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
    Serial.println(PIN_D7);
    Serial.print("Array Kondisi : ");
    Serial.println(kondisi);
    pinStatus = kondisi;
    }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void loop() {
  
  if(digitalRead(PIN_D7) == HIGH && pinStatus != 2){
      postKondisi(2);
      delay(2000);
  } else if(digitalRead(PIN_D7) == LOW && pinStatus != 1){
      postKondisi(1);
      delay(2000);
  }

  getLampu();
  delay(7000);
}
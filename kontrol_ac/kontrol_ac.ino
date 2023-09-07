/*
 *  ESP8266 JSON Decode of server response
 *  -Manoj R. Thkuar
 *  https://circuits4you.com
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* wifiName = "KOMINFO";
const char* wifiPass = "banyuwangi2023";
String host = "http://be.banyuwangikab.go.id/public/api/lampu/";
String group = "A";

static const uint8_t PIN_D1 = 5;
static const uint8_t PIN_D2 = 4;
static const uint8_t PIN_D3 = 0;
static const uint8_t PIN_D4 = 2;
int statusAC = 0;
int kondisiAC = 0;

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
  
  pinMode(PIN_D1, OUTPUT);
  pinMode(PIN_D2, INPUT);
  pinMode(PIN_D3, OUTPUT);
  pinMode(PIN_D4, OUTPUT);

}

void getAC(){

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
    int data_pin = doc["data"]["pin"]; // 2
    int data_status = doc["data"]["status"]; // 1

    if (data_status == 1 && statusAC == 2) {
      digitalWrite(data_pin,HIGH);
      delay(500);
      digitalWrite(data_pin,LOW);
      delay(500);
      statusAC = 1;
    } else if(data_status == 2 && statusAC == 1){
      digitalWrite(data_pin,HIGH);
      delay(500);
      digitalWrite(data_pin,LOW);
      delay(500);
      statusAC = 2;
    }

    http.end();  //Close connection
    }

}

void postKondisi(int kondisi){
  
  String serverPost = host + "get-group/" + group;

  char json2[2000];        
  DynamicJsonDocument doc(1024); 
  JsonArray data = doc.createNestedArray("data");
  JsonObject data_0 = data.createNestedObject();
  data_0["pin"] = PIN_D1;
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
    Serial.println(PIN_D1);
    Serial.print("Array Kondisi : ");
    Serial.println(kondisi);
    kondisiAC = kondisi;
    }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void loop() {

  if(digitalRead(PIN_D2) == HIGH && kondisiAC == 2){
      postKondisi(2);
      delay(2000);
  } else if(digitalRead(PIN_D2) == LOW && kondisiAC == 1){
      postKondisi(1);
      delay(2000);
  }
  
  getAC();
  delay(7000);
}
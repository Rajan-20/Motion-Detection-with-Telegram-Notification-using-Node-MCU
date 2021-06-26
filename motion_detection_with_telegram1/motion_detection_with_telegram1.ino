
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "rajanmohan";
const char* password = "12348765";

#define BOTtoken "1534947308:AAFPUY3UciF5lddzC2PaOMfrfqFc4WXNl94"

#define CHAT_ID "440355546"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

const int motionSensor = 14; 
bool motionDetected = false;

void ICACHE_RAM_ATTR detectsMovement() {
  //Serial.println("MOTION DETECTED!!!");
  motionDetected = true;
}

void setup() {
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");   
  client.setTrustAnchors(&cert); 

  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot started up", "");
}

void loop() {
  if(motionDetected){
    bot.sendMessage(CHAT_ID, "Motion detected!!", "");
    Serial.println("Motion Detected");
    motionDetected = false;
  }
}

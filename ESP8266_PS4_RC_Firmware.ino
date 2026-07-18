/*
 ESP8266 RC Car - PS4 WebSocket Firmware
 Pins:
 IN1 D1(GPIO5)
 IN2 D2(GPIO4)
 IN3 D5(GPIO14)
 IN4 D6(GPIO12)
 ENA D7(GPIO13)
 ENB D8(GPIO15)

 Install:
  ESP8266WebServer
  WebSocketsServer by Markus Sattler
  ArduinoJson
*/

#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <math.h>

const char* ssid="ESP8266-RC";
const char* pass="12345678";

WebSocketsServer ws(81);

const int IN1=5,IN2=4,IN3=14,IN4=12,ENA=13,ENB=15;

float targetThrottle=0;
float currentThrottle=0;
float steering=0;

const float accelRate=0.03;
const float coastRate=0.015;

unsigned long lastPacket=0;

void stopAll(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  digitalWrite(IN1,0);digitalWrite(IN2,0);
  digitalWrite(IN3,0);digitalWrite(IN4,0);
}

void drive(float throttle,float steer){

  float left=throttle+steer;
  float right=throttle-steer;

  float m=max(fabs(left),fabs(right));
  if(m>1){left/=m;right/=m;}

  bool lf=left>=0;
  bool rf=right>=0;

  digitalWrite(IN1,lf);
  digitalWrite(IN2,!lf);
  digitalWrite(IN3,rf);
  digitalWrite(IN4,!rf);

  analogWrite(ENA,(int)(fabs(left)*255));
  analogWrite(ENB,(int)(fabs(right)*255));
}

void onWS(uint8_t num, WStype_t type, uint8_t *payload, size_t len) {

  if (type != WStype_TEXT) return;

  StaticJsonDocument<128> doc;

  DeserializationError err = deserializeJson(doc, payload, len);
  if (err) return;

  float sx = doc["steer"] | 0.0f;
  float r2 = doc["r2"] | 0.0f;
  float l2 = doc["l2"] | 0.0f;

  if (fabs(sx) < 0.05f) sx = 0;

  steering = sx;

  if (r2 > 0.02f) {
    targetThrottle = r2;
  }
  else if (l2 > 0.02f) {

    if (currentThrottle > 0.05f) {
      targetThrottle = currentThrottle - (l2 * 0.15f);
      if (targetThrottle < 0) targetThrottle = 0;
    } else {
      targetThrottle = -l2;
    }

  } else {
    targetThrottle = 0;
  }

  lastPacket = millis();
}

void setup() {

  Serial.begin(115200);
  delay(500);

  Serial.println();
  Serial.println("Booting...");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopAll();

  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);

  bool ok = WiFi.softAP(ssid, pass);

  Serial.print("softAP: ");
  Serial.println(ok ? "OK" : "FAILED");

  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  ws.begin();
  ws.onEvent(onWS);

  Serial.println("WebSocket Ready");
}

void loop(){

  ws.loop();

  // fail-safe
  if(millis()-lastPacket>300){
    targetThrottle=0;
    steering=0;
  }

  // smooth acceleration
  if(currentThrottle<targetThrottle){
    currentThrottle+=accelRate;
    if(currentThrottle>targetThrottle)
      currentThrottle=targetThrottle;
  }
  else if(currentThrottle>targetThrottle){
    currentThrottle-=coastRate;
    if(currentThrottle<targetThrottle)
      currentThrottle=targetThrottle;
  }

  drive(currentThrottle,steering);
  delay(5);
}

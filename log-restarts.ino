#include <Arduino.h>
#include <SPI.h>
#include "constants.h"
#include "tm.h"
#include "network.h"

Preferences appSettings;

Network network;
TimeManager timeManager;

StateType state = StateType_Idle;

boolean networkConnected = false;
boolean dateSynced = false;

unsigned long currentTime;
unsigned long waitTime;
unsigned long start;
unsigned long timeNow;
unsigned long timeDelay;
unsigned long startupTime;
String str = "";

void setup() {
  Serial.begin(115200);
  pinMode(D2, INPUT_PULLDOWN);
  digitalWrite(D2, LOW);
  pinMode(D2, OUTPUT);
  digitalWrite(D2, LOW);
  start = millis();
  delay(1000);
  
  network.setup();

  blink("none", 1, 100);

  appSettings.begin("log-restarts", false);
}

String logTime() {
  String log = "";
  if (dateSynced) {
    timeNow = (long)timeManager.getNowUTC();
    timeNow = timeNow - round((currentTime - start) / 1000);
    log.concat(timeNow);
  } else {
    log = "Date not synced";
  }
  return log;
}

void blink(String color, int times, long wait) {
  for( int i = 0 ; i < times; i++ ) {

    digitalWrite(LED_BLUE, color == "blue" ? LOW : HIGH);
    digitalWrite(LED_GREEN, color == "green" ? LOW : HIGH);
    digitalWrite(LED_RED, color == "red" ? LOW : HIGH);
    digitalWrite(LED_BUILTIN, HIGH);

    delay(wait);

    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);

    delay(wait);
  }
}

void loop() {
  currentTime = millis();

  if (networkConnected) {
    network.handleClient();
  }

  switch (state) {
    case StateType_Idle:

      blink("blue", 5, 250);

      if (!dateSynced) {
        if (!networkConnected) {
          state = StateType_StartNetwork;
          return;
        } else {
          state = StateType_StartNetwork;
          return;
        }
      }
      return;
    case StateType_StartNetwork:

      blink("green", 5, 100);
      
      if (!networkConnected) {
        networkConnected = network.connect();
        if (!networkConnected) {
          state = StateType_StartHotspot;
          return;
        } else {
          state = StateType_TimeSync;
          return;
        }
      }
      return;
    case StateType_StartHotspot:

      blink("blue", 10, 100);
      
      if (!networkConnected) {
        networkConnected = network.startAP();
        if (!networkConnected) {
          state = StateType_Error;
          return;
        }
      }
      return;
    case StateType_Hotspot:

      blink("blue", 1, 500);
      
      return;
    case StateType_TimeSync:

      blink("blue", 5, 500);
      
      if (!dateSynced) {
        dateSynced = timeManager.sync();
        if (dateSynced) {
           state = StateType_Ready;
          return;
        } else {
          state = StateType_Error;
          return;
        }
      }
      return;
    case StateType_Error:
      blink("red", 5, 500);
      return;
    case StateType_Ready:
      blink("green", 1, 500);

      str = appSettings.getString("RESTARTS", "");
      str.concat(logTime());
      str.concat(";");
      appSettings.putString("RESTARTS", str);
      Serial.println(str);

      waitTime = currentTime;
      state = StateType_Wait;
      return;
    case StateType_Wait:
      if (currentTime - waitTime > 10 * 1000) {
        blink("blue", 3, 100);
        digitalWrite(D2, LOW);
        state = StateType_Sleep;
      }
      return;
    case StateType_Sleep:
      blink("green", 3, 100);
      digitalWrite(D2, HIGH);
      return;
  }
}

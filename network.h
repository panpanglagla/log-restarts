#ifndef NETWORK_H
#define NETWORK_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <StringSplitter.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "css.h"

const static int MAX_WIFIS = 100;
const static int MAX_LOGS = 100;

class Network
{
  private:
    long _i = 0;
    String _header = "";
    String _names[MAX_WIFIS] = {};
    String _passwords[MAX_WIFIS] = {};
    Preferences _settings;
    Preferences _appSettings;
    WebServer _server;
    Css _css;
    
    String getLogs();
    String renderLogs();
    String renderWifiSettings();
    String renderJS();

    void restore();
    void save();
    void setWifi(String wifi, String pwd);
    long getWifiCount();
    void deleteWifis();
    void deleteLogs();

  public:
    Network();
    void setup();
    boolean connect();
    boolean connected();
    boolean startAP();
    void handleClient();
};

#endif
#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#define WIFI_AUTH_OPEN ENC_TYPE_NONE
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Unsupported Board Type. Please use ESP8266 or ESP32"
#endif

#include "Arduino.h"
#include <functional>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <WebSocketsServer.h>
#include <ESPAsyncWebServer.h>

#include "DebugUtils.h"
#include "WifiManagerWebPage.h"


class WifiManager {
private:
	String ssid = "";
	String password = "";
	String authentication = "";
	String accessPointSSID = "";
	String accessPointPassword = "";
	bool connectionState = false;
	unsigned char rstBtnDelaySec = 4;
	unsigned char wifiResetPin;
	unsigned char seedPin;

	void CreateAP();
	void ReadEeprom();
	void EraseEeprom();
	void AppendRandomAPssidSuffix(String prefix);
	bool CheckDuplicateSSID(String ssid);

	String GetAPssid();
	String GetAPpassword();

	static void notFoundHandler(AsyncWebServerRequest* request);
	static void WebSocketEventHandler(uint8_t num, WStype_t type, uint8_t* payload, size_t length);

public:
	WifiManager();
	WifiManager(unsigned char wifiResetPin, unsigned char seedPin);
	~WifiManager();

	void Begin();
	void Begin(std::function<void()> callback);
	bool Connect();
	bool Connect(std::function<void(int)> callback);
	bool SpawnAP(String softap_ssid, String softap_pass);
	void UpdateServer();

	String GetSSID();
	String GetPassword();
	String GetAuthentication();
	bool GetConnectedState();

};

#endif //WIFI_MANAGER_H

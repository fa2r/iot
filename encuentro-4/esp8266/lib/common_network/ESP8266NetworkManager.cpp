#ifdef WIFI
#include "ESP8266WiFi.h"
#include "Arduino.h"
#include "NetworkManager.h"

ESP8266NetworkManager::ESP8266NetworkManager()
{
	WiFiClient client;
	_client = client;
	_ssid = WLAN_SSID;
	_password = WLAN_PASSWORD;
}
WiFiClient& ESP8266NetworkManager::getClient()
{
return _client;
}
IPAddress ESP8266NetworkManager::getIp()
{
return WiFi.localIP();
}

void ESP8266NetworkManager::disconnect() {
	WiFi.disconnect();
	delay(100);
}

void ESP8266NetworkManager::begin() {
	#if DEBUG
		Serial.println("try connect ot the inet ...");
	#endif
	WiFi.begin(_ssid, _password);
	delay(500);
	
	int wifiretrycount = 0;
			
	while (WiFi.status() != WL_CONNECTED && wifiretrycount < 500) {
		delay(500);
		Serial.print(".");
		wifiretrycount ++;
		//digitalWrite(WLANLED, HIGH);
	}
	
	if(WiFi.status() != WL_CONNECTED && wifiretrycount >= 500 )
	{
		//ESP.deepSleep(WIFI_SLEEP_DELAY_IN_SECONDS * 1000000, WAKE_RF_DEFAULT);
		#if DEBUG
			Serial.println("Faild connect to the Wlan go to the deepSleep and retry");
		#endif
		
		delay(100);
	}
	//digitalWrite(WLANLED, LOW);
	
	#if DEBUG
		Serial.println("start Wifi");
		Serial.print("IP:");
		Serial.println(WiFi.localIP());
	#endif
}	
#endif
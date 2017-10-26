#include "Arduino.h"
#include <IPAddress.h>
#include <Client.h>
class NetworkManager
{
	public:
	  	virtual ~NetworkManager() {};
	  	virtual void begin() = 0;
	  	virtual IPAddress getIp() = 0;
	  	virtual void disconnect() = 0;
	private:
	  IPAddress _ip;
};

#include "ESP8266WiFi.h"
class ESP8266NetworkManager : public NetworkManager {
	public:
	    ESP8266NetworkManager();
	  	virtual void begin();
	  	virtual void disconnect();
	  	virtual IPAddress getIp();
	  	virtual WiFiClient& getClient();
	private:
		WiFiClient _client = WiFiClient();
		const char* _ssid;
		const char* _password;
};

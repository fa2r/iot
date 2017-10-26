#ifndef MqttManager_h
#define MqttManager_h

#include <Client.h>
#include <PubSubClient.h>
#include "Arduino.h"

class MqttManager
{
	public:
	  MqttManager(const char* deviceId,const char* mqtt_host,Client& ehtClient);
	  PubSubClient getClient();
	  void checkOrReconnect();
	  void begin();
	  void publish(const char* topic, char* message );
	  void loop();
	  void disconnect();
	private:
	  const char* _deviceId;
	  const char* _mqtt_host;
	  int _mqtt_port;
	  PubSubClient _client;
	  void reconnect();
};

#endif
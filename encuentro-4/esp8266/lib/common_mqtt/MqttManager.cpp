#include "Arduino.h"
#include "MqttManager.h"
#include <PubSubClient.h>
//#include <Ethernet.h>

MqttManager::MqttManager(const char* deviceId,const char* mqtt_host,Client& ethClient)
{
    _deviceId = deviceId;
    _mqtt_host = mqtt_host;
    _mqtt_port = 1883;
	PubSubClient client(ethClient);
	_client = client;
}

void MqttManager::begin()
{
    #if DEBUG
		Serial.println("start mqtt");
		Serial.print("connect to: ");
		Serial.print(_mqtt_host);
		Serial.print(":");
		Serial.println(_mqtt_port);
	#endif
	_client.setServer(_mqtt_host, _mqtt_port);
	delay(100);
}

void MqttManager::loop()
{
	_client.loop();
	delay(100);
}
PubSubClient MqttManager::getClient()
{
	return _client;
}

void MqttManager::disconnect()
{

#ifdef ESPSLEEP
	_client.disconnect();
#endif
	delay(100);
}

void MqttManager::publish(const char* topic, char* message )
{
    #if DEBUG
		Serial.print("Publish to Topic: ");
		Serial.println(topic);
		Serial.print("Message: ");
		Serial.println(message);
	#endif
	_client.publish(topic, message);
	delay(2000);
	#if DEBUG
		Serial.println("Published...");
	#endif
}

void MqttManager::reconnect()
{
	#if DEBUG
		Serial.print("reconnect...");
	#endif
}

void MqttManager::checkOrReconnect()
{
	#if DEBUG
		Serial.println("check connection");
	#endif
	delay(100);
	if (!_client.connected()) {
		#if DEBUG
			Serial.println("not connected try connect");
		#endif
		delay(100);
		while (!_client.connected()) {
			#if DEBUG
				Serial.print("Attempting MQTT connection...");
			#endif
			// Attempt to connect
			if (_client.connect(_deviceId)) {
				#if DEBUG
				    Serial.println("OK");
					Serial.println("Connected to the broker as client:");
					Serial.println(_deviceId);
				#endif
			} else {
				#if DEBUG
					Serial.print("failed, rc=");
					Serial.print(_client.state());
					Serial.println(" try again in 5 seconds");
				#endif
				// Wait 5 seconds before retrying
				delay(5000);
			}
		}
	}

}

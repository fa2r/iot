#include <PubSubClient.h>
#include <NetworkManager.h>
#include <MqttManager.h>

ESP8266NetworkManager networkManager;

char DEVICE_ID[] = MQTT_DEVICE_ID;

MqttManager mqttManager(MQTT_DEVICE_ID,MQTT_HOST,networkManager.getClient());

char MQTT_PATH[] = "/2/temp";

void setup() {
	#if DEBUG
		Serial.begin(9600);
		Serial.println("start NodeMcu Sensor");
	#endif

	networkManager.begin();
	delay(2500);
	mqttManager.begin();
	delay(1000);
	#if DEBUG
		Serial.println("end NodeMcu Sensor");
	#endif
}

int analogPin = A0;     // pin A0 is the ADC
int val = 0;           // variable to store the value read

void loop() {

	mqttManager.checkOrReconnect();
	delay(100);
	mqttManager.loop();

	val = analogRead(analogPin);    // read the input pin
	char value[10];
	sprintf(value,"%d",val);
	mqttManager.publish(MQTT_PATH, value);

	delay(1000);
}

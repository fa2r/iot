#!/usr/bin/python
"""
Agente que obtiene datos provenientes de Arduino por puerto serie, los parsea e
inserta en MQTT
"""

import paho.mqtt.client as paho
import serial
import io
import threading

# Constants
MqttHost = '127.0.0.1'
MqttPort = 1883

DeviceId = 1

SerialPortName = '/dev/ttyUSB0'
BaudRate = 9600

ser = serial.Serial(SerialPortName, baudrate=BaudRate)
ser_io = io.TextIOWrapper(io.BufferedRWPair(ser, ser, 1),
                          newline='\r',
                          line_buffering=True)


def on_message_led(mosq, obj, msg):
    value = str(msg.payload)
    if (value == 'true'):
        ser.write('ledOn')
    else:
        ser.write('ledOff')


def on_message_light(mosq, obj, msg):
    value = str(msg.payload)
    if (value == 'true'):
        ser.write('lightOn')
    else:
        ser.write('lightOff')


def on_message_play(mosq, obj, msg):
    print(msg.topic + " " + str(msg.payload))
    ser.write('play')


def on_message(mosq, obj, msg):
    print(msg.topic + " " + str(msg.payload))


client = paho.Client()

client.message_callback_add('/{}/led/#'.format(DeviceId), on_message_led)
client.message_callback_add('/{}/light/#'.format(DeviceId), on_message_light)
client.message_callback_add('/{}/play/#'.format(DeviceId), on_message_play)
client.on_message = on_message

client.connect(MqttHost, port=MqttPort, keepalive=60, bind_address="")
client.subscribe("/#", 0)


# Insertar en MQTT
def insertData(topic, data):

    topic = '/{}/{}'.format(DeviceId, topic)
    payload = '{}'.format(data)

    client.publish(topic, payload=payload, qos=0, retain=False)


if __name__ == "__main__":

    t = threading.Thread(target=client.loop_forever)
    t.daemon = True
    t.start()

    while(True):
        data = ser_io.readline().strip()
        try:
            (key, value) = data.split(' ')
            insertData(key, value)
            print key, value
        except:
            insertData(data, 'clic')
            print data

    ser.close()

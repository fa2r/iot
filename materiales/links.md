# Materiales para prácticos

## programar-arduino-con-atom-y-platformio-ide

https://www.luisllamas.es/programar-arduino-con-atom-y-platformio-ide/

## LDR

https://www.luisllamas.es/medir-nivel-luz-con-arduino-y-fotoresistencia-ldr/

https://www.prometec.net/ldrs/#modal

## Temperatura LM35

https://www.luisllamas.es/medir-temperatura-con-arduino-y-sensor-lm35/
http://www.internetdelascosas.cl/2012/05/04/midiendo-temperatura-con-arduino-y-lm35/

## Rele

https://www.prometec.net/reles/

http://howtomechatronics.com/tutorials/arduino/control-high-voltage-devices-arduino-relay-tutorial/



# Flashear firmware ESP8266 desde Arduinos
http://blog.theinventorhouse.org/cargar-firmware-al-esp8266-con-arduino/

```C
//sketch para cargar firmware a ESP8266 por medio de Arduino
//Esquematico en
int ch_pd = 3;
int io0 = 2;

void setup() {
  pinMode(ch_pd, OUTPUT);
  pinMode(io0, OUTPUT);
  digitalWrite(io0,LOW);
  digitalWrite(ch_pd, LOW);
  delay(1000);
  digitalWrite(ch_pd, HIGH);
}

void loop()
{

}
```



# MicroPython

http://micropython-iot-hackathon.readthedocs.io/en/latest/projects.html

## tutorials
https://home-assistant.io/blog/2016/07/28/esp8266-and-micropython-part1/
https://home-assistant.io/blog/2016/07/28/esp8266-and-micropython-part2/

## thingflow-python

https://github.com/mpi-sws-rse/thingflow-python/tree/master/micropython

## HomeAssistant
https://home-assistant.io/

## Jupyter

http://jupyter.org/

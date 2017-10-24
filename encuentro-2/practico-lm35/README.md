# Temperatura LM35

Fuente: https://www.luisllamas.es/medir-temperatura-con-arduino-y-sensor-lm35/

## Esquemático

![](images/arduino-LM35-sensor.png)

![](images/arduino-LM35-esquema-electrico.png)

## Montaje

![](images/arduino-LM35-montaje-electrico.png)

## Código de ejemplo


```C
const int sensorPin= A0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(sensorPin);
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10;
  Serial.print(celsius);
  Serial.println(" C");
  delay(1000);
}```

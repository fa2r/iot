# Ejemplo Python

## Instalar dependencias

```bash
sudo pip install -r requirements.txt
```

- `pyserial` Para el acceso al puerto serie
- `paho-mqtt` Implementa la comunicación MQTT


## Ejecución del ejemplo

Antes de ejecutar el ejemplo, editar el código y setear valores para las siguientes constantes:
```python
# Constants
MqttHost = '127.0.0.1'
MqttPort = 1883

DeviceId = 1

SerialPortName = '/dev/ttyUSB0'
BaudRate = 9600
```

### Ejecución

```bash
python arduino_agent.py
```


# Proyecto OpenHAB con MQTT

`/etc/openhab2/items/demo.items `

```
Switch Switch1 {mqtt=">[mosquitto:/office/switch1:command:ON:1],>[mosquitto:/office/switch1:command:OFF:0],<[mosquitto:/office/switch1:state:ON:1],<[mosquitto:/office/switch1:state:OFF:0]"}
Switch Switch2 {mqtt=">[mosquitto:/office/switch2:command:ON:1],>[mosquitto:/office/switch2:command:OFF:0],<[mosquitto:/office/switch2:state:ON:1],<[mosquitto:/office/switch2:state:OFF:0]"}
Number temperature "Temperatura [%.1f ºC]" {mqtt="<[mosquitto:/office/temperature:state:default]"}
Switch doorbell "Timbre [%s]" {mqtt="<[mosquitto:/office/doorbell:command:ON]"}
Number ldr "Luminancia [%.1f Lux]" {mqtt="<[mosquitto:/office/ldr:state:default]"}

```

`/etc/openhab2/sitemaps/demo.sitemap`

```
sitemap demo label="Demo"
{
    Switch item=Switch1 label="Home Light 1"
    Switch item=Switch2 label="Home Light 2"
    Frame label="Sensores" {
        Text item=temperature
        Text item=ldr
        Switch item=doorbell
    }
}
```

## Tópicos MQTT

```bash
$ mosquitto_pub -h 192.168.80.139 -t /office/switch1 -m 1
$ mosquitto_pub -h 192.168.80.139 -t /office/doorbell -m 1
$ mosquitto_pub -h 192.168.80.139 -t /office/temperature -m 23
```

# Documentación OpenHAB
## Configuración

### Items

http://docs.openhab.org/configuration/items.html

```
Switch Kitchen_Light "Kitchen Light" {mqtt="<[...], >[...]" }
String Bedroom_Sonos_CurrentTitle "Title [%s]" (gBedRoom) {channel="sonos:..."}
Number Bathroom_WaschingMachine_Power "Power [%.0f W]" <energy> (gPower) {channel="homematic:..."}

Number Livingroom_Temperature "Temperature [%.1f °C]" <temperature> (gTemperature, gLivingroom) ["TargetTemperature"] {knx="1/0/15+0/0/15"}
```

### Tipos de componentes

http://docs.openhab.org/concepts/items.html


-`Color`: 	Color information (RGB)	[OnOff, IncreaseDecrease, Percent, HSB]
-`Contact`: 	Item storing status of e.g. door/window contacts	[OpenClose]
-`DateTime`: 	Stores date and time
-`Dimmer`: 	Item carrying a percentage value for dimmers	[OnOff, IncreaseDecrease, Percent]
-`Group`: 	Item to nest other items / collect them in groups
-`Image`: 	Holds the binary data of an image
-`Location`: 	Stores GPS coordinates	[Point]
-`Number`: 	Stores values in number format	[Decimal]
-`Player`: 	Allows to control players (e.g. audio players)	[PlayPause, NextPrevious, RewindFastforward]
-`Rollershutter`: 	Typically used for blinds	[UpDown, StopMove, Percent]
-`String`: 	Stores texts	[String]
-`Switch`: 	Typically used for lights (on/off)	[OnOff]

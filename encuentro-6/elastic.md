# Python y ElasticSearch

# Creación del Indice en Elasticsearch



## Snippets
Los siguientes snippets se pueden ejecutar desde la consola **Dev Tools** de **Kibana**


### Eliminación completa del índice

```json
DELETE devices
```

### Tipo de datos para geolocalización

Para la creación de un índice que incluya información de geolocalización se debe especificar el tipo de datos.

```json
PUT devices
{
  "mappings": {
    "event": {
      "properties": {
        "location": {
          "type": "geo_point"
        },
        "timestamp": {
          "type": "date",
          "format":"yyyy-MM-dd HH:mm:ss"
        },
        "_timestamp": {
            "enabled": "true",
            "store": "yes"
        }
      }
    }
  }
}
```


### Insertar eventos con posición geográfica
```json
POST devices/event
{
  "devId": "dev1",
  "text": "Geo-point as an object",
  "timestamp": "2017-06-05 14:18:00",
  "location": {
    "lat": 41.12,
    "lon": -71.34
  }
}

POST devices/event
{
    "devId": "dev1",
    "text": "Geo-point as string",
    "timestamp": "2017-06-05 14:18:10",
    "location": "41.12,-71.34"
}

POST devices/event
{
  "devId": "dev1",
  "text": "Geo-point as a geohash",
  "timestamp": "2017-06-05 14:18:20",
  "location": "drm3btev3e86"
}

POST devices/event
{
  "devId": "dev1",
  "text": "Geo-point as an array",
  "timestamp": "2017-06-05 14:18:30",
  "location": [ -71.34, 41.12 ]
}
```

### Consultar eventos dentro de un área geográfica
```json
GET devices/_search
{
  "query": {
    "geo_bounding_box": {
      "location": {
        "top_left": {
          "lat": 42,
          "lon": -72
        },
        "bottom_right": {
          "lat": 40,
          "lon": -74
        }
      }
    }
  }
}
```



## Ejemplos de búsquedas

### Buscar el último evento de cada Device
```json
GET /devices/event/_search
{
"size": 0,
"query": {
  "terms": {
     "devId":  ["dev1","dev2","dev3"]
  }
},
"aggs": {
  "group_by_country": {
     "terms": {
        "field": "text",
        "size" :0
     },
     "aggs":{
      "top_hits_country"   :{
       "top_hits"   :{
           "size":1
       }
      }
     }
    }
  }
 }
 ```


# Pruebas de búsquedas

### Crear el indice
```json
PUT devices
{
  "mappings": {
    "event": {
      "properties": {
        "location": {
          "type": "geo_point"
        },
        "timestamp": {
          "type": "date"
        },
        "devId": {
          "type": "long"
        }
      }
    }
  }
}
```

### Insertar un evento
```json
POST devices/event
{
    "devId": "5",
    "text": "Actualizacion de posicion",
    "timestamp": "2017-06-06T10:20:50",
    "location": "41.17,-71.34"
}
```
## Búsquedas

### Filtrar dispositivos IDs
```json
GET /devices/event/_search
{
"size": 0,
"query": {
  "terms": {
     "devId":  [1,3,6]
  }
},
"aggs": {
  "group_by_device": {
     "terms": {
        "field": "devId"
     },
     "aggs":{
      "top_hits_device"   :{
       "top_hits"   :{
           "size":1
       }
      }
     }
    }
  }
 }
```
### Obtener los IDs de todos los dispositivos
```json
GET /devices/event/_search
{
"size": 0,
"aggs" : {
    "devs" : {
        "terms" : { "field" : "devId",  "size" : 100 }
    }
}}
```



### Último evento de los dispositivos 1,3,6

```json
GET /devices/event/_search
{
  "size": 0,
  "query": {
    "terms": {
      "devId": [1,3,6]
    }
  },
  "aggs": {
    "group_by_device": {
      "terms": {
        "field": "devId"
      },
      "aggs": {
        "lastEvent": {
          "max": {
            "field": "timestamp"
          }
        }
      }
    }
  }
}
```



### Último evento de cada dispositivo

```json
GET /devices/event/_search
{
  "size": 0,
  "aggs": {
    "group_by_device": {
      "terms": {
        "field": "devId"
      },
      "aggs" : {
        "lastEvent" : {
          "max" : { "field" : "timestamp" }
         }
       }
      }
    }
}
```

o minificado:

```json
GET /devices/event/_search
{"size":0,"aggs":{"group_by_device":{"terms":{"field":"devId"},"aggs":{"lastEvent":{"max":{"field":"timestamp"}}}}}}
```



# Ejemplo Python - ElasticSearch

```bash
sudo apt-get install python-elasticsearch
```


```python
#!/usr/bin/python

import binascii
import struct
import time
from bluepy.bluepy.btle import UUID, Peripheral

from datetime import datetime
from elasticsearch import Elasticsearch
es = Elasticsearch('192.168.80.110')

temp_uuid = UUID(0x2A19)

p = Peripheral("C2:3B:0B:6F:13:0C", "random")

try:
    ch = p.getCharacteristics(uuid=temp_uuid)[0]
    if (ch.supportsRead()):
        while 1:
            val = binascii.b2a_hex(ch.read())
            val = int(val,16)
            print str(val) + ' %'

            doc = {
                "devId": "1",
                "text": "Lectura del nivel bateria",
                "batery": str(val),
                "timestamp": datetime.now(),
                "location": "41.17,-71.34"
            }

            res = es.index(index='ble', doc_type='event', body=doc)
            print(res['created'])

finally:
    p.disconnect()

```

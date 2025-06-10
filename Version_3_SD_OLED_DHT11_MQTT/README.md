# Version 3 - SD + OLED + DHT11 + MQTT

This version logs temperature and humidity from DHT11 to SD card, displays it on OLED, and publishes it to an MQTT broker.
-Publishes (DHT11 data) temperature and humidity to a topic (esp32/dht11/data)
-Subscribe to a control topic (e.g. esp32/dht11/control)
(This version integrates multiple features into one ESP32 project:
- Reads temperature & humidity from DHT11 sensor
- Displays readings on OLED display
- Saves data in  a text file to SD card for local backup, Works even if Wi-Fi is unavailable (SD still logs)
- Publishes data over MQTT for remote monitoring---- Ideal for testing real-time + offline logging for embedded IoT systems.)
#
  

### Features:
- Logs data to SD card
- Shows data on 128x64 OLED
- Publishes data to `esp32/dht11/data` topic via MQTT
- Subscribes to `esp32/dht11/control` 

### MQTT Broker:
Tested with `broker.hivemq.com` (port: 1883)

### Hardware Used:
- ESP32 (main microcontroller to control all)
- DHT11 Sensor
- OLED Display (I2C)
- SD Card Module(stores data in  a text file)
### Libraries required:
-DHT sensor library
-Adafruit SSD1306
-Adafruit GFX
-PubSubClient
-SD, SPI, Wire
### View Live Data on a Dashboard
   Eclipse WebSocket Live MQTT Dashboard.This uses WebSocket to subscribe to topics on public brokers.
 ---Steps:
         Open: https://www.hivemq.com/demos/websocket-client/
---Set parameters:
        Host: mqtt.eclipseprojects.io
        Port: 1883
        Client ID: Any random unique string like esp32_viewer_001
        Click “Connect”
        In "Subscribe to Topic" enter: esp32/dht11/data
        Click “Subscribe”
---Now you'll see live JSON messages from your ESP32!




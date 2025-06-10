# Version 4 – ESP32 SD Card Logger with DHT11 and RTC (Timestamped Logging)

This version of the ESP32 SD card logger adds **timestamping** to the DHT11 sensor logs using a **DS3231 RTC module**. It writes date/time-stamped temperature and humidity data to the SD card.
Here MQTT is not used like version 3 as MQTT (Message Queuing Telemetry Transport) is a network protocol ,used only when you want to publish sensor data to a server/cloud, such as: Batter Monitoring System dashboards,
Remote energy monitoring, Mobile/web apps that subscribe to ESP32 data. MQTT adds extra complexity (Wi-Fi, client setup, topic management), which is not required for offline logging.



##  Components Used
- ESP32 Dev Board
- DHT11 Sensor
- DS3231 RTC Module
- SD Card Module
- Jumper Wires
- Breadboard

## Wiring Overview

![Wiring Diagram](wiring.png)

## Sample Output (From SD Card)


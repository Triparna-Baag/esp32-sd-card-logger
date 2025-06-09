# Version 2: ESP32 + SD Card + OLED + DHT11 Logger

This is Version 2 of ESP32 logging project.
It logs real-time temperature and humidity from a **DHT11 sensor** to a **microSD card** and also displays the data on a **128x64 OLED screen**.
- Logs Temp & Humidity every 5 seconds
- Saves data to `/log.txt` on SD card
- Displays on OLED (Entry number, Temp, Hum)
---

## Hardware Used
- ESP32 Dev Board
- DHT11 Module
- SD Card Module
- 0.96" OLED Display (I2C)
- Jumper Wires, Breadboard

---

##  Features
-Sensor Reading:Uses the DHT library to read temperature and humidity.
-Display Output:OLED screen shows:
                Entry count
                Current temperature
                Current humidity
-Data Logging: Saves each reading to /log.txt on the SD card in this format:t
-Entry 3: Temp = 28.3 C, Humidity = 57.0 %
----Error Handling:
    If DHT fails: prints error and skips loop.
      If SD/OLED initialization fails: displays error and halts.

---
## Flowchart
1)Setup:
  Start Serial, OLED, DHT, and SD card.
  Show SD init result on OLED.
2)Loop (every 5 sec):
    Read sensor values.
    Display on OLED.
    Append data to SD card.
    Wait for 5 seconds.


##  Wiring Diagram
--
DHT11 :
   Connect the DATA pin of DHT11 sensor to GPIO 14 of ESP32(as in your code); GND pin of DHT to GND of ESP32 ; VCC pin of DHT11 to Vin of ESP32.
-- 
OLED :
   Connect Vcc pin of OLED to 3.3V of ESP32; Gnd of OLED to GND of esp32 ; SDA pin of OLED to GPIO21 of ESP32; SCL pin of OLED to GPIO22 of ESP32.
--
SD CARD Module:
   Connect VCC pin of sd_card to Vin of esp32;  Gnd of sd_card to GND of esp32 ; CS (sd card) to GPIO5(esp32); MOSI(sd card) to GPIO23; MISO(sd card) to GPIO19; SCK to GPIO18(esp32).


Important Notes:
Use 3.3V for OLED display , 5V for  SD card module and DHT11 .
Some SD card modules have onboard voltage regulators and level shifters; check your module specs before connecting to 3.3V or 5V.
---


## Flowchart
![Flowchart](flowchart.png)

---

## 🧾 Sample Output

**OLED:**
Entry: 1
Temp: 28.4 C
Humidity: 65.2 %
Entry: 2
Temp: 28.4 C
Humidity: 65.2 % 
..
..


**Serial Monitor:**
Data logged

**SD Log File:**
Entry 5: Temp = 28.4 C, Humidity = 65.2 %


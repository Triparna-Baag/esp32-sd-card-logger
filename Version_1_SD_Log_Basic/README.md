# Version 1 – Basic SD Card Logger with ESP32
A beginner-friendly ESP32 project that logs a simple message to a microSD card via SPI, introducing file systems and data logging basics.

----

##   What It Does

- Initializes a microSD card using the SD library
- Writes a test message to a file named `test.txt`
- Verifies the data by reading it back via Serial Monitor

----

## 🧾 Message Logged
"Triparna's first SD log!"

---
##🔌 Wiring the SD Card Module to ESP32
SD card module communicates with the ESP32 via the SPI interface. Here's a typical wiring configuration:

(SD Card Module Pin <--> 	ESP32 Pin )
      VCC	       <-->       5V ;
      GND          <-->  	GND ;
      MISO         <--> 	GPIO19 ;
      MOSI	       <-->   GPIO23 ;
      SCK          <-->   GPIO18  ;
      CS (SS)	 <-->   GPIO5 .

Ensure that your SD card module is compatible with 3.3V logic levels. Some modules include onboard voltage regulators and level shifters, allowing them to interface safely with the ESP32's 3.3V logic

------
 ### Wiring Diagram
![Wiring Diagram](wiring.png)


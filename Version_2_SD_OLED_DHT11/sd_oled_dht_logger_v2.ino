#include <SPI.h>                 
#include <SD.h>                  
#include <Wire.h>                
#include <Adafruit_GFX.h>       
#include <Adafruit_SSD1306.h>    
#include <DHT.h>                 

// === Pin Definitions ===
#define DHTPIN 14                 // GPIO pin where DHT11 data pin is connected
#define DHTTYPE DHT11             // Define the sensor type as DHT11
#define SD_CS 5                   // GPIO pin for SD card Chip Select (CS)

// OLED display size definitions
#define SCREEN_WIDTH 128          // OLED display width in pixels
#define SCREEN_HEIGHT 64          // OLED display height in pixels

// Create OLED display object using I2C (Wire), no reset pin (-1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Initialize DHT sensor object with defined pin and sensor type
DHT dht(DHTPIN, DHTTYPE);

// Declare a File object for logging data to SD card
File logFile;

// Counter to keep track of number of data entries logged
int entryCount = 0;

void setup() {
  Serial.begin(115200);          // Initialize serial communication at 115200 baud
  dht.begin();                   // Start DHT sensor

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
    Serial.println("OLED initialization failed");
    while (true);                // Stop here if OLED fails to initialize
  }

  // Clear OLED buffer and set text properties
  display.clearDisplay();
  display.setTextSize(1);        // Set text size to 1 (smallest)
  display.setTextColor(SSD1306_WHITE); // Set text color to white

  // Initialize SD card
  if (!SD.begin(SD_CS)) {        // Try to initialize SD card using defined CS pin
    display.println("SD Init Failed");
    display.display();           // Show error message on OLED
    Serial.println("SD card initialization failed!");
    while (true);                // Stop here if SD card initialization fails
  }

  // If SD card initialization is successful
  display.println("SD Init OK");
  display.display();             // Show success message on OLED
  delay(1000);                  // Wait for 1 second before starting main loop
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Check if any reading failed (NaN means failure)
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read DHT");
    return;                     // Skip the rest of the loop if failed to read sensor
  }

  // Increment the entry count for each successful reading
  entryCount++;

  // Display sensor data on OLED screen
  display.clearDisplay();       // Clear previous display contents
  display.setCursor(0, 0);      // Set cursor to top-left corner
  display.printf("Entry: %d\n", entryCount);
  display.printf("Temp: %.1f C\n", temp);
  display.printf("Humidity: %.1f %%\n", hum);
  display.display();            // Send buffer to OLED to update screen

  // Open file on SD card in append mode to add new data without erasing old
  logFile = SD.open("/log.txt", FILE_APPEND);
  if (logFile) {
    // Write formatted string to SD card
    logFile.printf("Entry %d: Temp = %.1f C, Humidity = %.1f %%\n", entryCount, temp, hum);
    logFile.close();            // Close file to save data properly
    Serial.println("Data logged");  // Inform in serial monitor that data was logged
  } else {
    Serial.println("SD write failed");  // Inform if unable to open file for writing
  }

  delay(5000);                 // Wait 5 seconds before next reading
}

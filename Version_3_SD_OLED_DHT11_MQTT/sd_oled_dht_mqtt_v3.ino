#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

// === User WiFi Credentials ===
const char* ssid = "TRIPARNA";
const char* password = "ABC";

// === MQTT Settings ===
const char* mqtt_server = "broker.hivemq.com";  // Public MQTT broker
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/dht11/data"; //Topic to be subscribed

// === Pin Definitions ===
#define DHTPIN 14
#define DHTTYPE DHT11
#define SD_CS 5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// === Objects ===
DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WiFiClient espClient;
PubSubClient client(espClient);
File logFile;

int entryCount = 0;

// === Functions ===
void setup_wifi() {
  delay(100);
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // SD card init
  if (!SD.begin(SD_CS)) {
    display.println("SD Init Failed");
    display.display();
    Serial.println("SD card failed!");
    while (true);
  }
  display.println("SD Init OK");
  display.display();
  delay(1000);

  // WiFi + MQTT init
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT read failed");
    return;
  }

  entryCount++;

  // OLED display
  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("Entry: %d\n", entryCount);
  display.printf("Temp: %.1f C\n", temp);
  display.printf("Humidity: %.1f %%\n", hum);
  display.display();

  // SD card log
  logFile = SD.open("/log.txt", FILE_APPEND);
  if (logFile) {
    logFile.printf("Entry %d: Temp = %.1f C, Humidity = %.1f %%\n", entryCount, temp, hum);
    logFile.close();
    Serial.println("Data logged");
  } else {
    Serial.println("SD write failed");
  }

  // MQTT publish
  char payload[100];
  snprintf(payload, sizeof(payload),
           "{\"entry\":%d,\"temp\":%.1f,\"humidity\":%.1f}",
           entryCount, temp, hum);
  client.publish(mqtt_topic, payload);
  Serial.println("MQTT published: ");
  Serial.println(payload);

  delay(5000);
}

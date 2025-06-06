///This code writes a message to a microSD card connected to the ESP32

#include <SPI.h>    // Include SPI library for communication with SD card
#include <SD.h>     // Include SD library to work with SD card modules

File myFile;       // Create a File object to hold the file reference
const int CS = 5;  // Chip Select pin for SD card module (GPIO5 in this case)

// Function to write a message to a file on the SD card
void WriteFile(const char * path, const char * message){
  myFile = SD.open(path, FILE_WRITE);  // Open the file in write mode (creates if doesn't exist)
  if (myFile) {                        // Check if the file opened successfully
    Serial.printf("Writing to %s ", path);  // Print to serial which file is being written
    myFile.println(message);           // Write the message and add newline to the file
    myFile.close();                    // Close the file to save changes
    Serial.println("completed.");      // Print completion message to serial
  } else {
    Serial.println("error opening file "); // Print error if file can't be opened
    Serial.println(path);
  }
}

// Function to read and print the contents of a file from the SD card
void ReadFile(const char * path){
  myFile = SD.open(path);  // Open the file in read mode (default)
  if (myFile) {            // Check if the file opened successfully
    Serial.printf("Reading file from %s\n", path);  // Print to serial which file is being read
    while (myFile.available()) {  // Loop until all bytes are read
      Serial.write(myFile.read()); // Read one byte and send it to serial monitor
    }
    myFile.close();        // Close the file after reading
  } else {
    Serial.println("error opening test.txt"); // Print error if file can't be opened
  }
}

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud
  delay(500);          // Small delay to let Serial port initialize
  Serial.println("Initializing SD card...");
  
  // Initialize SD card with the chip select pin
  if (!SD.begin(CS)) {  
    Serial.println("initialization failed!");  // Print error if initialization fails
    return;  // Stop further execution in setup if SD card init fails
  }
  
  Serial.println("initialization done.");
  
  // Write a line to the file "test.txt" in SD card root directory
  WriteFile("/test.txt", "Triparna's first SD log!");
  
  // Read and print the contents of the file just written
  ReadFile("/test.txt");
}

void loop() {
  // Nothing happens here after setup
}

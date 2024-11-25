/*
  P5- Interface a soil moisture sensor YL-69 or HL-69 using analog output
  with an Arduino, read the moisture level, and control a water motor
  based on the soil moisture level. Write a program in Embedded C to
  detect and display these values.
*/

// Define the sensor and relay pins
#define sensorPin A0         // Analog pin for soil moisture sensor
#define relayPin 8           // Digital pin for relay module

// Define threshold values for soil moisture
#define soilWet 500          // Value when soil is considered wet
#define soilDry 750          // Value when soil is considered dry

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode (sensorPin, INPUT); // Set relay pin as output
  digitalWrite(relayPin, LOW);      // Initially turn off the relay
  Serial.begin(9600);               // Begin serial communication
}

void loop() {
  int moistureLevel = analogRead(sensorPin); // Read the moisture level
  Serial.print("Soil Moisture Level: ");
  Serial.println(moistureLevel);

  // Check if the soil is too dry
  if (moistureLevel >= soilDry) {
    Serial.println("Soil is too dry - Turning on water pump");
    digitalWrite(relayPin, HIGH);  // Turn on the relay to start the pump
  }
  // Check if the soil moisture is in an acceptable range
  else if (moistureLevel < soilDry && moistureLevel > soilWet) {
    Serial.println("Soil moisture is perfect - Water pump off");
    digitalWrite(relayPin, LOW);   // Turn off the relay to stop the pump
  }
  // If soil is too wet
  else {
    Serial.println("Soil is too wet - Water pump off");
    digitalWrite(relayPin, LOW);   // Turn off the relay to stop the pump
  }

  delay(1000);  // Wait for 1 second before taking another reading
}

/*
  Name : Pratham Katariya
  GR No : 22211592
  Roll No : 311029
  Batch : A2
  Exp 3 b :To interface an LM35 temperature sensor with an Arduino Uno
  Nano, read temperature values, display these values in both Celsius and
  Fahrenheit on an LCD screen and record the readings in an observation table over a period of time.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27 and 16x2 display dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = A0;
float sensorValue;
float voltageOut;
float temperatureC;
float temperatureF;

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
}

void loop() {
  // Read sensor value
  sensorValue = analogRead(sensorPin);
  voltageOut = (sensorValue * 5000) / 1024;
  temperatureC = voltageOut / 10;
  temperatureF = (temperatureC * 1.8) + 32;

  // Print values to Serial Monitor
  Serial.print("Temperature(oC): ");
  Serial.print(temperatureC);
  Serial.print(" Temperature(oF): ");
  Serial.println(temperatureF);

  // Display values on LCD
  lcd.clear();
  
  // Display temperature in Celsius
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  // Display temperature in Fahrenheit
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureF);
  lcd.print((char)223); // Degree symbol
  lcd.print("F");

  delay(1000);
}

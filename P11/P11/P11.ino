/*
  P11- Interface WiFi ESP01/ESP8266 module with Arduino UNO/NANO and con-
trol four LEDs/Relays connected to Arduino board through WiFi module Access
Point (AP) without a router using BLYNK Cloud platform.
*/


// Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL3KG9iEKiZ"
#define BLYNK_TEMPLATE_NAME "Pratham Katariya"
#define BLYNK_AUTH_TOKEN "e7UxWB93JbXmrpVAe5xAP_nNWWz-5tlu"

// Include correct libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define LED pins
#define LED1_PIN D5    // Changed from 8 to D5
#define LED2_PIN D6    // Changed from 9 to D6
#define LED3_PIN D7    // Changed from 10 to D7
#define LED4_PIN D8    // Changed from 11 to D8

// WiFi credentials for AP mode
const char* ssid = "ABC";      // Your ESP8266 AP name
const char* pass = "12345678"; // Added password (minimum 8 characters required)

// This function will be called when LED status changes in Blynk app
BLYNK_WRITE(V1) {
  digitalWrite(LED1_PIN, param.asInt());
}

BLYNK_WRITE(V2) {
  digitalWrite(LED2_PIN, param.asInt());
}

BLYNK_WRITE(V3) {
  digitalWrite(LED3_PIN, param.asInt());
}

BLYNK_WRITE(V4) {
  digitalWrite(LED4_PIN, param.asInt());
}

void setup() {
  // Debug console
  Serial.begin(115200);  // Changed to 115200 for better debugging
  delay(100);           // Increased delay for stability

  // Configure LED pins as outputs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);

  // Set initial LED states to OFF
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  digitalWrite(LED4_PIN, LOW);

  // Configure ESP8266 in Access Point mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);

  Serial.println("\nESP8266 Access Point Mode");
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP Password: ");
  Serial.println(pass);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Using the correct auth token
  Serial.println("Connected to Blynk!");
}

void loop() {
  Blynk.run();
}

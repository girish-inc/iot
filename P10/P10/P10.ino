/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3Y83HTnSi"
#define BLYNK_TEMPLATE_NAME "Relay LED ON OFF"
#define BLYNK_AUTH_TOKEN "Ok0ue45q8flOEWPIaw-s869wH7RLXnjC"
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Access Point (AP) mode credentials
char ssid[] = "ESP8266_AP";  // Access Point SSID
char pass[] = "12345678";    // Access Point Password

// GPIO0 pin setup
#define RELAY_LED_PIN 0 // GPIO0 connected to Relay/LED

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Configure GPIO0 pin
  pinMode(RELAY_LED_PIN, OUTPUT);
  digitalWrite(RELAY_LED_PIN, LOW); // Ensure Relay/LED is OFF initially

  // Start WiFi in Access Point (AP) mode
  WiFi.softAP(ssid, pass);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Initialize Blynk
  Blynk.config(BLYNK_AUTH_TOKEN); // AP mode doesn't need WiFi.begin()
  Blynk.connect();
}

void loop()
{
  Blynk.run();

  // Control Relay/LED via Blynk virtual pin (e.g., V0)
  // Add a Blynk app button connected to V0
  Blynk.virtualWrite(V0, [](bool state) {
    digitalWrite(RELAY_LED_PIN, state ? HIGH : LOW);
  });
}

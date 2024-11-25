/*
  P7- To interface an Infrared (IR) sensor module with an Arduino to de-
  tect and count the presence of objects. The count of detected objects
  will be displayed on a 4-digit 7-segment display using I2C communica-
  tion TM1637.
*/

#include <TM1637Display.h>

// Pin Definitions
int isObstaclePin = 7; // IR sensor input pin
int count = 0; // Object count

// TM1637 Pin Definitions
#define CLK 2  // Clock pin for TM1637
#define DIO 3  // Data pin for TM1637

TM1637Display display(CLK, DIO);

void setup() {
  pinMode(isObstaclePin, INPUT);
  display.setBrightness(0x0f); // Set brightness to max
  display.showNumberDec(0); // Initialize display to 0
  Serial.begin(9600);
}

void loop() {
  int isObstacle = digitalRead(isObstaclePin);

  if (isObstacle == LOW) // Object detected
  {
    count++;
    display.showNumberDec(count); // Display the count on the 7-segment display
    Serial.print("Object Detected! Count: ");
    Serial.println(count);

    // Wait for the object to move away before detecting again
    while (digitalRead(isObstaclePin) == LOW) {
      delay(50);
    }
  }
  else
  {
    Serial.println("No Object Detected");
  }

  delay(200);
}

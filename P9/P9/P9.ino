/*
P9- Implement four-way traffic control system using Arduino/Uno.
*/

// Define the pin numbers for each LED (Red, Yellow, Green) for each lane
int Lane1[] = {13, 12, 11}; // Lane 1 Red, Yellow, and Green LEDs
int Lane2[] = {10, 9, 8};   // Lane 2 Red, Yellow, and Green LEDs
int Lane3[] = {7, 6, 5};    // Lane 3 Red, Yellow, and Green LEDs
int Lane4[] = {4, 3, 2};    // Lane 4 Red, Yellow, and Green LEDs

void setup() 
{
  // Set each LED pin as an output
  for (int i = 0; i < 3; i++) 
  {
    pinMode(Lane1[i], OUTPUT); 
    pinMode(Lane2[i], OUTPUT);
    pinMode(Lane3[i], OUTPUT);
    pinMode(Lane4[i], OUTPUT);
  }

  // Initialize all LEDs to be off
  for (int i = 0; i < 3; i++) 
  {
    digitalWrite(Lane1[i], LOW); 
    digitalWrite(Lane2[i], LOW);
    digitalWrite(Lane3[i], LOW);
    digitalWrite(Lane4[i], LOW);
  }
}

void loop() 
{
  // Lane 1 Green ON, others Red
  digitalWrite(Lane1[2], HIGH); // Lane 1 Green ON
  digitalWrite(Lane3[0], HIGH); // Lane 3 Red ON
  digitalWrite(Lane4[0], HIGH); // Lane 4 Red ON
  digitalWrite(Lane2[0], HIGH); // Lane 2 Red ON
  delay(30000); // Wait for 30 seconds

  // Lane 1 Yellow ON (transition), Green OFF
  digitalWrite(Lane1[2], LOW); // Lane 1 Green OFF
  digitalWrite(Lane1[1], HIGH); // Lane 1 Yellow ON
  delay(5000); // Wait for 5 seconds
  digitalWrite(Lane1[1], LOW); // Lane 1 Yellow OFF
  digitalWrite(Lane2[0], LOW); // Lane 2 Red OFF

  // Lane 2 Green ON, others Red
  digitalWrite(Lane1[0], HIGH); // Lane 1 Red ON
  digitalWrite(Lane2[2], HIGH); // Lane 2 Green ON
  digitalWrite(Lane3[0], HIGH); // Lane 3 Red ON
  digitalWrite(Lane4[0], HIGH); // Lane 4 Red ON
  delay(30000); // Wait for 30 seconds

  // Lane 2 Yellow ON (transition), Green OFF
  digitalWrite(Lane2[2], LOW); // Lane 2 Green OFF
  digitalWrite(Lane2[1], HIGH); // Lane 2 Yellow ON
  delay(5000); // Wait for 5 seconds
  digitalWrite(Lane2[1], LOW); // Lane 2 Yellow OFF
  digitalWrite(Lane3[0], LOW); // Lane 3 Red OFF

  // Lane 3 Green ON, others Red
  digitalWrite(Lane1[0], HIGH); // Lane 1 Red ON
  digitalWrite(Lane2[0], HIGH); // Lane 2 Red ON
  digitalWrite(Lane3[2], HIGH); // Lane 3 Green ON
  digitalWrite(Lane4[0], HIGH); // Lane 4 Red ON
  delay(30000); // Wait for 30 seconds

  // Lane 3 Yellow ON (transition), Green OFF
  digitalWrite(Lane3[2], LOW); // Lane 3 Green OFF
  digitalWrite(Lane3[1], HIGH); // Lane 3 Yellow ON
  delay(5000); // Wait for 5 seconds
  digitalWrite(Lane3[1], LOW); // Lane 3 Yellow OFF
  digitalWrite(Lane4[0], LOW); // Lane 4 Red OFF

  // Lane 4 Green ON, others Red
  digitalWrite(Lane1[0], HIGH); // Lane 1 Red ON
  digitalWrite(Lane2[0], HIGH); // Lane 2 Red ON
  digitalWrite(Lane3[0], HIGH); // Lane 3 Red ON
  digitalWrite(Lane4[2], HIGH); // Lane 4 Green ON
  delay(30000); // Wait for 30 seconds

  // Lane 4 Yellow ON (transition), Green OFF
  digitalWrite(Lane4[2], LOW); // Lane 4 Green OFF
  digitalWrite(Lane4[1], HIGH); // Lane 4 Yellow ON
  delay(5000); // Wait for 5 seconds
  digitalWrite(Lane4[1], LOW); // Lane 4 Yellow OFF
  digitalWrite(Lane1[0], LOW); // Lane 1 Red OFF
}

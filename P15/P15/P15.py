#P15- Design and implement a system to control Raspberry Pi digital outputs using 
# Python by interfacing LEDs with the respective GPIO ports. Utilize either physical (BOARD) 
# or Broadcom (BCM) GPIO numbering.

import RPi.GPIO as GPIO  # Import the GPIO library
import time              # Import the time library for delays

# Pin configuration
LED_PIN = 18  # Use GPIO 18 for the LED

# GPIO setup
GPIO.setmode(GPIO.BCM)        # Use Broadcom GPIO numbering
GPIO.setup(LED_PIN, GPIO.OUT) # Set the pin as an output

try:
    while True:  # Loop to blink the LED
        GPIO.output(LED_PIN, GPIO.HIGH)  # Turn the LED on
        print("LED ON")
        time.sleep(1)                   # Wait for 1 second
        GPIO.output(LED_PIN, GPIO.LOW)  # Turn the LED off
        print("LED OFF")
        time.sleep(1)                   # Wait for 1 second

except KeyboardInterrupt:  # Stop the program when Ctrl+C is pressed
    print("\nExiting program.")

finally:
    GPIO.cleanup()  # Clean up the GPIO pins for reuse

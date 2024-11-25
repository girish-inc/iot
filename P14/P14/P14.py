/*
P14- Control Raspberry Pi Digital input with Python by interfacing DHT11
sensor with respective GPIO ports and monitoring the Temperature and
humidity parameters on screen. Use the GPIO numbering either physi-
cal(BOARD) or Broadcom (BCM).
*/

import Adafruit_DHT
import RPi.GPIO as GPIO
import time

# Set up GPIO using BCM numbering
GPIO.setmode(GPIO.BCM)

# DHT11 sensor type and GPIO pin
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 5  # Use GPIO 5 (BCM)

try:
    while True:
        # Read temperature and humidity from DHT11
        humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)

        # Check if the reading is valid
        if humidity is not None and temperature is not None:
            print(f"Temp: {temperature}°C  Humidity: {humidity}%")
        else:
            print("Failed to retrieve data from sensor")

        # Wait before the next reading
        time.sleep(2)

except KeyboardInterrupt:
    print("Program terminated")

finally:
    GPIO.cleanup()

# P16- Develop a Python program to interface a DHT11 sensor with a Raspberry Pi and create a channel on ThingSpeak loT cloud to monitor and analyze the temperature and humidity data.
import time
import board
import adafruit_dht
import requests
import logging
from datetime import datetime

# Logging configuration
logging.basicConfig(level=logging.INFO, 
                    format='%(asctime)s - %(levelname)s - %(message)s',
                    filename='dht11_monitoring.log')

class DHT11Monitor:
    def __init__(self, 
                 thingspeak_api_key='YOUR_WRITE_API_KEY', 
                 thingspeak_channel_id='YOUR_CHANNEL_ID',
                 temp_threshold=30.0, 
                 humidity_threshold=70.0):
        """
        Initialize DHT11 monitor with ThingSpeak configuration
        
        Args:
            thingspeak_api_key (str): ThingSpeak Write API Key
            thingspeak_channel_id (str): ThingSpeak Channel ID
            temp_threshold (float): Temperature alert threshold in Celsius
            humidity_threshold (float): Humidity alert threshold in percentage
        """
        # ThingSpeak settings
        self.WRITE_API_KEY = thingspeak_api_key
        self.CHANNEL_ID = thingspeak_channel_id
        
        # Sensor settings
        self.dht_sensor = adafruit_dht.DHT11(board.D5)  # Use board.D5 for GPIO5
        
        # Thresholds for alerts
        self.TEMP_THRESHOLD = temp_threshold
        self.HUMIDITY_THRESHOLD = humidity_threshold
        
        # Logging
        self.logger = logging.getLogger(__name__)

    def read_sensor(self):
        """
        Read temperature and humidity from DHT11 sensor
        
        Returns:
            tuple: (humidity, temperature) or (None, None) if reading fails
        """
        try:
            temperature = self.dht_sensor.temperature
            humidity = self.dht_sensor.humidity
            
            return humidity, temperature
        
        except RuntimeError as error:
            # Sensor reading errors are common, log and continue
            self.logger.error(f"Sensor reading error: {error}")
            return None, None
        
        except Exception as error:
            # Unexpected errors
            self.logger.critical(f"Unexpected error: {error}")
            return None, None

    def send_to_thingspeak(self, temp, humidity):
        """
        Send sensor data to ThingSpeak
        
        Args:
            temp (float): Temperature value
            humidity (float): Humidity value
        
        Returns:
            bool: True if data sent successfully, False otherwise
        """
        try:
            url = f'https://api.thingspeak.com/update?api_key={self.WRITE_API_KEY}&field1={temp}&field2={humidity}'
            response = requests.get(url, timeout=10)
            
            if response.status_code == 200:
                self.logger.info(f"Data sent to ThingSpeak - Temp: {temp}°C, Humidity: {humidity}%")
                return True
            else:
                self.logger.warning(f"Failed to send data. Status code: {response.status_code}")
                return False
        
        except requests.RequestException as e:
            self.logger.error(f"Network error while sending data: {e}")
            return False

    def send_alert(self, message):
        """
        Send alert message (placeholder method)
        
        Args:
            message (str): Alert message to be sent
        """
        # Implement your preferred alert mechanism here
        # Options include:
        # 1. Email sending via SMTP
        # 2. SMS via Twilio
        # 3. Telegram/WhatsApp notifications
        # 4. Push notifications
        
        self.logger.warning(f"ALERT: {message}")
        print(f"ALERT: {message}")

    def monitor(self, interval=30):
        """
        Continuous monitoring of temperature and humidity
        
        Args:
            interval (int): Time between readings in seconds
        """
        try:
            while True:
                humidity, temperature = self.read_sensor()
                
                if humidity is not None and temperature is not None:
                    # Send data to ThingSpeak
                    self.send_to_thingspeak(temperature, humidity)
                    
                    # Check and send alerts if thresholds are crossed
                    if temperature > self.TEMP_THRESHOLD:
                        self.send_alert(f"High Temperature: {temperature:.1f}°C")
                    
                    if humidity > self.HUMIDITY_THRESHOLD:
                        self.send_alert(f"High Humidity: {humidity:.1f}%")
                
                # Wait before next reading
                time.sleep(interval)
        
        except KeyboardInterrupt:
            print("\nMonitoring stopped by user.")
        
        finally:
            # Clean up sensor resources
            self.dht_sensor.exit()

def main():
    # Create monitor instance
    monitor = DHT11Monitor(
        thingspeak_api_key='YOUR_WRITE_API_KEY',
        thingspeak_channel_id='YOUR_CHANNEL_ID'
    )
    
    # Start continuous monitoring
    monitor.monitor()

if __name__ == "__main__":
    main()
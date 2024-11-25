#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

class OLEDDisplay {
private:
    Adafruit_SSD1306 display;

public:
    OLEDDisplay() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

    bool begin() {
        Wire.begin();
        if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
            return false;
        }
        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setTextWrap(true);
        display.dim(true);  // Reduce display brightness
        display.display();
        return true;
    }

    void clear() {
        display.clearDisplay();
        display.display();
    }

    // Enhanced text display with multiple styling options
    void displayText(const String& text, uint8_t x = 0, uint8_t y = 0, 
                     uint8_t textSize = 1, bool centered = false) {
        display.clearDisplay();
        display.setTextSize(textSize);
        display.setTextColor(SSD1306_WHITE);

        if (centered) {
            int16_t x1, y1;
            uint16_t w, h;
            display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
            x = (SCREEN_WIDTH - w) / 2;
        }

        display.setCursor(x, y);
        display.println(text);
        display.display();
    }

    // Truly inverted text display
    void displayInvertedText(const String& text, uint8_t x = 0, uint8_t y = 0, 
                              uint8_t textSize = 1, bool centered = false) {
        display.clearDisplay();
        display.setTextSize(textSize);
        
        // Set background to white, text to black for true inversion
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);

        if (centered) {
            int16_t x1, y1;
            uint16_t w, h;
            display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
            x = (SCREEN_WIDTH - w) / 2;
        }

        display.setCursor(x, y);
        display.println(text);
        display.display();
    }

    // Enhanced number display with base conversion
    void displayNumber(long number, uint8_t base = DEC, 
                       uint8_t x = 0, uint8_t y = 0, 
                       uint8_t textSize = 1, bool centered = false) {
        String numStr;
        switch(base) {
            case BIN: numStr = "Bin: " + String(number, BIN); break;
            case OCT: numStr = "Oct: " + String(number, OCT); break;
            case DEC: numStr = "Dec: " + String(number, DEC); break;
            case HEX: numStr = "Hex: " + String(number, HEX); break;
            default:  numStr = String(number);
        }

        display.clearDisplay();
        display.setTextSize(textSize);
        display.setTextColor(SSD1306_WHITE);

        if (centered) {
            int16_t x1, y1;
            uint16_t w, h;
            display.getTextBounds(numStr, 0, 0, &x1, &y1, &w, &h);
            x = (SCREEN_WIDTH - w) / 2;
        }

        display.setCursor(x, y);
        display.println(numStr);
        display.display();
    }

    // Advanced horizontal scrolling with multiple effects
    void scrollHorizontal(const String& text, uint8_t y = 0, 
                           uint8_t textSize = 1, bool rightToLeft = true) {
        int textWidth = text.length() * 6 * textSize;
        int start = rightToLeft ? SCREEN_WIDTH : -textWidth;
        int end = rightToLeft ? -textWidth : SCREEN_WIDTH;
        int step = rightToLeft ? -2 : 2;

        for (int x = start; rightToLeft ? x > end : x < end; x += step) {
            display.clearDisplay();
            display.setTextSize(textSize);
            display.setCursor(x, y);
            display.println(text);
            display.display();
            delay(50);
        }
    }

    // Vertical scrolling with bounce effect
    void scrollVertical(const String& text, uint8_t x = 0, 
                        uint8_t textSize = 1) {
        int textHeight = 8 * textSize;
        
        // Downward scroll
        for (int y = -textHeight; y < SCREEN_HEIGHT; y += 2) {
            display.clearDisplay();
            display.setTextSize(textSize);
            display.setCursor(x, y);
            display.println(text);
            display.display();
            delay(50);
        }
    }

    // Bitmap display with multiple modes
    void displayImage(const uint8_t* bitmap, uint8_t x, uint8_t y, 
                      uint8_t width, uint8_t height, bool inverted = false) {
        display.clearDisplay();
        
        // Option to invert bitmap
        if (inverted) {
            for (int16_t i = 0; i < width * height / 8; i++) {
                display.drawBitmap(x, y, bitmap, width, height, 
                                   SSD1306_BLACK, SSD1306_WHITE);
            }
        } else {
            display.drawBitmap(x, y, bitmap, width, height, SSD1306_WHITE);
        }
        
        display.display();
    }
};

// Sample bitmap (16x16 pixel)
const PROGMEM uint8_t heartBitmap[] = {
    0b00000000, 0b00000000,
    0b01100110, 0b01100110,
    0b11111111, 0b11111110,
    0b11111111, 0b11111110,
    0b01111111, 0b11111100,
    0b00111111, 0b11111000,
    0b00011111, 0b11110000,
    0b00001111, 0b11100000,
    0b00000111, 0b11000000,
    0b00000011, 0b10000000,
    0b00000001, 0b00000000,
    0b00000000, 0b00000000
};

OLEDDisplay oledDisplay;

void setup() {
    Serial.begin(9600);
    
    if (!oledDisplay.begin()) {
        Serial.println("OLED Display initialization failed!");
        while(1);
    }

    // Demonstrate various display capabilities
    delay(1000);

    // Centered normal text
    oledDisplay.displayText("WELCOME!", 0, 0, 2, true);
    delay(2000);

    // Inverted text display
    oledDisplay.displayInvertedText("INVERTED!", 0, 0, 2, true);
    delay(2000);

    // Number display in different bases
    oledDisplay.displayNumber(255, HEX, 0, 0, 2, true);
    delay(2000);
    oledDisplay.displayNumber(255, BIN, 0, 0, 2, true);
    delay(2000);

    // Horizontal scrolling
    oledDisplay.scrollHorizontal("ARDUINO OLED", 20, 2);
    delay(1000);

    // Vertical scrolling
    oledDisplay.scrollVertical("IOT\nPROJECT", 40, 2);
    delay(1000);

    // Image display (normal and inverted)
    oledDisplay.displayImage(heartBitmap, 40, 20, 16, 12);
    delay(2000);
    oledDisplay.displayImage(heartBitmap, 40, 20, 16, 12, true);
}

void loop() {
    // Additional interactive logic can be added here
}

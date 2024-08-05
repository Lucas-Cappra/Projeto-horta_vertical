  #ifndef DISPLAY_OLED_H
#define DISPLAY_OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayOLED {
public:
    DisplayOLED(uint8_t width, uint8_t height, uint8_t addr);
    void begin();
    void clear();
    void printMessage(const String& message, int x, int y);

private:
    Adafruit_SSD1306 display;
    uint8_t address;
};

#endif

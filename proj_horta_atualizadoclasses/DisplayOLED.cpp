#include "DisplayOLED.h"

DisplayOLED::DisplayOLED(uint8_t width, uint8_t height, uint8_t addr) 
    : display(width, height, &Wire, -1), address(addr) {}

void DisplayOLED::begin() {
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, address);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.clearDisplay();
    display.display();
}

void DisplayOLED::clear() {
    display.clearDisplay();
    display.display();
}

void DisplayOLED::printMessage(const String& message, int x, int y) {
    display.setCursor(x, y);
    display.print(message);
    display.display();
}

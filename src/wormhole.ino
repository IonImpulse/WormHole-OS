#include <Adafruit_FlashCache.h>
#include <Adafruit_FlashTransport.h>
#include <Adafruit_SPIFlash.h>
#include <flash_devices.h>

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <SPI.h>

#include <TouchScreen.h>
#include <Adafruit_HX8357.h>
#include <WiFiNINA.h>
#include <Adafruit_NeoPixel.h>

#define RED_LED       13 // Bootup LED
#define TFT_RESET     24 // Reset the screen
#define TFT_BACKLIGHT 25 // Set the backlight power
#define SD_CS         32 // Read SD card
#define SD_CS_EXIST   33 // See if SD card exists
#define SPEAKER_STOP  50 // Speaker stopping

#define SPEAKER_OUT   A0 // Analog speaker out
#define LIGHT_SENSOR  A2 // Analog light sensor in

#define TFT_D0        34 // Data bit 0 pin (MUST be on PORT byte boundary)
#define TFT_WR        26 // Write-strobe pin (CCL-inverted timer output)
#define TFT_DC        10 // Data/command pin
#define TFT_CS        11 // Chip-select pin
#define TFT_RST       24 // Reset pin
#define TFT_RD         9 // Read-strobe pin
#define TFT_TE        12

#define TFT_ROTATION   3

#define TFT_DEFAULTFILL 0x182E

Adafruit_HX8357 tft = Adafruit_HX8357(tft8bitbus, TFT_D0, TFT_WR, TFT_DC, TFT_CS,TFT_RST, TFT_RD);
Adafruit_FlashTransport_QSPI flashTransport(PIN_QSPI_SCK, PIN_QSPI_CS, PIN_QSPI_IO0, PIN_QSPI_IO1, PIN_QSPI_IO2, PIN_QSPI_IO3);
Adafruit_SPIFlash flash(&flashTransport);

#define YD A4  // must be an analog pin, use "An" notation!
#define XL A5  // must be an analog pin, use "An" notation!
#define YU A6  // can be a digital pin
#define XR A7  // can be a digital pin

TouchScreen ts = TouchScreen(XR, YU, XL, YD, 300);
#define X_MIN  750
#define X_MAX  325
#define Y_MIN  840
#define Y_MAX  240

SdFat SD;

void setup() {
    Serial.begin(9600);
    Serial.println("HX8357D Test!");

    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH);

    tft.begin();
    tft.setRotation(TFT_ROTATION);
    tft.fillScreen(TFT_DEFAULTFILL);

    svg.readFile((char *)"/svgs/boot.svg");

    svg.print();

}

void loop() {
    // read diagnostics (optional but can help debug problems)
    uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);
    Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDMADCTL);
    Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDCOLMOD);
    Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDDIM);
    Serial.print("Image Format: 0x"); Serial.println(x, HEX);
    x = tft.readcommand8(HX8357_RDDSDR);
    Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 


    delay(5000);
}
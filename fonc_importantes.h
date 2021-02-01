#include <SPI.h>
#include <Adafruit_I2CDevice.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h" 
#include <Keypad.h>
#include <DS3231.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <DFRobotDFPlayerMini.h>
#include "URTouch.h"
#include <stdlib.h>

File myFile;

String fichiers[8];

Time  t;
void printDetail(uint8_t type, int value);
char alphabet[37] = {' ','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0'};

DFRobotDFPlayerMini myDFPlayer;
//_________________________________________________________
//                    declaration des broches
const byte ROWS = 4; //s
const byte COLS = 4; //four clumns
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {46, 44, 42, 40};
byte colPins[COLS] = {38, 36, 34, 32};
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
DS3231  rtc(SDA, SCL);
#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

#define _sclk 33
#define _miso 12
#define _mosi 11
#define _cs 35
#define _dc 37
#define _rst 27
#define TFT_DC 9              
#define TFT_CS 7             
#define TFT_RST 6             
#define TFT_MISO 12           
#define TFT_MOSI 11    
#define BUFFPIXEL 20       
#define TFT_CLK 13    
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

const byte chipSelect = 53;

int actuRam;
int actuHeure;

long chrono1 = -60000;
long chrono2 = -60000;
long chrono3 = -60000;
long chrono4 = 0;
bool game = false;
int touche;

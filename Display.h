#include "Fonts/FreeSans9pt7b.h"   
#include "Fonts/FreeSans12pt7b.h" 

/* configure */
uint16_t x, y;

//MCUFRIEND_kbv tft;
UTFTGLUE tft(0,A2,A1,A3,A4,A0);
const int XP=8,XM=A2,YP=A3,YM=9;
const int TS_LEFT=117,TS_RT=907,TS_TOP=950,TS_BOT=92;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

void screen()
{
  tp = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  x = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
  y = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
}

void while_not_press()
{
  while(!(tp.z > MINPRESSURE && tp.z < MAXPRESSURE))
    screen();
}

bool touch()
{
  return (tp.z > MINPRESSURE && tp.z < MAXPRESSURE);
}

void init_bar(){
  tft.setColor(66, 167, 255);
  tft.fillRoundRect(20, 256, 300, 276);
}
void error_bar(){
  tft.setColor(255, 0, 0);
  tft.fillRoundRect(23, 259, 23 + (60*274)/100, 273);
}
void set_bar(byte pourcent)
{
  tft.setColor(0, 0, 0);
  tft.fillRoundRect(23, 259, 23 + (pourcent*274)/100, 273);
}

void light(bool state)
{
  digitalWrite(12, state);
  if(state == HIGH) 
  {
    uint16_t ID = tft.readID(); 
    tft.begin(ID);
    tft.InitLCD();
    tft.setFont(SmallFont);
    tft.setRotation(0);
  }
}

#define BUFFPIXEL 40  
uint16_t read16(File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

void bmpDraw(char *filename, uint8_t x, uint16_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { 

        goodBmp = true; 
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        rowSize = (bmpWidth * 3 + 3) & ~3;
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        for (row=0; row<h; row++) {
          if(flip) 
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else   
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) {
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);
            
          }

          for (col=0; col<w; col++) { 
            if (buffidx >= sizeof(sdbuffer)) {
              //tft.endWrite();
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0;
            }

            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            if(!(b == 255 && g == 255 && r == 255))
            {tft.setColor(r, g, b);
            tft.drawPixel(col, row);}
          } 
        } 
      } 
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}
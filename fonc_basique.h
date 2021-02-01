int f_read_int(String adresse)
{
	int value = 0;
	myFile = SD.open(adresse, FILE_READ);

	while(myFile.available())
	{
		value = value * 10 + (myFile.read() - 48);
	}
	return value;
}

void f_write_int(String adresse, int value)
{
	SD.remove(adresse);
	myFile=SD.open(adresse, FILE_WRITE);
	myFile.print(value);
}

String f_read_string(String adresse)
{
	String value;

	myFile=SD.open(adresse, FILE_READ);
	while(myFile.available())
	{
		value = value + myFile.read();
	}
	return value;
}

void f_write_string(String adresse, String value)
{
	SD.remove(adresse);
	myFile=SD.open(adresse, FILE_WRITE);
	myFile.print(value);
}

void f_print_string(String adresse, String value)
{
  myFile=SD.open(adresse, FILE_WRITE);
  myFile.print(value);
}

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
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.startWrite(); // Start TFT transaction
        tft.setAddrWindow(x, y, w, h);

        for (row=0; row<h; row++) {
          if(flip) 
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else   
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) {
            tft.endWrite(); 
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer);
            
            tft.startWrite();
          }

          for (col=0; col<w; col++) { 
            if (buffidx >= sizeof(sdbuffer)) {
              tft.endWrite();
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0;
              tft.startWrite();
            }

            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.color565(r,g,b));
          } 
        } 
        tft.endWrite();
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } 
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

void crs(int x, int y)
{
	tft.setCursor(x, y);
}

void light(bool etat)
{
	digitalWrite(3, etat);
}

void taille(int t)
{
	tft.setTextSize(t);
}

int ramlibre() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

String extract(int from, int to, String str)
{
    String substr;
  
    if( from > str.length() || to > str.length() || from >= to || from < 0)
    {
        Serial.println("erreur");
        exit(EXIT_FAILURE);
    }

    for(int i = from, j = 0; i < to; i++, j++)
        substr += str[i];

    return substr;  
}

int find_char(char c, String str)
{
  for(int size = 0; size < str.length(); size++)
  {
      if(str[size] == c)
        return size;
  }
  return -1; 
}

void ecran(uint16_t couleur)
{
	tft.fillRect(0, 31, 320, 189, couleur);
}

void couleur(uint16_t couleur)
{
	tft.setTextColor(couleur);
}

void touches(String a, String b, String c, String d)
{
  couleur(0xFFFF);
  tft.fillRect(0, 220, 320, 30, 0x0000);
  taille(1);
  crs(33, 227);
  tft.print("A:");
  tft.print(a);
  crs(93, 227);
  tft.print("B:");
  tft.print(b);
  crs(153, 227);
  tft.print("C:");
  tft.print(c);
  crs(213, 227);
  tft.print("D:");
  tft.print(d);
}

byte clavier()
{
	touche = customKeypad.getKey() - 48;
}



byte type(byte b){
	int str_len = fichiers[b].length() + 1; 

	char analise[str_len];

	fichiers[b].toCharArray(analise, str_len);

	  char type_file[3];
	  for(byte i = 0; i < fichiers[b].length(); i++)
	  {
	    type_file[0] = analise[i];
	    type_file[1] = analise[i+1];
	    type_file[2] = analise[i+2];
		if(type_file[0] == 'B'&& type_file[1] == 'M'&& type_file[2] == 'P'){break;}else{
	    if(type_file[0] == 'T'&& type_file[1] == 'X'&& type_file[2] == 'T'){break;}else{}}
	  }
  	if(type_file[0] == 'B'&& type_file[1] == 'M'&& type_file[2] == 'P')
  	{
  	  return 1;
  	}
  	else
  	{
  	  if(type_file[0] == 'T'&& type_file[1] == 'X'&& type_file[2] == 'T')
    	{
    	  return 2;
    	}
    	else
    	{	
      		return 0;
    	}
  	}
}


void listDirectoryFiles(File directory, int indent) {
  byte i = 0;
  File entry = directory.openNextFile();
  while(entry) {
    for (byte i = 0; i < indent; i++) {
      Serial.write(' ');
    }
    fichiers[i] = entry.name();
    i++;
    if (entry.isDirectory()) {
    } else {
    }
    entry.close();
    entry = directory.openNextFile();
  }
  directory.rewindDirectory();
  c = i;
}

void ouverture(String adresse)
{

}

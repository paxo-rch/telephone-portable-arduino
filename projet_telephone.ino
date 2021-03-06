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

File myFile;
File noms;
File texte;
Time  t;
void printDetail(uint8_t type, int value);

DFRobotDFPlayerMini myDFPlayer;
//_________________________________________________________
//                    declaration des broches
  String fichiers[8];
  byte e[2][8] = {{10,80,150,220,10,80,150,220},{10,10,10,10,100,100,100,100}};
  byte c;
  String directionfichier = "";
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
/*#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif*/
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


//_________________________________________________________
//    declaration variables


const byte chipSelect = 53;
byte ymenu = 10;
byte xmenu = 1;
int toucheclavier = 0;
bool etatcode = 0;
short unsigned int aleasigne;
byte scorebon = 0;
int scorefaux = 0;
byte resultatcalcul;
bool reload = false;
byte reponse;
bool fincalcul = 0;
long code;
int ancien;
double aleanombre1, aleanombre2;
byte derqual;
byte curseurecriture = 93;
float calc1 , calc2;
short int compteur = 0;
float memoire1 = 0;
int memoire2;
bool etat_veille = false;
byte lettrechoisie = 0;
byte cursormessage = 1;
String demande1;
char alphabet[37] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0',' '};
char messagetxt[50];
char messagesim800l[20];
long ancienneheure;
byte bufferavider;
byte curseursim = 1;
static unsigned long chrono = 0;
static unsigned long chronometre = 0;
byte qualite;
String derheure;
//double char texte {
//_________________________________________________________
//                              Setup
void demarage(){
  demandecode();
}

void setup() {
  pinMode(53, OUTPUT);
digitalWrite(3, HIGH);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, OUTPUT);
    tft.begin(9600);
  tft.setTextSize(4);
  tft.setCursor(100, 120);
  tft.setTextColor(ILI9341_GREEN);
  tft.setRotation(3);
  tft.print("paxo");
//_________________________________________________________
//                    declaration des broches

pinMode(6, OUTPUT);
digitalWrite(6, LOW);
//_________________________________________________________
//                          Demarages modules
  Serial1.begin(9600);
  rtc.begin();
  Serial.begin(9600);
  Serial1.print("AT");
  delay(500);
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.print("    ");
  if (!SD.begin(4)) {
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_RED);
    tft.print("ERREUR: Carte SD");
    while(true);
  }
  demarage();
  randomSeed(analogRead(A1));

}

//_________________________________________________________
//                                Loop
void loop() {
  menu();
  if(ymenu == 10){
    switch(xmenu)
    {
      case 1:
        jeucalcul();
      break;
      case 2:
        telephone();
      break;
      case 3:
        message();
      break;
      case 4:
        heureetdate();
      break;
      case 5:
        calculatrice();
      break;
      case 6:
        sdread();
      break;
      case 7:
        foncchronometre();
      break;
      case 8:
        snake();
      break;
      case 9:
        lecon();
      break;
      case 10:
        cartes();
      break;
      case 11:
        pong();
      break;
      case 12:
        explo();
      break;
    }
 
  }
}

void demandecode(){
  code=0;
  tft.fillRect(100, 96, 80, 20, ILI9341_BLACK);
  tft.fillRect(102, 98, 76, 16, 0xC71C);
  tft.setTextSize(2);
  tft.begin();
  tft.setRotation(3);
  printtft("entrez le PIN:", 50, 50, 13, 2);
  while(etatcode == 0){
    verification();
    int toucheclavier = customKeypad.getKey();
    if(toucheclavier == 68){
      if(code == 101427){
    etatcode = 1;
    }else{
      tft.setTextSize(2);
      delay(1000);
      asm volatile ("  jmp 0"); 
      
    }
    }
    if(toucheclavier){
      tft.setTextSize(2);
      if(!etatcode == 1){
      curseurvirtuel();
      tft.setCursor(curseurecriture, 99);
      tft.print("*");
      }
    code = code * 10 + toucheclavier - 48;    
  }
}
}
void menu(){
  tft.fillScreen(0xFEF4);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  printtft("jeux", 25, 30, 5, 1);
  printtft("telephone", 25, 90, 9, 1);
  bmpDraw("icontel.bmp", 25, 80);
  //printtft("messages", 25, 150, 8, 1);
  bmpDraw("iconmes.bmp", 25, 140);
  printtft("heure", 25, 210, 6, 1);
  //bmpDraw("iconheur.bmp", 25, 200);
  printtft("calculatrice", 110, 30, 12, 1);  
  printtft("conctacts", 110, 90, 9, 1);
  printtft("chronometre", 110, 150, 11, 1);
  printtft("snake", 110, 210, 5, 1);
  //bmpDraw("iconsnak.bmp", 210, 200);
  printtft("lecon", 210, 30, 5, 1);
  printtft("carte", 210, 90, 5, 1);
  printtft("pong", 210, 150, 5, 1);
  printtft("fichiers", 210, 210, 5, 1);
  int toucheclavier = 0;
        
      chrono = millis() + 20000;
      toucheclavier = 0;
  while(toucheclavier != 20)
  {
    verification();
    tft.setTextSize(1);
    toucheclavier = customKeypad.getKey();
    toucheclavier = toucheclavier - 48;
    if(toucheclavier)
    {
      printmenu();
      tft.setTextColor(0xFEF4);
      tft.print("o");
      switch(toucheclavier){
        case 17:
          info();
          break;
        case 2:
          if(xmenu != 1, xmenu != 5, xmenu != 14){ xmenu = xmenu - 1; }
        break;
        case 8:
          if(xmenu != 4, xmenu != 4, xmenu != 14){ xmenu = xmenu + 1; }
        break;
        case 4:
          if(xmenu > 4){ xmenu = xmenu - 4; }
        break;
        case 6:
          if(xmenu < 14){ xmenu = xmenu + 4; }
        break;
        
      }
      if(xmenu > 12)
    {
      xmenu = 1;
    }
      Serial.println(xmenu);
      printmenu();
      tft.setTextColor(ILI9341_BLACK);
      tft.print("o");
    }
  }
}

void printmenu(){
  switch(xmenu){
        case 1:
          tft.setCursor(15, 35);
        break;
        case 2:
          tft.setCursor(15, 95);
        break;
        case 3:
          tft.setCursor(15, 155);
        break;
        case 4:
          tft.setCursor(15, 215);
        break;
        case 5:
          tft.setCursor(100, 34);
        break;
        case 6:
          tft.setCursor(100, 94);
        break;
        case 7:
          tft.setCursor(100, 154);
        break;
        case 8:
          tft.setCursor(100, 214);
        break;
        case 9:
          tft.setCursor(200, 35);
        break;
        case 10:
          tft.setCursor(200, 94);
        break;
        case 11:
          tft.setCursor(200, 154);
        break;
        case 12:
          tft.setCursor(200, 214);
        break;
        default:
          tft.setCursor(100, 154);
        break;
  }
}

void heureetdate(){
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(4);
  toucheclavier = 0;
  tft.setCursor(10, 150);
      tft.setTextColor(ILI9341_RED,ILI9341_BLACK);
      tft.fillRect(10, 150, 200, 30, ILI9341_BLACK);
      tft.println(rtc.getTimeStr());
      chrono = millis() + 20000;
  while(toucheclavier != 65){
    if(etat_veille == false)
    {
      verification();
    }else{
      if(digitalRead(4) == LOW){
        digitalWrite(3, HIGH);
        while(digitalRead(4) == LOW);
         etat_veille = false;
         break;
    }}
    tft.setTextSize(4);
    toucheclavier = customKeypad.getKey();
    if(millis() > ancienneheure + 60000){
      Serial.println(ancienneheure);
      tft.setCursor(10, 150);
      tft.setTextColor(ILI9341_RED);
      tft.fillRect(10, 150, 200, 30, ILI9341_BLACK);
      tft.setTextSize(4);
      tft.println(rtc.getTimeStr());
      ancienneheure = millis();
    }
  }
  digitalWrite(3, HIGH);
}
void jeucalcul(){
  tft.fillScreen(ILI9341_WHITE);
  tft.setCursor(50, 100);
  tft.setTextSize(5);
  tft.print("jouer");
  chrono = millis() + 20000;
  while(toucheclavier != 68){
    verification();
    toucheclavier = customKeypad.getKey();
  }
  tft.setTextColor(ILI9341_RED);
  tft.setCursor(50, 100);
  tft.setTextSize(5);
  tft.print("jouer");
  tft.setTextColor(ILI9341_BLACK);
  while(toucheclavier != 65){
    chrono = millis() + 20000;
    verification();
  aleasigne = random(1, 5);
  if(aleasigne == 1){                                 //addition
    aleanombre1 = random(30, 200);
    aleanombre2 = random(30, 100);
    resultatcalcul = aleanombre1 + aleanombre2;
    
  }
  if(aleasigne == 2){                                 //soustraction
    aleanombre1 = random(50, 200);
    aleanombre2 = random(30, aleanombre1);
    resultatcalcul = aleanombre1 - aleanombre2;
    
  }
  if(aleasigne == 3){                                 //multiplication
    aleanombre1 = random(3, 20);
    aleanombre2 = random(3, 20);
    resultatcalcul = aleanombre1 * aleanombre2;
    
  }
  if(aleasigne == 4){                                 //addition
    memoire1 = random(5, 20);
    aleanombre2 = random(5, 20);
    aleanombre1 = memoire1 * aleanombre2;
    resultatcalcul = aleanombre1 / aleanombre2;

  }
  
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(20, 200);
  tft.print(scorebon);
  tft.setTextColor(ILI9341_RED);
  tft.setCursor(100, 200);
  tft.print(scorefaux);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(0, 30);
  tft.setTextSize(3);
  tft.print(aleanombre1);
  tft.print(" ");
  if(aleasigne == 1){
    tft.print("+");
  }
  if(aleasigne == 2){
    tft.print("-");
  }
  if(aleasigne == 3){
    tft.print("X");
  }
  if(aleasigne == 4){
    tft.print("/");
  }
  tft.print(" ");
  tft.print(aleanombre2);
  tft.print(" = ");
  
  
  
  reponse = 0;
  int toucheclavier = 1;
  fincalcul = 0;
  chrono = millis() + 20000;
  curseurecriture = 0;
  while(fincalcul == 0){
    verification();
      int toucheclavier = customKeypad.getKey();
      toucheclavier;
      if(toucheclavier && toucheclavier != 68){
      curseurvirtuel();
      tft.setTextSize(2);
      tft.setCursor(curseurecriture, 140);
      tft.print(toucheclavier - 48);
      reponse = reponse * 10 + toucheclavier - 48;    
      }
      if(toucheclavier == 65){
        return setup;
      }
      if(toucheclavier == 68){
      if(reponse == resultatcalcul){
        scorebon++;
        fincalcul++;
        tft.setCursor(100, 100);
        tft.print("bon");
      }else{
        scorefaux++;
        fincalcul++;
        tft.setCursor(100, 100);
        tft.println("faux");
        tft.print("le reponse etait: ");
        tft.println(resultatcalcul);
      }
      }
  }
}
}
void calculatrice(){
  tft.fillScreen(0xFEF4);
  tft.setTextColor(ILI9341_BLACK);
  curseurecriture = 10;
  tft.setTextSize(3);
  fincalcul = 0;
  aleasigne = 0;
  aleanombre1 = 0;
  aleanombre2 = 0;
  compteur = 1;
  memoire1 = 0;
  toucheclavier = 0;
  while(toucheclavier != 68){
    verification();
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      if(toucheclavier != 68 && toucheclavier != 67){
      curseurvirtuel();
      tft.setTextSize(2);
        tft.setCursor(curseurecriture, 100);
      tft.print(toucheclavier-48);
      if(fincalcul == 0){
           aleanombre1 = aleanombre1 * 10 + toucheclavier - 48; 
      }else{

           aleanombre2 = aleanombre2 * 10 + toucheclavier - 48; 
      }
    }
    if(toucheclavier == 67){
      compteur = 1;
      while(toucheclavier != 66){
        verification();
        toucheclavier = customKeypad.getKey();
        if(toucheclavier){
          if(toucheclavier == 67){
            fincalcul = 1;
            tft.setTextColor(0xFEF4);
            tft.setCursor(20, 200);
            tft.setTextSize(5);
            if(compteur  == 1){
              tft.print("+");
            }else{if(compteur == 2){
              tft.print("-");
            }else{if(compteur == 3){
              tft.print("x");
            }else{if(compteur == 4){
              tft.print("/");
            }}}}
            compteur++;
            if(compteur == 5){
              compteur = 1;
            }
            tft.setCursor(20, 200);
            tft.setTextColor(ILI9341_BLACK);
            tft.setTextSize(5);
            if(compteur  == 1){
              tft.print("+");
            }
            {if(compteur == 2){
              tft.print("-");
            }
            {if(compteur == 3){
              tft.print("x");
            }
            {if(compteur == 4){
              tft.print("/");
            }}}}
          }
          
        }
      }
      tft.setTextColor(ILI9341_BLACK);
            curseurvirtuel();
            tft.setCursor(curseurecriture, 100);
            tft.setTextSize(2);
            if(compteur  == 1){
              tft.print("+");
            }else{if(compteur == 2){
              tft.print("-");
            }else{if(compteur == 3){
              tft.print("x");
            }else{if(compteur == 4){
              tft.print("/");
            }}}}
            tft.setTextSize(5);
            tft.setTextColor(ILI9341_YELLOW);
            tft.setCursor(20, 200);
            if(compteur  == 1){
              tft.print("+");
            }else{if(compteur == 2){
              tft.print("-");
            }else{if(compteur == 3){
              tft.print("x");
            }else{if(compteur == 4){
              tft.print("/");
            }}}}
            tft.setTextColor(ILI9341_BLACK);
            tft.setTextSize(3);
    }
    }
  }
  toucheclavier = 0;
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(100, 30);
  tft.print("=");
  if(compteur == 1){
    memoire1 = aleanombre1 + aleanombre2;
    tft.print(memoire1);
 }
  if(compteur == 2){
    memoire1 = aleanombre1 - aleanombre2;
   tft.print(memoire1);
  }
  if(compteur == 3){
    memoire1 = aleanombre1 * aleanombre2;
    tft.print(memoire1);
  }
  if(compteur == 4){
    memoire1 = aleanombre1 / aleanombre2;
    tft.print(memoire1);
  }
  while(toucheclavier != 68){
    verification();
    toucheclavier = customKeypad.getKey();
  }
}
void telephone(){
  tft.setCursor(10, 150);
  tft.print("memoire: ");
  tft.print(code);
  tft.setCursor(80, 3);
  code=0;
  etatcode = 0;
  tft.setTextSize(2);
   tft.fillScreen(ILI9341_WHITE);
  printtft("composer le numero", 10, 40, 18, 1);
  tft.setCursor(10, 90);
  toucheclavier = 0;
  fincalcul = 0;
  curseurecriture  = 0;
  while(true){
    verification();
    int toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      tft.setTextSize(2);
      if(toucheclavier == 67){
        Serial1.println("ATH");
      }
      if(toucheclavier == 65){
        break;
      }
      if(toucheclavier == 66){
        Serial1.println("ATA");
      }
    if(toucheclavier - 48 == 20){
      appel();
    }
    if(!etatcode == 1 && toucheclavier-48 != 20 && toucheclavier - 48 != 19 && toucheclavier - 48 != 18 && toucheclavier - 48 != 17){
      curseurvirtuel();
      tft.setCursor(curseurecriture, 140);
      tft.setTextColor(ILI9341_BLACK);
      tft.print(toucheclavier-48);
      
    code = code * 10 + toucheclavier - 48;
    }
  }
}
code = 0;
}
void message(){
    code=0;
    curseurecriture = 10;
  etatcode = 0;
  tft.setTextSize(2);
   tft.fillScreen(ILI9341_WHITE);
  tft.println("composer le numero pour envoyer un message");
  toucheclavier = 0;
  fincalcul = 0;
  toucheclavier = 0;
  curseurecriture = 0;
  while(true){
    verification();
    int toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      tft.setTextSize(2);

    if(toucheclavier - 48 == 17){
      break;
    }
    if(!etatcode == 1 && toucheclavier-48 != 20){
      curseurvirtuel();
      tft.setTextSize(2);
      tft.setCursor(curseurecriture, 140);
      tft.print(toucheclavier-48);
      
    code = code * 10 + toucheclavier - 48;
    }
  }
  }
  tft.fillScreen(ILI9341_GREEN);                
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  while(true){
    verification();
    claviercomplet();

    delay(100);
  if(toucheclavier == 65){
      break;
    }
  tft.setTextSize(2);
  }
}

void claviercomplet(){
  tft.setTextSize(3);
  while(true){
    verification();
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
  if(toucheclavier == 68){
      messagetxt[cursormessage] = alphabet[lettrechoisie];
      tft.setTextSize(2);
      tft.setCursor(curseurecriture, 30);
      tft.print(alphabet[lettrechoisie]);
    }
    if(toucheclavier == 67){
      envoyermessage();
      tft.print("message envoyé");
    } 

    
    if(toucheclavier - 48 == 6 && lettrechoisie != 38){
      lettrechoisie++;
      tft.setCursor(0, 200);
      tft.setTextColor(ILI9341_GREEN);
      tft.print(alphabet[lettrechoisie - 1]);  
    }
    if(toucheclavier - 48 == 4 && lettrechoisie != 0){
      lettrechoisie--;
          tft.setCursor(0, 200);
    tft.setTextColor(ILI9341_GREEN);
      tft.print(alphabet[lettrechoisie + 1]); 
    }
        if(toucheclavier - 48 == 6 && lettrechoisie == 37){
      tft.setCursor(0, 200);
      tft.setTextColor(ILI9341_GREEN);
      tft.print("a");  
    lettrechoisie = 0;
    }
    if(toucheclavier - 48 == 4 && lettrechoisie == 0){
      tft.setCursor(0, 200);
      tft.setTextColor(ILI9341_GREEN);
      tft.print("a");  
    lettrechoisie = 37;
    }
    
    tft.setCursor(0, 200);
    tft.setTextColor(ILI9341_BLACK);
    tft.print(alphabet[lettrechoisie]);
}

void appel(){
  Serial1.print("ATD");
  Serial1.print("+33");
  Serial1.print(code);
  Serial1.println(";");
}
void envoyermessage(){
    Serial1.print("AT+CMGF=1\r");
    delay(1000);
    Serial1.print("AT+CMGS=");
    Serial1.print("\"");
    Serial1.print("+33");
    Serial1.print(code);
    Serial1.println("\"");
    Serial.print("AT+CMGS=");
    Serial1.print("\r");
    Serial.print("+33");
    Serial.print(code);
    Serial.println("\"");
    delay(1000);
    int lecturemessage = 1;
    while(lecturemessage < cursormessage){
      Serial1.print(messagetxt[lecturemessage]);
      Serial.print(messagetxt[lecturemessage]);
      lecturemessage++;
    }
    Serial.println();
    Serial1.println();
    
    delay(1000);
    Serial1.write(char(26));
    Serial.write(char(26));
    Serial.println();
    Serial1.println();
}
void interfacechiffre(){
    tft.fillScreen(ILI9341_RED);                
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(30, 30);
  tft.setTextSize(3);
  tft.print("entrez ");
  tft.print(demande1);
  while(true){
    verification();
    int toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      tft.setTextSize(4);
      if(toucheclavier == 68){
        appel();
        break;
      }
      if(!etatcode == 1 && toucheclavier-48 != 20){
        tft.print(toucheclavier-48);
        code = code * 10 + toucheclavier - 48;
      }
    }
  }
}


void verification(){
  
  int val = digitalRead(4);
  if(val == 0){
    reload = true;
    while(reload == true){
      etat_veille = true;
      digitalWrite(3, LOW);
      while(digitalRead(4) == LOW);
      heureetdate();
      etat_veille = false;
      while(true)
      {
        int toucheclavier = customKeypad.getKey();
        if(toucheclavier){
          reload = false;
          break;
        }
        if(digitalRead(4) == LOW){
          reload = true;
          break;
        }
      }
    
    
    }
      menu();
  }
    tft.setTextSize(2);
    if(toucheclavier == -6){tft.begin(); Serial.print("begin");}
  if(millis()-chrono>20000ul){
    chrono = millis();
    tft.fillRect(0, 0, 320, 20, 0xFF54);
    Serial1.println("AT+CSQ");
    curseursim = 1;
    while(Serial1.available() > 0){
      messagesim800l[curseursim] = Serial1.read();
      curseursim++;
    }
      qualite = (messagesim800l[16]-48)*10 +messagesim800l[17]-48;
      
      tft.setTextColor(ILI9341_BLACK);
      tft.setCursor(5, 0);
      if(qualite == 0){
        tft.print("---");
      }else{
        if(qualite < 10){
          tft.print("o--");
          }else{
        if(qualite < 20){
          tft.print("oo-");
        }else{
          tft.print("ooo");
        }
      }
      }
      derheure = rtc.getTimeStr();
      tft.setTextColor(ILI9341_BLACK);
      tft.setCursor(80, 3);
      tft.print(derheure);
      while(Serial1.available() > 0){
        bufferavider = Serial1.read();
      }
      tft.drawLine(0, 20, 320, 20, ILI9341_BLACK);
      tft.setCursor(80, 3);
          tft.begin();
  tft.setRotation(3);
  }
}

void sdread(){
  tft.fillScreen(0xFF54);
  tft.setTextSize(2);
  tft.setCursor(0, 23);
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile = SD.open("test.txt");
  if (myFile) {
    while(myFile.available()) {
      tft.write(myFile.read());
    }
    myFile.close();
  } else {
    tft.print("erreur lors de l'ouverture de contact");
  }
  chrono = millis() + 20000;
  curseurecriture = 70;
  tft.setCursor(3, 3);
  tft.print("mem:");
  while(true){
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      if(toucheclavier - 48 == 20){
        break;
      }else{
        curseurvirtuel();
        tft.setCursor(curseurecriture, 3);
        tft.print(toucheclavier - 48);
        code = code * 10 + toucheclavier - 48;
      }
    }
  }
}

void foncchronometre(){
  tft.fillScreen(ILI9341_WHITE);
  while(true){
    verification();
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      if(toucheclavier == 65){
        break;
      }
      if(toucheclavier == 68){
        chronometre = millis();
        while(true){
          toucheclavier = customKeypad.getKey();
          if(toucheclavier == 68){
            break;
          }
          if(chrono < millis() - 200){
            tft.setTextSize(2);
            tft.setCursor(20, 40);
            tft.setTextColor(ILI9341_WHITE);
            tft.print(chrono);
            chrono = float((millis() - chronometre) / 1000);
            tft.setCursor(20, 40);
            tft.setTextColor(ILI9341_BLACK);
            tft.print(chrono);
          } 
        } 
        tft.setTextSize(2);
        tft.setCursor(20, 100);
        tft.print(float(millis() - chronometre) / 1000);
      }
    } 
  }
}



void curseurvirtuel(){
  curseurecriture = curseurecriture + 12;
}

void printtft(String texte, byte x, byte y, byte taille, byte police)
{
  if(police != 2 && police != 3 && police != 4){
    police = 1;
  }
  tft.fillRect(x + 5, y + 5,taille * 7 * police, 20 * police, 0xDDED);
  tft.fillRect(x, y,taille * 7 * police, 20 * police,  0xFE71);
  tft.setCursor(x + 5 , y + 5);
  tft.setTextSize(police);
  tft.print(texte);
}

int file_ecriture(String nom_du_fichier, long valeur)
{
  SD.remove(nom_du_fichier);
  myFile=SD.open(nom_du_fichier ,FILE_WRITE);
  myFile.print(valeur);
  myFile.close();
}

int file_lecture(String nom_du_fichier)
{
  long valeur = 0;
  myFile = SD.open(nom_du_fichier ,FILE_READ);
  while(myFile.available())
  {
    valeur = valeur * 10 + myFile.read() - 48;
  }
  return valeur;
}

void snake()
{
  tft.fillScreen(ILI9341_WHITE);
  byte snake[50][2] = {0};
  byte tete = 0;
  byte deriere = 0;
  bool point = true;
  byte pointxy[2] = {0, 0};
  int vitesse;
  byte piege1[2] = {0, 0};
  byte i;
  byte piege2[2] = {0, 0};
  byte piege3[2] = {0, 0};
  bool gameover = false;
  long conteur = millis();
  snake[0][1] = 8;
  snake[0][0] = 8;
  byte direc = 2;
  int score = 5;
  pointxy[0] = random(1, 32);
    pointxy[1] = random(1, 24);
    Serial.print(pointxy[0]);
    Serial.print(" ");
    Serial.println(pointxy[1]);
    tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 9, 9, ILI9341_GREEN);
  while(gameover == false)
  {
    if(score < 25){
      vitesse = score;
    }
    if(millis()-300ul > conteur - vitesse * 10)
    {
      i = score;
      Serial.println("1");
      while(i != 1)
      {
          i--;
          snake[i][1] = snake[i - 1][1];
          snake[i][0] = snake[i - 1][0];
      }
      
      toucheclavier = customKeypad.getKey();
      if(toucheclavier){
          tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 9, 9, ILI9341_GREEN);
          toucheclavier = toucheclavier - 48;
          if(toucheclavier == 2){direc = 3;}
          if(toucheclavier == 6){direc = 2;}
          if(toucheclavier == 8){direc = 1;}
          if(toucheclavier == 4){direc = 4;}
      }
      if(direc == 2)
      {
        snake[0][1] = snake[0][1] + 1;      
      }
      if(direc == 4)
      {
        snake[0][1] = snake[0][1] - 1;      
      }
      if(direc == 1)
      {
        snake[0][0] = snake[0][0] + 1;      
      } 
      if(direc == 3)
      {
        snake[0][0] = snake[0][0] - 1;      
      }
      tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 9, 9, ILI9341_BLACK);
      tft.fillRect(snake[score - 1][1] * 10, snake[score - 1][0] * 10, 9, 9, ILI9341_WHITE);
      conteur = millis();
    }
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
          toucheclavier = toucheclavier - 48;
          if(toucheclavier == 2){direc = 3;}
          if(toucheclavier == 6){direc = 2;}
          if(toucheclavier == 8){direc = 1;}
          if(toucheclavier == 4){direc = 4;}
    }
    tete = 1;
    while(tete != score)
    {
      if(snake[0][1] == snake[tete][1] && snake[0][0] == snake[tete][0])
      {
        tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 9, 9, ILI9341_RED); 
        gameover = true;
      }
      tete++;
    }
      if(snake[0][0] == pointxy[1] && snake[0][1] == pointxy[0]){
    pointxy[0] = random(1, 32);
    pointxy[1] = random(1, 24);
    tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 9, 9, ILI9341_GREEN);
      score++;
  }
  }
tft.fillScreen(ILI9341_WHITE);
tft.setCursor(100, 100);
  tft.setTextSize(4);
  tft.print(score);
delay(5000);
  
   }
   

void lecon(){
  tft.fillScreen(0xFF54);
  tft.setTextSize(1);
  tft.setCursor(0, 23);
  myFile = SD.open("DESK/lecon.txt", FILE_WRITE);
  myFile = SD.open("DESK/lecon.txt");
  if(myFile) {
    while(myFile.available()) {
      tft.write(myFile.read());
    }
    myFile.close();
  }else{
    tft.print("erreur lors de l'ouverture de lecon");
  }
  while(true){
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
  bmpDraw("jumpers.bmp", 0, 0);
  while(true){
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
}

void pong()
{
  float direction_pong[2] = {2, 2};
  float  raquette = 100;
  long conteur = 0;
  byte score = 0;
  conteur = millis();
  float pong[2] = {10,10};
    while(true)
    {
      direction_pong[1] = 2;
      pong[1] = 10;
      direction_pong[0] = 2;
      pong[0] = 10;
      tft.fillScreen(ILI9341_BLACK);
      while(true)
    {
      if(direction_pong[0] == 0)direction_pong[0] = random(-1,1);
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      toucheclavier = toucheclavier - 48;
      tft.fillRect(raquette - 25, 230, 50, 10, ILI9341_BLACK); 
      switch(toucheclavier){
        case 6:
          raquette= raquette + 20;
        break;
        case 4:
          raquette=raquette-20;
        break;
      }
      tft.fillRect(raquette - 25, 230, 50, 10, ILI9341_WHITE); 
    }
    if(millis()-20ul > conteur)
    {
      conteur = millis();
      if(pong[0] > 315 || pong[0] < 5)direction_pong[0] = direction_pong[0] * (-1);
      if(pong[1] < 5)direction_pong[1] = direction_pong[1] * (-1);

      
      if(pong[1] > 210 && pong[0] < raquette + 30 && pong[0] > raquette - 30)
      {
        direction_pong[1] = direction_pong[1] * (-1);
        direction_pong[0] = direction_pong[0] + (pong[0]-raquette)/10;
        tft.setTextSize(2);
        tft.setCursor(290, 2);
        tft.setTextColor(ILI9341_BLACK);
        tft.print(score);
        
        score = score + 1;
        tft.setCursor(290, 2);
        tft.setTextColor(ILI9341_WHITE);
        tft.print(score);
      }
      Serial.print(direction_pong[0]);
      Serial.print(" ");
      Serial.println(direction_pong[1]);
      if(pong[1] > 230)
      {break;}

      
      tft.fillRect(pong[0], pong[1], 9, 9, ILI9341_BLACK); 
    pong[0] = pong[0] + direction_pong[0];
    pong[1] = pong[1] + direction_pong[1];
    tft.fillRect(pong[0], pong[1], 9, 9, ILI9341_WHITE); 
}
    }
    while(true){
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
    
  }
  score = 0;
  if(toucheclavier-48 == 17){break;}
    }
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
          Serial.print(100-((float)ramlibre()/32000*100));
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

void info(){
  tft.setTextColor(ILI9341_BLACK);
  tft.fillScreen(ILI9341_WHITE);
  bmpDraw("logo.bmp", 0, 0);
  tft.setTextSize(2);
  tft.setCursor(175, 30);
  tft.print("model paxo2");
  tft.setCursor(175, 50);
  tft.print("version: b10");
  tft.setCursor(175, 120);
  tft.print("paxo.fr 2020");
  while(true){
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
  menu();
}

void cartes()
{
  tft.setRotation(2);
  tft.fillScreen(ILI9341_WHITE);
  bmpDraw("carte1.bmp", 0, 0);
  while(true){
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
  bmpDraw("carte2.bmp", 0, 0);
  while(true){
    toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
  tft.setRotation(3);
}

int ramlibre() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}



void explo(){

  while(true)
  {
    tft.fillScreen(ILI9341_WHITE);
  File lieu = SD.open(directionfichier);
  listDirectoryFiles(lieu, 0);
  lieu.close();
  drawicones(); 
  byte lecteur = 0;
  int toucheclavier;
  while(1){
    toucheclavier = customKeypad.getKey();
    
    if(toucheclavier){
      toucheclavier -= 48;
      Serial.print(toucheclavier);
      tft.setCursor(e[0][lecteur], e[1][lecteur]+70);
      tft.setTextColor(ILI9341_BLACK);
      tft.print(fichiers[lecteur]);
       
      if(toucheclavier == 6){
        lecteur++;
      }
      if(toucheclavier == 18){
        tft.begin();
        tft.setRotation(3);
        tft.fillScreen(ILI9341_WHITE);
        drawicones(); 
      }
      if(toucheclavier == 4){
        lecteur--;
      }
      if(toucheclavier == 20){
        break;
      }
      if(toucheclavier == 17){
        break;
      }
      tft.setCursor(e[0][lecteur], e[1][lecteur]+70);
      tft.setTextColor(ILI9341_BLUE);
      tft.print(fichiers[lecteur]);
    }
  }
  directionfichier = directionfichier+"/"+fichiers[lecteur];
  if(toucheclavier == 17){
        directionfichier = "/";
      }
      ouverture();
  }
}

void listDirectoryFiles(File directory, int indent) {
  byte i = 0;
  File entry = directory.openNextFile();
  while(entry) {
    for (byte i = 0; i < indent; i++) {
      Serial.write(' ');
    }
    Serial.print(entry.name());
    fichiers[i] = entry.name();
    i++;
    if (entry.isDirectory()) {
      Serial.println("/");
    } else {
      Serial.println(entry.size(), DEC);
    }
    entry.close();
    entry = directory.openNextFile();
  }
  directory.rewindDirectory();
  c = i;
}




void drawicones(){
  for(byte b = 0; b < c; b++){
    String tem;
    if(type(b) == 0){
      Serial.print("fichier detecte");
      tem = "/ARDUINO/ICONES/FICHIER.BMP";
    }
    if(type(b) == 1){
      Serial.print("image detecte");
      tem = "/ARDUINO/ICONES/IMAGE.BMP";
    }
    if(type(b) == 2){
      Serial.print("txt detecte");
      tem = "/ARDUINO/ICONES/TEXTE.BMP";
    }
    bmpDraw(tem, e[0][b], e[1][b]);
    tft.setCursor(e[0][b], e[1][b]+70);
    tft.print(fichiers[b]);
  }
}

void ouverture()
{
  Serial.print("ouverture : ");
  Serial.println(directionfichier);
  fichiers[c] = directionfichier;
    if(type(c) == 1){
      openimage();
    }
    if(type(c) == 2){
      texteviewer();
    }
}

void texteviewer(){
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setCursor(70,1);
  tft.setTextSize(2);
  tft.print("texte apercu");
  tft.setTextSize(1);
  tft.setCursor(1,20);
  myFile = SD.open(directionfichier, FILE_READ);
  myFile = SD.open(directionfichier);
  Serial.print("ouverture txt: ");
  Serial.println(directionfichier);
  if(myFile) {
    while(myFile.available()) {
      tft.write(myFile.read());
    }
    myFile.close();
  } else {
    tft.print("erreur lors de l'ouverture du fichier");
  }
  while(true){
    int toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
}

void openimage(){
  tft.fillScreen(ILI9341_WHITE);
  bmpDraw(directionfichier, 0,0);
  while(true){
    int toucheclavier = customKeypad.getKey();
    if(toucheclavier){
      break;
    }
  }
}

byte type(byte b){
  Serial.print("a analiser  ");
Serial.println(fichiers[b]);
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
    Serial.print(type_file[0]);
    Serial.print(type_file[1]);
    Serial.println(type_file[2]);
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

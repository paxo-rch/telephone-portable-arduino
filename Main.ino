// Les applications sont a deposer dans le dossier principal et a inclure dans "Apps.h"
// /!\ mettre des actu(); dans chaque while du code pour ne pas louper d'appel et pour actualiser l'heure



/* library basic */

#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include <UTFTGLUE.h> 
#include <TouchScreen.h>
#include "SPI.h"  
#include "SD.h"   

/* library system */
#include "Display.h"
#include "Files.h"
#include "Utils.h"
#include "Apps.h"
#include "background.h"


/* declarations & configurations */


void setup() {
  //affectation des broches
  pinMode(32, OUTPUT); digitalWrite(32, LOW); pinMode(33, INPUT_PULLUP); //bouton home
  pinMode(12,OUTPUT);

  light(true);
  tft.fillScreen(0x0000);
  init_bar();
  
  //demarages series
  Serial.begin(9600);
  Serial1.begin(9600);
  set_bar(30);
  
  if (!SD.begin(53)){ error_bar(); error("carte sd non detectee"); while(1);}
  set_bar(60);

  get_code();
}

void loop() {

}

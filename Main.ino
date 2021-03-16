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
#include "hardwere.h"
#include "Display.h"
#include "Files.h"
#include "Background.h"
#include "Utils.h"
#include "Apps.h"



/* declarations & configurations */

#define PIN_BUTTON_HOME 33

void init_pin(void)
{
  pinMode(32, OUTPUT); digitalWrite(32, LOW); pinMode(PIN_BUTTON_HOME, INPUT_PULLUP); //bouton home
  pinMode(12,OUTPUT);
  
  Serial.begin(9600);
  Serial1.begin(9600);
}

void setup() {
  //affectation des broches

  init_pin();
  
  light(true);
  
  tft.fillScreen(0x0000);
  init_bar();
  
  //demarages series
  set_bar(30);
  try_sd:
  if (!SD.begin(53)){ error_bar(); error("carte sd non detectee"); while_not_press(); goto try_sd;}
  set_bar(100);
  
  while(!get_code());
  
  chrono_actu_hour = millis();
  actu();
  //while(!get_code());
  exit_all:
    menu();
}

void loop() {

}

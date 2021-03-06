// Les applications sont a deposer dans le dossier apps et a inclure dans "Apps.h"



/* library basic */

#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include <UTFTGLUE.h> 
#include <TouchScreen.h>
#include "SPI.h"  
#include "SD.h"   


#include <DS3231.h>

/* library system */
#include "hardwere.h"
#include "Display.h"
#include "Files.h"
#include "background.h"
#include "Utils.h"
#include "apps/Apps.h"



/* declarations & configurations */

#define PIN_BUTTON_HOME 33

void init_pin(void)
{
  pinMode(32, OUTPUT); digitalWrite(32, LOW); pinMode(PIN_BUTTON_HOME, INPUT_PULLUP); //bouton home
  pinMode(12,OUTPUT);
  
  Serial.begin(9600);
  Serial1.begin(9600);

  rtc.begin();
}

void setup() {
  init_pin();
  
  light(true);
  
  tft.fillScreen(0x0000);
  init_bar();
  
  //demarages series
  set_bar(30);
  try_sd:
  if (!SD.begin(53)){ error_bar(); error("carte sd non detectee"); while_not_press(); goto try_sd;}
  set_bar(100);
  
  chrono_actu_hour = millis();
  actu();
  //while(!get_code());
  exit_all:
    menu();
}

void loop() {

}

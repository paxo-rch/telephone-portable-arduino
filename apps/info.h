String ad_info(){ return "/arduino/apps/info/info.bmp"}

void info()
{
  fill_screen(20,255,20);
  tft.setCursor(0, 40);
  tft.setTextColor(0,0,0);
  tft.print("Ce telephone est basé sur arduino mega2560\n La description est sur le site: paxo.fr\nModel open-source Paxo2\n\nPAXO gabriel rochet");
  while()
}
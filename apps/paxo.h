String ad_paxo(){ return "/arduino/apps/paxo/paxo.bmp";}

void paxo()
{
	fill_screen(20,255,20);
  	tft.setCursor(0, 40);
  	tft.setTextColor(0x0000);
  	tft.setTextSize(2);
  	tft.print("Ce telephone est base sur arduino mega2560\n La description est sur le site: paxo.fr\nModel open-source Paxo2\n\nPAXO gabriel rochet");
  	screen();
  	while_not_press();
}
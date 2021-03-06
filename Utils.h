bool but_home()
{
	return (digitalRead(33) == LOW);
}

void error(String message)
{
	tft.setColor(255, 0, 0);
  	tft.fillRoundRect(50, 70, 270, 169);
  	tft.setCursor(60, 100);
  	tft.setColor(255, 255, 255);
  	tft.setFont(&FreeSans9pt7b);
  	tft.setTextSize(2);
  	tft.println("erreur:");
  	tft.setCursor(60, 140);
  	tft.println(message);
}

void get_code()
{
	tft.fillScreen(0x0000);
	for(byte i = 1; i < 11; i++)
	{
		byte crsy;
		if(i < 4){
			crsy = 1;
		}
		else
		{
			if(i < 7)
			{
				crsy = 2;
			}
			else
			{
				crsy = 3;
			}
		}
		tft.setColor(140, 140, 140);
		if(i == 10) tft.fillCircle(160, 400, 40);
		tft.fillCircle(260 + 100 * (i - crsy*3), 100 * crsy, 40);
		tft.setColor(255, 255, 255);
		tft.setCursor(255 + 100 * (i - crsy*3), 8 + 100 * crsy);
		tft.setFont(&FreeSans9pt7b);
		tft.setTextSize(3);
		if(i == 10) tft.setCursor(150, 405);
		tft.println(i);
	}
	while(true)
	{

	}
}
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
	screen();
  	while(x > 1000)
  	{
    	actu();
    	screen();
  	}
}

void while_press()
{
	screen();
    while(x < 1000)
  	{
    	actu();
    	screen();
  	}
}

bool touch()
{
  screen();
  return (x < 1000);
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

bool get_code()
{
	tft.setFont(&FreeSans12pt7b);
	tft.fillScreen(0x0000);
	for(byte i = 0; i < 10; i++)
	{
		byte y_cursor = (i-1)/3 + 1;

		tft.setColor(100, 100, 100);
		if(i != 0) tft.fillCircle(260 + 100 * (i - y_cursor*3), 100 + 90 * y_cursor, 30);
		else       tft.fillCircle(160, 400, 30);

		tft.setCursor(255 + 100 * (i - y_cursor*3), 8 + 100 * y_cursor);
		if(i == 0) tft.setCursor(155, 405);
		tft.println(i);
	}

	long code = 1234; //f_read_int("/arduino/paxo/data/code.txt");
	long code_input = 0;

	for(byte i = 0; i != 4; 1=1)
	{
		while_not_press();
	}
}
/*
tft.fillScreen(0x0000);
	for(byte i = 1; i < 11; i++)
	{
		byte crsy = (i-1)/3 +1;
		tft.setColor(100, 100, 100);
		if(i == 10) tft.fillCircle(160, 400, 40);
		tft.fillCircle(260 + 100 * (i - crsy*3), 100 * crsy, 40);
		tft.setColor(255, 255, 255);
		tft.setCursor(255 + 100 * (i - crsy*3), 8 + 100 * crsy);
		tft.setFont(&FreeSans9pt7b);
		tft.setTextSize(3);
		if(i == 10) tft.setCursor(155, 405);
		if(i == 10){ tft.println(0); }else{ tft.println(i);}
	}
	for(byte i = 1; i < 5; i++)
	{
		tft.drawCircle(64 * i, 30, 7);
	}
	tft.setCursor(230, 400);
	tft.print("clear", 230, 400, 0);
	long code = 1234; //f_read_int("/arduino/paxo/data/code.txt");
	long code_input = 0;
	byte nb;
	byte cursor = 1;
	screen();
	for(byte i = 0; i != 4; i=i)
	{
		actu();
		while(true)
		{
			screen();
			if(x < 1000) break;
			if(actu()) return 0;
		}

		nb = 255;
		if(60 < y && y < 140)
		{
			if(12 < x && x < 100) nb = 1;
			if(116 < x && x < 200) nb = 2;
			if(220 < x && x < 291) nb = 3;
		}
		if(162 < y && y < 233)
		{
			if(12 < x && x < 100) nb = 4;
			if(116 < x && x < 200) nb = 5;
			if(220 < x && x < 291) nb = 6;
		}
		if(259 < y && y < 337)
		{
			if(12 < x && x < 100) nb = 7;
			if(116 < x && x < 200) nb = 8;
			if(220 < x && x < 291) nb = 9;
		}
		if(370 < y && y < 430)
		{
			if(116 < x && x < 200) nb = 0;
		}
		if(370 < y && y < 430)
		{
			if(220 < x && x < 300)
			{
				i = 0;
				for(byte j = 1; j < 5; j++)
				{
					tft.drawCircle(64 * j, 30, 7);
				}
				code_input = 0;
			}
		}
		if(nb != 255)
		{
			i++;
			tft.fillCircle(64 * i, 30, 7);
			code_input = code_input*10 + nb;
			byte crsy = (nb-1)/3 +1;

			tft.setColor(255, 255, 255);
			if(nb == 0) tft.drawCircle(160, 400, 40);
			tft.drawCircle(260 + 100 * (nb - crsy*3), 100 * crsy, 40);
			tft.setColor(255, 255, 255);
			tft.setCursor(255 + 100 * (nb - crsy*3), 8 + 100 * crsy);
		}
		if(code == code_input){ tft.fillScreen(0x35C2); return 1; }
		screen();
		while(true)
		{
			screen();
			if(x > 1000) break;
		}
		byte crsy = (nb-1)/3 +1;

		tft.setColor(100, 100, 100);
		if(nb == 0) tft.drawCircle(160, 400, 40);
		tft.drawCircle(260 + 100 * (nb - crsy*3), 100 * crsy, 40);
		tft.setColor(255, 255, 255);
		tft.setCursor(255 + 100 * (nb - crsy*3), 8 + 100 * crsy);
		delay(100);
		
	}
	return 0;*/

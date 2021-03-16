long chrono_actu_hour = 0;
long delay_actu_hour = 10000;
long chrono_off = 0;
long delay_off_auto = 120000;

bool actu()
{

	if(chrono_actu_hour + delay_actu_hour < millis())
	{
		tft.setTextSize(3);
		tft.setFont(&FreeSans12pt7b);
		Time t = rtc.getTime();
		tft.setColor(112, 148, 255);
  		tft.fillRoundRect(0, 0, 320, 25);
  		tft.setColor(0,255,157);
  		tft.fillRoundRect(125, 3, 185, 22);
  		tft.setColor(0,0,0);
  		tft.setCursor(125, 20);
  		tft.print(t.hour);
  		tft.print(":");
  		tft.print(t.min);
  		tft.setCursor(190, 20);
  		tft.print(short(rtc.getTemp()));
  		tft.write("^C");
  		/*tft.setColor(255,0,0);
  		tft.fillRoundRect(10, 3, 80, 22);
  		tft.setTextColor(0xFFFF);
  		tft.setCursor(40, 20);
  		tft.print("X");
  		x = 2000;
  		y = 2000;*/
  		chrono_actu_hour = millis();
  	}

  	if(chrono_off + delay_off_auto < millis())
	{
		light(false);
		while(!but_home()){}
		light(true);
		chrono_off = millis();
		return 1;
  	}
  	if(x < 1000) chrono_off = millis();
  	return 0;
}

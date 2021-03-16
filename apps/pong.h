String ad_pong(){ return "/arduino/apps/pong/pong.bmp";}

void draw_pong_interface()
{
	fill_screen(0,0,0);
	tft.setColor(255, 255, 255);
  	tft.fillRoundRect(50, 70, 270, 169);
  	tft.setCursor(100, 120);
  	tft.setColor(0, 0, 0);
  	tft.setFont(&FreeSans9pt7b);
  	tft.setTextSize(2);
  	tft.println("PLAY PONG");
  	screen();
  	while_not_press();
  	fill_screen(0,0,0);
}

void run_game()
{

	float direction_pong[2] = {2, 2};
  	float  raquette = 100;
  	long conteur = 0;
  	unsigned int score = 0;
  	conteur = millis();
  	float pong[2] = {10,10};

    direction_pong[1] = -4;
    pong[1] = 40;
    direction_pong[0] = 4;
    pong[0] = 40;

	while(true)
	{

	    if(direction_pong[0] == 0)direction_pong[0] = random(-1,1);

	    if(touch){
	    	tft.setColor(0,0,0);
	    	tft.fillRect(raquette - 35, 460, raquette + 35, 465); 
	    	screen();
	    	raquette = x;
	    	tft.setColor(255,255,255);
	    	tft.fillRect(raquette - 35, 460, raquette + 35, 465); 
	    }

	    
	    if(millis()-10ul > conteur)
	    {
	      	if(pong[0] > 320 || pong[0] < 5)direction_pong[0] = direction_pong[0] * (-1);
	      	if(pong[1] < 30)direction_pong[1] = direction_pong[1] * (-1);

	      
	      	if(pong[1] > 460 && pong[0] < raquette + 40 && pong[0] > raquette - 40)
	      	{
	        	direction_pong[1] = direction_pong[1] * (-1);
		        direction_pong[0] = direction_pong[0] + (pong[0]-raquette)/10;

		        tft.setTextSize(2);
		        tft.setCursor(290, 40);
		        tft.setTextColor(0x000);
		        tft.print(score);
		        
		        score = score + 1;

		        tft.setCursor(290, 40);
		        tft.setTextColor(0xFFFF);
		        tft.print(score);
	      	}

	      	conteur = millis();

	      	if(pong[1] > 470) return;

	      	tft.setColor(0,0,0);
		    tft.fillCircle(pong[0], pong[1], 2);

		    pong[0] = pong[0] + direction_pong[0];
		    pong[1] = pong[1] + direction_pong[1];

		    tft.setColor(255,255,255);
		    tft.fillCircle(pong[0], pong[1], 2); 
	  	}
	}
}

void pong()
{
	draw_pong_interface();
	run_game();

} 
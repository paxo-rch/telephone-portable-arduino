static void draw_menu_interface(byte page)
{
	fill_screen(255,255,255);
	for(byte i = 0; i < nb_apps; i++)
	{
		short cox[12] = { 30, 120, 210,  30, 120, 210,  30, 120, 210,  30, 120, 210};
		short coy[12] = {100, 100, 100, 190, 190, 190, 280, 280, 280, 370, 370, 370};
		String ad = adress[i]();
		char buf[ad.length() + 1];
		ad.toCharArray(buf, ad.length()+1);
		bmpDraw(buf, cox[i], coy[i], 4);
	}
}


void boot_app(byte application)
{
	if(application == 12)  return;
	apps[application]();
	fill_screen(255,215,184);
	draw_menu_interface(1);
}

void menu()
{
	short cox[12] = { 30, 120, 210,  30, 120, 210,  30, 120, 210,  30, 120, 210};
	short coy[12] = {100, 100, 100, 190, 190, 190, 280, 280, 280, 370, 370, 370};

	draw_menu_interface(1);
	screen();
	while(true)
	{
		screen();
		while_not_press();
		byte app_to_boot = 0;
		for(; app_to_boot < 12; app_to_boot++)
		{
			if(cox[app_to_boot] < x && x <  cox[app_to_boot] + 80 && coy[app_to_boot] < y && y <  coy[app_to_boot] + 80)break;
		}
		boot_app(app_to_boot);
	}
} 
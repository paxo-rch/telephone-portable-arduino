/* Les applications sont a #include ici */

#include "apps/message.h"
#include "apps/phone.h"
#include "apps/pong.h"
#include "apps/snake.h"
#include "apps/files.h"
#include "apps/chrono.h"
#include "apps/editor.h"
#include "apps/paxo.h"
#include "apps/calcul.h"
#include "apps/hour.h"
#include "apps/info.h"

#define nb_apps 8

/* Les applications sont a declarer ici avec une "," */
void (*apps[])(void) = 
{
	phone,
	message,
	pong,
	snake,
	files,
	chrono,
	editor,
	paxo,
	calcul,
	hour,
	info,
};

String (*adress[])(void) = 
{
	ad_phone,
	ad_message,
	ad_pong,
	ad_snake,
	ad_files,
	ad_chrono,
	ad_editor,
	ad_paxo,
	ad_calcul,
	ad_hour,
	ad_info,
};



#include "menu.h" // NE PAS MODIFIER
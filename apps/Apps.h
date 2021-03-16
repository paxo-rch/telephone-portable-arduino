/* Les applications sont a #include ici */

#include "message.h"
#include "phone.h"
#include "pong.h"
#include "snake.h"
#include "files.h"
#include "chrono.h"
#include "editor.h"
#include "paxo.h"
#include "calcul.h"

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
};



#include "menu.h" // NE PAS MODIFIER
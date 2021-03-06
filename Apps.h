/* Les applications sont a #include ici */

#include "message.h"
#include "phone.h"
#include "pong.h"
#include "snake.h"

/* Les applications sont a declarer ici avec une "," */
void (*apps[])(void) = 
{
	phone,
	message,
	pong,
	snake,
};

void (*adress[])(void) = 
{
	ad_phone,
	ad_message,
	ad_pong,
	ad_snake,
};



#include "menu.h" // NE PAS MODIFIER
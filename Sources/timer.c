#include "derivative.h"
#include "gendefs.h"
#include "timer.h"
#include "leds.h"


#pragma DATA_SEG DIRECT MY_ZEROPAGE

static unsigned int delay ;
static unsigned int ledtimer = LEDTIM;




/* aqui cada 1 ms - llamada desde interrupt del timer */

void
timer(void)
{
	if( delay )
		--delay;
		
}

void
delay_ms(unsigned int t)
{
	delay = t;
	while( delay )
		wait();	
}



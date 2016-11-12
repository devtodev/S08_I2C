#include "derivative.h" /* alli donde se define hardware del micro */
#include "leds.h"



void
clear_leds(void)
{
    LEDPORT = 0;   
}




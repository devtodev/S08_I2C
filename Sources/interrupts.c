#include "derivative.h"
#include "gendefs.h"
#include "vectors_QE8.h"
#include "timer.h"
#include "display_led.h"

/* llamada desde el hardware por una interrupcion
    de evento de Timer Overflow ( bit TOF ) */

interrupt  
TIMER1_OVF_VECTOR
void
TIMERTICK_interrupt(void)
{
    /* aqui cada 1 ms */

 	TPM1SC_TOF = 0; /* bajar el flag de interrupt por TOF */
	timer();
	display();
}


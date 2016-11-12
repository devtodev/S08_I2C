#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "gendefs.h"
#include "display_led.h"
#include "timer.h"
#include "RTC.h"

void MCU_init(void);

void 
main(void) 
{
    unsigned char hh , mm;
    
    MCU_init();         /* HARDWARE */
 //   init_RTC();         /* SOLO 1 VEZ PARA PONER EN HORA */
    
    EnableInterrupts;
    
    forever
    {
        hh = get_RTC_minutos();
        mm = get_RTC_segundos();
        print_reloj( hh , mm );
        delay_ms(250);
    }
}



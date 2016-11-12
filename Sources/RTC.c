#include "derivative.h"
#include "I2C.h"
#include "RTC.h"

static char rtc[RTCREGS];


void
init_RTC(void)
{
    stop_RTC();
    set_horas(0x11);
    set_minutos(0x16); 
    set_dia(VIERNES);
    set_fecha(0x20);
    set_mes(MAYO);    
    set_year(0x13);
    set_control(0x43); /* salida 32768 Hz */
    set_calibration(0);
    start_RTC();
}

unsigned char
write_RTC_register( unsigned char rtcaddress , unsigned char rtcdata )
{
    return I2C_write_byte( RTCADDRESS , rtcaddress , rtcdata , RTCWDELAY);
}

unsigned char
read_RTC_register( unsigned char rtcaddress )
{
    return I2C_read_byte( RTCADDRESS , rtcaddress );
}

void
stop_RTC(void)
{
    write_RTC_register(0,0);        
}
void
start_RTC(void)
{
    char x;
    
    for( x = MINUTES ; x <= CALIBRATION ; ++x )
        write_RTC_register( x , rtc[x]);    

    write_RTC_register(0,0x80);
}

void
set_segundos(char secs)
{
    rtc[SECONDS] = secs;
}

void
set_minutos(char mins)
{
    rtc[MINUTES] = mins;
}

void
set_horas(char horas)
{
    rtc[HOURS] = horas;
}

void
set_dia(char dia)
{
    rtc[DAY] = dia;
}

void
set_fecha(char fecha)
{
    rtc[DATE] = fecha;
}

void
set_mes(char mes)
{
    rtc[MONTH] = mes;
}

void
set_year(char year)
{
    rtc[YEAR] = year;
}

void
set_control(char control)
{
    rtc[CONTROL] = control;
}

void
set_calibration(char calibration)
{
    rtc[CALIBRATION] = calibration;
}

void
set_RTCRAM( char address , char data)
{
    write_RTC_register( address+RTCOFFSET , data );
}

unsigned char
get_RTCRAM(char address)
{
    return read_RTC_register( address+RTCOFFSET);
}


char
get_RTC_segundos(void)
{
	return read_RTC_register( 0 ) & 0x7F;
}

char
get_RTC_minutos(void)
{
	return read_RTC_register( 1 ) & 0x7F;	
}

char
get_RTC_horas(void)
{
	return read_RTC_register( 2 ) & 0x3F;	
}

char
get_RTC_dia(void)
{
	return read_RTC_register( 3 ) & 0x07;		
}

char
get_RTC_fecha(void)
{
	return read_RTC_register( 4 ) & 0x3F;		
}

char
get_RTC_mes(void)
{
	return read_RTC_register( 5 ) & 0x1F;	
}

char
get_RTC_ano(void)
{
	return read_RTC_register( 6 ) ;	
}







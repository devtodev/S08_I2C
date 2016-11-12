#include "derivative.h"
#include <stdio.h>
#include "display_led.h"


static unsigned char disbuf[MAXDIGS];
static char str[5];
static unsigned char ans = ANSINIT;

static void shftdelay(void);
static void shift_out(unsigned char c);


/*  llamada desde interrupt del timer
    cada 1 ms */

void
display(void)
{
    static char digcount;
    static unsigned char temp;
    
    shift_out(0);       /* apagar barras */
    
    temp = ANSPORT;
    temp |= ANSOFF;
    ANSPORT = temp;    /* apagar anodos */
    
    shift_out(disbuf[digcount]);
    
    temp = ANSPORT;
    temp &= 0xF0;
    temp |= ( ~ans & 0x0F) ;
   
    ans >>= 1;
    
    if( ++digcount >= MAXDIGS )
    {
        digcount = 0;
        ans = ANSINIT;    
    }
    
    ANSPORT = temp;     /* la mascara está negada - los anodos encienden con ceros */
}


static const char bin_to_seg[] =
{
    CERO , UNO , DOS , TRES , CUATRO , CINCO,
    SEIS , SIETE, OCHO, NUEVE, BLANK 
};


void
shftdelay(void)
{
    asm "NOP";
    asm "NOP";
    asm "NOP";
    asm "NOP";
    asm "NOP";
}

#define MAXBITS 8
#define SHMASK  0x80

void
shift_out(unsigned char c)
{
    char x;
    unsigned char mask = SHMASK;
    
    for( x = 0 ; x < MAXBITS ; ++x )
    {
        if( c & mask )
            DATA = 1;
        else
            DATA = 0;

        mask >>= 1;
        
        CLK = 1;
        shftdelay();
        CLK = 0;                                        
    }
    LAT = 1;
    shftdelay();
    LAT = 0;
}


void
print_reloj( unsigned char h , unsigned char m )
{
    print_display_led( m & 0x0F , 0 ); 
    print_display_led( m >> 4 , 1 ); 
    print_display_led( h & 0x0F, 2 ); 
    print_display_led( h >> 4, 3 );    /* MAS SIGNIFICATIVO */  
}


void
print_display_led( char n , char pos )
{
    disbuf[pos] = bin_to_seg[n];
}

//#define OPTION  1

void
print_int_2_display(int n)
{
    int a , b , c , d , ibcd;
    unsigned char bcd[2];
    
    str[0] = '\0' ;
    
    #ifdef OPTION
 
     (void) sprintf( str , "%04d" , n );    
    print_display_led( str[0] - '0' , 3 );
    print_display_led( str[1] - '0' , 2 );
    print_display_led( str[2] - '0' , 1 );
    print_display_led( str[3] - '0' , 0 );
 
    #else

    if( n > 9999)
    {
         bcd[0] = bcd[1] = 0x99;
         return;
    }
    
	d = n / 1000;
	a = d; 
	d = n - ((n / 1000) * 1000 ) ; 
	b = d/100;
	d = d - (( d / 100) * 100); 
	c = d / 10 ; 
	d = d - (( d / 10) * 10);

	ibcd = a << 12;
	ibcd += b << 8;
	ibcd += c << 4;
	ibcd += d;

	bcd[0] = (unsigned char)(ibcd >> 8);
	bcd[1] = (unsigned char) ibcd;
 
    print_display_led( bcd[0] >> 4   , 3 );
    print_display_led( bcd[0] & 0x0F , 2 );
    print_display_led( bcd[1] >> 4   , 1 );
    print_display_led( bcd[1] & 0x0F , 0 );
    #endif
}
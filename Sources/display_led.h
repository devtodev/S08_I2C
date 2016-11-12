
#define MAXDIGS     4
#define SEGPORT     PTBD    /* puerto de segmentos o barras */
#define ANSPORT     PTAD    /* puerto de anodos */   
#define ALLOFF      0
#define ANSINIT     0x08    /* condicion inicial de anodos */
#define ANSOFF      0x0F    /* anodos apagados */
#define LAT         PTBD_PTBD4
#define CLK         PTBD_PTBD1
#define DATA        PTBD_PTBD0

void display(void);
void print_display_led( char n , char pos );
void print_int_2_display(int n);
void print_reloj( unsigned char h , unsigned char m );

/* definicion de segmentos del display */

#define	A			1
#define	B			2
#define	C			4
#define	D			8
#define	E			16
#define	F			32
#define	G			64
#define	DP			128

/* definicion de digitos del display */

#define	BLANK		0
#define	CERO		A+B+C+D+E+F
#define	UNO			B+C
#define	DOS			A+B+G+E+D
#define	TRES		A+B+C+D+G
#define	CUATRO		F+G+B+C
#define	CINCO		A+F+G+C+D
#define SEIS		A+F+E+D+C+G
#define	SIETE		A+B+C
#define	OCHO		A+B+C+D+E+F+G
#define	NUEVE		A+B+C+F+G
#define GUION		G
#define LET_PP		A+B+G+E+F
#define LET_R		E+G
#define LET_HH		B+C+E+F+G
#define LET_FF		A+G+F+E
#define LET_I		C
#define LET_N		E+G+C
#define LET_CC		A+F+E+D
#define LET_EE		A+F+E+G+D
#define LET_LL		F+E+D
#define LET_UU		F+E+D+C+B
#define LET_AA		A+B+C+F+E+G
#define LET_BB		C+D+E+F+G
#define LET_DD		B+C+D+E+G
#define LET_T		D+E+F+G
#define LET_SS		A+F+G+C+D


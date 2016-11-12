
/*  Definiciones para el chip Microchip MCP7940 */

#define RTCADDRESS  0xDE
#define RTCWDELAY   0       /* no write delay for RTC */
#define RTCREGS     22      /* todo el mapa de registros del RTC */
#define RTCRAM      0x3F    /* tamaño de la RAM */
#define RTCOFFSET   0x20    /* offset al comienzo del banco de memoria RAM */


enum{   SECONDS,MINUTES,HOURS,DAY,DATE,MONTH,YEAR,CONTROL,CALIBRATION,RESERVED,
        A1_SECONDS,A1_MINUTES,A1_HOURS,A1_DAY,A1_DATE,A1_MONTH,A1_RESERVED,
        A2_SECONDS,A2_MINUTES,A2_HOURS,A2_DAY,A2_DATE,A2_MONTH,A2_RESERVED      };
        
enum{   RESERVADO1,DOMINGO,LUNES,MARTES,MIERCOLES,JUEVES,VIERNES,SABADO};
enum{   RESERVADO2,ENERO,FEBRERO,MARZO,ABRIL,MAYO,JUNIO,JULIO,AGOSTO,SETIEMBRE,OCTUBRE,NOVIEMBRE,DICIEMBRE}; 


unsigned char write_RTC_register( unsigned char rtcaddress , unsigned char rtcdata );
unsigned char read_RTC_register( unsigned char rtcaddress );

void init_RTC(void);
void stop_RTC(void);
void start_RTC(void);
void set_segundos(char secs);
void set_minutos(char mins);
void set_horas(char horas);
void set_dia(char dia);
void set_fecha(char fecha);
void set_mes(char mes);
void set_year(char year);
void set_control(char control);
void set_calibration(char calibration);
char get_RTC_segundos(void);
char get_RTC_minutos(void);
char get_RTC_horas(void);
char get_RTC_dia(void);
char get_RTC_fecha(void);
char get_RTC_mes(void);
char get_RTC_ano(void);
void set_RTCRAM( char address , char data);
unsigned char get_RTCRAM(char address);











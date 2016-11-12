#include "derivative.h"
#include "gendefs.h"
#include "I2C.h"
#include "timer.h"


/*
 *	Funciones para manejar un dispositivo por medio de IIC
 */


unsigned char
I2C_write_byte( unsigned char i2caddress , unsigned char address , unsigned char data , char delay)
{
	IIC_delay();
	
	IIC_start();
	
	shift_8_bits_out(i2caddress+WRITEMASK ); /* transmitir device address + write */
	if( get_ACK() == IIC_NOACK )	/* obtener y validar ACK */		
	{
		IIC_stop();	
		return 0x20;
	}
	shift_8_bits_out(address);		/* transmitir memory address */
	if( get_ACK() == IIC_NOACK )	/* obtener y validar ACK */		
	{
		IIC_stop();
		return 0x30;
	}
	shift_8_bits_out(data);			/* transmitir memory data */
	if( get_ACK() == IIC_NOACK )	/* obtener y validar ACK */		
	{	
		IIC_stop();	
		return 0x40;
	}

	/* ACK polling for write cycle timing */
	
	IIC_stop();						/* start write cycle */
	
    delay_ms(delay);                /* demora de escritura */
				
	return data;
}

unsigned char 
I2C_read_byte( unsigned char i2caddress , unsigned char address )
{
	char c;
	
	IIC_delay();

	IIC_start();
	
	shift_8_bits_out(i2caddress+WRITEMASK ); /* transmitir device address + write */
	if( get_ACK() == IIC_NOACK )			 /* obtener y validar ACK */		
	{
		IIC_stop();	
		return 0x50;
	}
		
	shift_8_bits_out(address); 				 /* memory address */
	if( get_ACK() == IIC_NOACK )			 /* obtener y validar ACK */		
	{	
		IIC_stop();
		return 0x60;
	}

	IIC_start();	/* repeated start */	
	
	shift_8_bits_out(i2caddress+READMASK );  /* transmitir device address + read */
	if( get_ACK() == IIC_NOACK )			 /* obtener y validar ACK */		
	{
		IIC_stop();	
		return 0x70;
	}
	
	c = shift_8_bits_in();					 /* leer memory data */
	
	send_NACK();
		
	IIC_stop();
	IIC_delay();
	
	return c;
		
}

void
init_eeprom(void)
{
	IIC_idle();
	scl_is_output();
	sda_is_output();	
	IIC_delay();	
}

static
void
shift_8_bits_out( char c )
{
	unsigned char shmask;
	
	sda_is_output();
	shmask = SHIFTMASK ;	
	
	while( shmask )					/* transmitir device address + write */
	{
		if( shmask & c )			/* escribir estado logico del bit */
			SDA = 1;
		else
			SDA = 0;
		
		IIC_delay();				/* clock */
		SCL = 1;
		IIC_delay();
		SCL = 0;
		IIC_delay();
		
		shmask >>= 1;	
				
	}
	
	sda_is_input();					/* poner la linea de datos como entrada para ACK */
	IIC_delay();
}


static
char
shift_8_bits_in(void)
{	
	unsigned char shmask , data ;
	
	shmask = SHIFTMASK;
	
	sda_is_input();
	
	IIC_delay();
	
	while( shmask )					/* leer memory data */
	{
		data <<= 1;
		
		SCL = 1;
		IIC_delay();
		
		if( SDA == 1 )
			data |= DATAMASK ;
		else
			data &= ~DATAMASK ;
	
		shmask >>= 1;
		
		SCL = 0;
		IIC_delay();
	}
	
	SDA = 1;
	sda_is_output();
	IIC_delay();
	return data;
}


static 
char
get_ACK(void)
{
	char x;
	
	SCL = 1 ;			/* clock hi */
	IIC_delay();
	
	x = SDA;			/* leer estado del ACK */
	IIC_delay();
	
	SCL = 0;			/* clock low */
	IIC_delay();	
	
	SDA = 1;			/* reponer la linea de datos como salida = HI */
	sda_is_output();	
	IIC_delay();
	
	return x ;
}

static
void
send_ACK(void)
{
	SDA = 0;
	IIC_delay();
	
	SCL = 1;
	IIC_delay();
	
	SCL = 0;
	IIC_delay();
}

static
void
send_NACK(void)
{
	SDA = 1;
	IIC_delay();
	
	SCL = 1;
	IIC_delay();
	
	SCL = 0;
	IIC_delay();
	
}

static
void
IIC_delay(void)
{
		
}

static
void
IIC_start(void)
{
	SDA = 1;
	sda_is_output();
	IIC_delay();
	
	SCL = 1;
	IIC_delay();
	
	SDA = 0;
	IIC_delay();
	
	SCL = 0;
	IIC_delay();
}

static
void
IIC_stop(void)
{
	SDA = 0;
	sda_is_output();
	IIC_delay();
		
	SCL = 1;
	IIC_delay();
	
	SDA = 1;
	IIC_delay();
	
}


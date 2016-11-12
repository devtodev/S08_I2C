
#define	SDA		PTBD_PTBD2      /* bit del port */
#define SDADDR	PTBDD_PTBDD2    /* data direction register del bit */
#define SCL		PTBD_PTBD3      /* bit del port */
#define SCLDDR	PTBDD_PTBDD3    /* data direction register del bit */

#define WRITEMASK	0x00
#define READMASK	0x01
#define SHIFTMASK	0x80
#define DATAMASK	0x01


#define	sda_is_output()	(SDADDR = 1)
#define	sda_is_input()	(SDADDR = 0)
#define	scl_is_output()	(SCLDDR = 1)
#define	scl_low()		(SCL = 0)
#define	scl_hi()		(SCL = 1)
#define	sda_low()		(SDA = 0)
#define	sda_hi()		(SDA = 1)
#define IIC_idle()		(SCL = 1 , SDA = 1)


enum { IIC_ACK ,IIC_NOACK };

unsigned char I2C_write_byte( unsigned char i2caddress , unsigned char address , unsigned char data , char delay);
unsigned char I2C_read_byte( unsigned char i2caddress , unsigned char address );


static void shift_8_bits_out( char c );
static char shift_8_bits_in(void);
static char get_ACK(void);
static void send_ACK(void);
static void send_NACK(void);
static void IIC_delay(void);
static void IIC_start(void);
static void IIC_stop(void);
static void delay_10_ms(void);


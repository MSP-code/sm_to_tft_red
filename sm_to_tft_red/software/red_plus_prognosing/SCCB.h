#ifndef _SCCB_H
#define _SCCB_H

#include"altera_avalon_pio_regs.h"
#include"system.h"
#define OUT 1
#define IN 0
/*
#define SCCB_DDR		DDRC
#define SCCB_PORT		PORTC
#define SCCB_PIN		PINC

#define SCCB_SIO_C		0
#define SCCB_SIO_D		1
*/
#define SIO_C_SET		IOWR_ALTERA_AVALON_PIO_DATA(SCL_BASE, 1)//{SCCB_PORT|=(1<<SCCB_SIO_C);}
#define SIO_C_CLR		IOWR_ALTERA_AVALON_PIO_DATA(SCL_BASE, 0)//{SCCB_PORT&=~(1<<SCCB_SIO_C);}
#define SIO_D_SET		IOWR_ALTERA_AVALON_PIO_DATA(SDA_BASE, 1)//{SCCB_PORT|=(1<<SCCB_SIO_D);}
#define SIO_D_CLR		IOWR_ALTERA_AVALON_PIO_DATA(SDA_BASE, 0)//{SCCB_PORT&=~(1<<SCCB_SIO_D);}

#define SIO_D_IN		IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, IN)//{SCCB_DDR&=~(1<<SCCB_SIO_D);}
#define SIO_D_OUT		IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, OUT)//{SCCB_DDR|=(1<<SCCB_SIO_D);}

#define SIO_D_STATE	IORD_ALTERA_AVALON_PIO_DATA(SDA_BASE)  //((SCCB_PIN&(1<<SCCB_SIO_D))==(1<<SCCB_SIO_D))


///////////////////////////////////////////
void DelaySCCB(void);
//void InitSCCB(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char SCCBwriteByte(unsigned char m_data);
unsigned char SCCBreadByte(void);


#endif /* _SCCB_H */



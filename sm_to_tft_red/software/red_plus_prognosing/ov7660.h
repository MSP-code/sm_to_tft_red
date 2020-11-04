#ifndef _OV7660_H
#define _OV7660_H

#include "system.h"
#include "VARIABLE.h"
#include "font.h"
#include "SCCB.h"

/*
#define CMOS_CLK_DDR  DDRD
#define CMOS_CLK_PORT PORTD
#define CMOS_CLK_PIN  PIND
#define CMOS_CLK_BIT  5

#define CLK_ON	        CMOS_CLK_PORT|=1<<CMOS_CLK_BIT
#define CLK_OFF		    CMOS_CLK_PORT&=~(1<<CMOS_CLK_BIT)
*/
/////////////////////////////////////////
//void CLK_init(void);
unsigned char wrOV7660Reg(unsigned char regID, unsigned char regDat);
unsigned char rdOV7660Reg(unsigned char regID, unsigned char *regDat);
void OV7660_config_window(unsigned int startx,unsigned int starty,unsigned int width, unsigned int height);
//void delay_us(unsigned int time);
//void delay_ms(unsigned int time);//delay some time
unsigned char OV7660_init(void);


#endif /* _OV7660_H */




/*
 * LCD.c
 *
 *  Created on: 22 трав. 2014
 *      Author: KOLIA
 */
#include "altera_avalon_pio_regs.h"
#include "LCD.h"
#include "system.h"
#include "english_16x8.h"
#include "alt_types.h"
#include "unistd.h"

#include <stdio.h>
#include "english_16x8.h"

#define Bus_16        //16

unsigned char *m_pdiffimage;
unsigned int *m_ptemplate;
unsigned char *m_pbackground;
unsigned char *m_pgrayimage1;
unsigned char *m_pgrayimage2;

alt_u16 Y1[240][320],Y2[240][320];



alt_u16 DeviceCode;




void delayms(int count)   //  X1ms
{
 int i;
 for(i=0;i<count;i++)
  usleep(5);//1000hz,е¦—жљ±иЃ†и…•иї»зґєз¬ўйѓ”пџІе“Џйѓ”дї‡и—ќи…”жќ…ж“‚
}


void LCD_Writ_Bus(alt_u16 data)   //з”њдїґжќ…ж“‚иїЎп µж»Іжќ…
{
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_DATA_OUT_BASE,data);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE,1);
}
void LCD_Write_COM(alt_u16 data)  //жҐ·е†ћйџњйЌ”
{
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE,0);
    LCD_Writ_Bus(data);
}


void LCD_Write_DATA(alt_u16 data)    //жҐ·е†ћжќ…ж“‚
{
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE,1);
    LCD_Writ_Bus(data);
}
void LCD_WR_REG(unsigned int index,unsigned int data)
{
     LCD_Write_COM(index);
     LCD_Write_DATA(data);
}

//В¶Р‘С�Р”Т‘Р¶Р–С‡
alt_u16 LCD_ReadReg(alt_u16 LCD_Reg)
{
    alt_u16 t;
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);
    LCD_Write_COM(LCD_Reg);

    IOWR_ALTERA_AVALON_PIO_DIRECTION(LCD_DATA_OUT_BASE,0x0000);

    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE,1);////////////////////////////

    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE,0);//LCD_RD_CLR;
    delayms(5);//FOR 8989,РЎРЈРљВ±5us
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,0);//turning lcd_switch to read state
     t = IORD_ALTERA_AVALON_PIO_DATA(LCD_DATA_OUT_BASE);
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,1);//turning lcd_switch to write state
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE,1);
    delayms(5);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,1);

    IOWR_ALTERA_AVALON_PIO_DIRECTION(LCD_DATA_OUT_BASE,0xffff);   //Р…В«FPGAВµР”Р›В«РџС‚РљСЌР§Р¦С—РЄР™РёР¦Р“С–Р™РљРґС–С†

    return t;
}
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
    LCD_Write_COM(0x0020);LCD_Write_DATA(x1);    //ж‰ўз¦»Xй‡ґжў“еј‡з¦»
    LCD_Write_COM(0x0021);LCD_Write_DATA(y1);   //ж‰ўз¦»Yй‡ґжў“еј‡з¦»
    LCD_Write_COM(0x0050);LCD_Write_DATA(x1);   //зѕІе®ЋX
    LCD_Write_COM(0x0052);LCD_Write_DATA(y1);    //зѕІе®ЋY
    LCD_Write_COM(0x0051);LCD_Write_DATA(x2);   //иі¦ж—°X
    LCD_Write_COM(0x0053);LCD_Write_DATA(y2);   //иі¦ж—°Y
    LCD_Write_COM(0x0022);
}
void LCD_write_english(unsigned char data,unsigned int color,unsigned int xcolor)//иїЎи¶јзќ«
{

    unsigned char avl,i,n;
    LCD_Write_COM(0x0022);
    for (i=0;i<16;i++)
    {
      avl=english[data-32][i];
      for (n=0;n<8;n++)
       {
            if(avl&0x80) LCD_Write_DATA(color);
             else LCD_Write_DATA(xcolor);

         avl<<=1;
       }
    }
}
void LCD_write_english_string(unsigned int x,unsigned char y,char *s,unsigned int color,unsigned int xcolor)//иЌЋжЃ…и¶јзќ«жЏ№зЏ†е°Ё
{
 unsigned int k=0;
 IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);  //ж№–зѕІпљјжЃЃе¦Џе¤”
 while (*s)
  {
     Lcd_SetBox(y,x+k,16,8);
     LCD_write_english( *s,color,xcolor);
     k=k+8;
     s++;

  }

}
/**********************************************
ж»Іжќ…йќЎг„©LcdијёжЃЃж»Іжќ…
й«Ўе¤”г„©жЃЃйљ…LcdеҐ»зЎЊйљ…и…”ж’»еЂ›пћҐйѓ–

и›Ѓз ©г„©xStartзќї yStartе‘ґи¦‚п›‘иє‰и…”е”…и›ЊеҐ§ињЉж›№г„›еј‡з¦»еІ†ж’»еЂ›йЃєи…”дѕђи·єи¤’

п µи«ізµ±жќ…г„©xStart xжєђз ѓи…”пњЂе®Ћиђё
          ySrart yжєђз ѓи…”з¬ќз ¦иђё
          xLong зЊЃжЃЃйљ…ж’»еЂ›и…”xжєђз ѓй…—еѓ…
          yLong  зЊЃжЃЃйљ…ж’»еЂ›и…”yжєђз ѓй…—еѓ…
ж®їйљ™зЎ‰г„©ж‹ё
***********************************************/
void Lcd_SetBox(unsigned char xStart,unsigned int yStart,unsigned char xLong,unsigned int yLong)
{
    LCD_SetCursor(xStart,312-yStart);

    LCD_WR_REG(0x0050,xStart);//й�Ёп›Ќ GRAMпњЂе®Ћеј‡з¦»
    LCD_WR_REG(0x0051,xStart+xLong-1);//й�Ёп›ЌGRAMз¬ќз ¦еј‡з¦»
    LCD_WR_REG(0x0052,312-yStart);//ж™¶зњ»GRAMпњЂе®Ћеј‡з¦»
    LCD_WR_REG(0x0053,312-yStart+yLong-1);//ж™¶зњ»GRAMз¬ќз ¦еј‡з¦»
}


/*************************************************
ж»Іжќ…йќЎг„©Lcdе«–жў“пњЂиђёйљ…еј‡ж»Іжќ…
й«Ўе¤”г„©зЎЊйљ…320240зЏ�е„’еҐ»и…”зЏЁиђёй‡¬еі€иїЎжќ…ж“‚и…”пњЂе®Ћиђё
п µи«ізµ±жќ…г„©x й‡ґжў“ 0~239
          y й‡ґжў“ 0~319
ж®їйљ™зЎ‰г„©ж‹ё
*************************************************/
void LCD_SetCursor(unsigned char Xpos, unsigned char Ypos)
{
 // CLR_RS;
  LCD_WR_REG(0x20, Xpos);
  LCD_WR_REG(0x21, Ypos);
}
/*===========================================================================
** ж»Іжќ…йќЎе‚™: LCD_reset()
** й«Ўе¤”йЏЎж‰ґ: и‘©еј‡LCDг„›и›Ѓз ©г„›иЎ„еҐЂе‰’и¦ѓж·•пќќз¶ґи¬—и·єdelay()и…”жЂЂп µзЎ‰ж№®и‹¤
============================================================================*/



void LCD_reset(void)
{
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_BASE,0);
    delayms(5);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_BASE,1);
    delayms(5);
}
//================
void Pant(alt_u16 data)
{
    int i,j;

    Address_set(0,0,239,319);
    for(i=0;i<320;i++)
     {
      for (j=0;j<240;j++)
        {
             LCD_Write_DATA(data);
        }

      }

}
//===================================
void LCD_Init(void)
{
	 IOWR_ALTERA_AVALON_PIO_DIRECTION(LCD_DATA_OUT_BASE,0xffff);   //Р…В«FPGAВµР”Р›В«РџС‚РљСЌР§Р¦С—РЄР™РёР¦Р“С–Р™РљРґС–С†
		    LCD_WriteReg(0x0000,0x0001);
		    delayms(5); // delay 50 ms

		/*  DeviceCode = LCD_ReadReg(0x0000);

		    printf(" LCD ID:%x\n",DeviceCode);
*/
	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_BASE,1);
	    delayms(5);
	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_BASE,0);
	    delayms(5);
	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_BASE,1);
	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,1);
	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE,1);
	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_WR_BASE,1);
	    delayms(5);


	    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);

LCD_WriteReg(0x0001,0x0100);	  /* Driver Output Contral Register  */
        		LCD_WriteReg(0x0002,0xFFFF);      /* LCD Driving Waveform Contral was0x0700 */
        		LCD_WriteReg(0x0003,0x1018);	  /* Entry ModeР™РёР¦Р“ was0x1030*/

        		LCD_WriteReg(0x0004,0x0000);	  /* Scalling Control register */
        		LCD_WriteReg(0x0008,0x0202);	  /* Display Control 2 */
        		LCD_WriteReg(0x0009,0x0000);	  /* Display Control 3 */
        		LCD_WriteReg(0x000A,0x0000);	  /* Frame Cycle Control */
        		LCD_WriteReg(0x000C,0x0000);	  /* External Display Interface Control 1  */
        		LCD_WriteReg(0x000D,0x0000);      /* Frame Maker Position */
        		LCD_WriteReg(0x000F,0x00c0);	  /* External Display Interface Control 2 */
        		delayms(50);
        		LCD_WriteReg(0x0007,0x0133);	  /* Display Control was 133 */
        		delayms(50);
        		LCD_WriteReg(0x0010,0x16B0);      /* Power Control 1 */
        		LCD_WriteReg(0x0011,0x0001);      /* Power Control 2 */
        		LCD_WriteReg(0x0017,0x0001);      /* Power Control 3 */
        		LCD_WriteReg(0x0012,0x0138);      /* Power Control 4 */
        		LCD_WriteReg(0x0013,0x0800);      /* Power Control 5 */
        		LCD_WriteReg(0x0029,0x0009);	  /* NVM read data 2 */
        		LCD_WriteReg(0x002a,0x0009);	  /* NVM read data 3 */
        		//LCD_WriteReg(0x00a4,0x0000);
        		LCD_WriteReg(0x0050,0x0000);
        		LCD_WriteReg(0x0051,0x00EF);//0xef
        		LCD_WriteReg(0x0052,0x0000);
        		LCD_WriteReg(0x0053,0x013F);//13E

        		LCD_WriteReg(0x0060,0x2700);	  /* Driver Output Control */

        		LCD_WriteReg(0x0061,0x0001);	  /* Driver Output Control */
        		LCD_WriteReg(0x006A,0x0000);	  /* Vertical Scroll Control */

        		LCD_WriteReg(0x0080,0x0000);	  /* Display Position РЃC Partial Display 1 */
        		LCD_WriteReg(0x0081,0x0000);	  /* RAM Address Start РЃC Partial Display 1 */
        		LCD_WriteReg(0x0082,0x0000);	  /* RAM address End - Partial Display 1 */
        		LCD_WriteReg(0x0083,0x0000);	  /* Display Position РЃC Partial Display 2 */
        		LCD_WriteReg(0x0084,0x0000);	  /* RAM Address Start РЃC Partial Display 2 */
        		LCD_WriteReg(0x0085,0x0000);	  /* RAM address End РЃC Partail Display2 */
        		LCD_WriteReg(0x0090,0x0010);	  /* Frame Cycle Control */
        		LCD_WriteReg(0x0092,0x0000); 	  /* Panel Interface Control 2 */
        		LCD_WriteReg(0x0093,0x0003);	  /* Panel Interface control 3 */
        		LCD_WriteReg(0x0095,0x0000);	  /* Frame Cycle Control */
        		LCD_WriteReg(0x0097,0x0000);
        		LCD_WriteReg(0x0098,0x0000);
        		LCD_WriteReg(0x0007,0x0173);//173


    delayms(50);

    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,1);  //еЈЅж••пљјжЃЃе¦Џе¤”
}



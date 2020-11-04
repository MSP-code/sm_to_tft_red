//#include "ov7660config.c"
#include "SCCB.h"
#include "delay.h"
////////////////////////////
//¹¦ÄÜ£ºÌá¹©7660Ê±ÖÓ
//·µ»Ø£ºÎÞ
/*void CLK_init(void)
{
   CLK_ON;
}
*/
////////////////////////////
//¹¦ÄÜ£ºÐ´OV7660¼Ä´æÆ÷
//·µ»Ø£º1-³É¹¦	0-Ê§°Ü

#define CHANGE_REG_NUM 121//120 for ov7660/176 ov7670
unsigned char change_reg[CHANGE_REG_NUM][2]=
{

			{ 0x00 , 0x00 },//COM1   { 0x00 , 0x00 },
		    { 0x01 , 0x80 },//COM1
		    { 0x02 , 0x80 },//COM1
		    { 0x03 , 0x00 },//COM1
		    { 0x04 , 0x03 },//COM1
		    { 0x07 , 0xff },
		    { 0x09 , 0x03 },//COM2
		    { 0x10 , 0x40 },//
		    { 0x0C , 0x04 },//COM3 0x42=MSB LSB swap   { 0x0C , 0x04 }?????
		    { 0x0E , 0x81 }, //com5 48MHz
		    { 0x0F , 0x09 },//COM6   { 0x0F , 0xCB },
		    { 0x11 , 0x83 },//CLKRC  2M PCLK///83 pclk 48/4
		    { 0x12 , 0x14 }, //COM7  QVGA RGB   { 0x12 , 0x14 },
		    { 0x13 , 0x83 }, //COM8-8F// a2 äëÿ ðàáîòû â òåìíîòå agc äîëæåí á³òü âûêëþ÷åí
		    { 0x14 , 0x4a },//COM9  { 0x14 , 0x4a },agc äîëæåí á³òü 0
		    { 0x15 , 0x00 }, //COM10  PCLK
		    { 0x23 , 0x80 }, //r-adblc
		    { 0x24 , 0x78 }, //AEW-30
		    { 0x25 , 0x68 }, //AEB-85
		    { 0x2a , 0x00 }, // 50HZ
		    { 0x2b , 0x9d },
		    { 0x37 , 0x04 }, //adc-00
		    { 0x3B , 0x08 },
		    { 0x3D , 0x00 }, //
		    { 0x40 , 0xd0 }, //COM15  RGB565 out
		    { 0x69 , 0x50 }, //HV
		    { 0x27 , 0x95 }, //HV
		    { 0x28 , 0xe0 }, //HV
		    { 0x41 , 0x20 }, //HV

		    { 0x4F , 0x80 }, //HV
		    { 0x50 , 0x86 }, //HV
		    { 0x51 , 0x06 }, //HV
		    { 0x52 , 0x20 }, //HV
		    { 0x53 , 0x50 }, //HV
		    { 0x54 , 0x70 }, //HV

		    { 0x6C , 0xf0 },
		    { 0x6D , 0xf0 },
		    { 0x6E , 0xf0 },
		    { 0x6F , 0x70 },
		    { 0x70 , 0x58 },
		    { 0x71 , 0x58 },
		    { 0x72 , 0x48 },
		    { 0x73 , 0x48 },
		    { 0x74 , 0x38 },
		    { 0x75 , 0x40 },
		    { 0x76 , 0x34 },
		    { 0x77 , 0x34 },
		    { 0x78 , 0x2e },
		    { 0x79 , 0x28 },
		    { 0x7a , 0x24 },
		    { 0x7b , 0x22 },
		    { 0x7C , 0x0f },
		    { 0x7D , 0x1e },
		    { 0x7E , 0x3c },
		    { 0x7F , 0x58 },
		    { 0x80 , 0x63 },
		    { 0x81 , 0x6e },
		    { 0x82 , 0x77 },
		    { 0x83 , 0x80 },
		    { 0x84 , 0x87 },
		    { 0x85 , 0x8f },
		    { 0x86 , 0x9C },
		    { 0x87 , 0xa9 },
		    { 0x88 , 0xc0 },
		    { 0x89 , 0xd4 },
		    { 0x8A , 0xE6 },

		    { 0x3f , 0x81 },
		    { 0x41 , 0x00 },
		    { 0xa1 , 0xc8 },

		    { 0x3a , 0x00 },
		    { 0x67 , 0x80 },
		    { 0x68 , 0x80 },
		    { 0x9D , 0x99 },//b50f-66

		    { 0x20,  0xff }, //COM7  QVGA RGB

};

unsigned char wrOV7660Reg(unsigned char regID, unsigned char regDat)
{
	startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	//usleep(100);
	delay_us(100);
  	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	//usleep(100);
  	delay_us(100);
  	if(0==SCCBwriteByte(regDat))
	{
		stopSCCB();
		return(0);
	}
  	stopSCCB();
	
  	return(1);
}
////////////////////////////
//¹¦ÄÜ£º¶ÁOV7660¼Ä´æÆ÷
//·µ»Ø£º1-³É¹¦	0-Ê§°Ü
unsigned char rdOV7660Reg(unsigned char regID, unsigned char *regDat)
{
	//Í¨¹ýÐ´²Ù×÷ÉèÖÃ¼Ä´æÆ÷µØÖ·
	startSCCB();
	if(0==SCCBwriteByte(0x42))
	{
		stopSCCB();
		return(0);
	}
	//usleep(100);
	delay_us(100);
	if(0==SCCBwriteByte(regID))
	{
		stopSCCB();
		return(0);
	}
	stopSCCB();
	
	//usleep(100);
	delay_us(100);
	//ÉèÖÃ¼Ä´æÆ÷µØÖ·ºó£¬²ÅÊÇ¶Á
	startSCCB();
	if(0==SCCBwriteByte(0x43))
	{
		stopSCCB();
		return(0);
	}
	//usleep(100);
	delay_us(100);
	*regDat=SCCBreadByte();
  	noAck();
  	stopSCCB();
  	return(1);
}


//(140,16,640,480) is good for VGA
//(272,16,320,240) is good for QVGA
/* config_OV7660_window */
void OV7660_config_window(unsigned int startx,unsigned int starty,unsigned int width, unsigned int height)
{
	unsigned int endx;
	unsigned int endy;// "v*2"±ØÐë
	unsigned char temp_reg1, temp_reg2;
	unsigned char state, temp;
	
	endx=(startx+width);
	endy=(starty+height+height);// "v*2"±ØÐë
	state = rdOV7660Reg(0x03, &temp_reg1 );
	temp_reg1 &= 0xf0;
	state = rdOV7660Reg(0x32, &temp_reg2 );
	temp_reg2 &= 0xc0;
	
	// Horizontal
	temp = temp_reg2|((endx&0x7)<<3)|(startx&0x7);
	state = wrOV7660Reg(0x32, temp );
	temp = (startx&0x7F8)>>3;
	state = wrOV7660Reg(0x17, temp );
	temp = (endx&0x7F8)>>3;
	state = wrOV7660Reg(0x18, temp );
	
	// Vertical
	temp = temp_reg1|((endy&0x3)<<2)|(starty&0x3);
	state = wrOV7660Reg(0x03, temp );
	temp = starty>>2;
	state = wrOV7660Reg(0x19, temp );
	temp = endy>>2;
	state = wrOV7660Reg(0x1A, temp );
}



/* OV7660_init() */
//·µ»Ø1³É¹¦£¬·µ»Ø0Ê§°Ü
unsigned char OV7660_init(void)
{
	unsigned char temp;
	
	unsigned int i=0;

	//uchar ovidmsb=0,ovidlsb=0;
	
//	InitSCCB();//io init..

	temp=0x80;

	if(0==wrOV7660Reg(0x12, temp)) //Reset SCCB
	{
		return 0 ;
	}
	delay_ms(5);



    wrOV7660Reg(0x39 ,0x57); //??

    wrOV7660Reg(0xa1 ,0x07); //  ??

    wrOV7660Reg(0x69 ,0x80);
    wrOV7660Reg(0x43 ,0xf0);
    wrOV7660Reg(0x44 ,0x10);
    wrOV7660Reg(0x45 ,0x78);
    wrOV7660Reg(0x46 ,0xa8);
    wrOV7660Reg(0x47 ,0x60);
    wrOV7660Reg(0x48 ,0x80);
    wrOV7660Reg(0x59 ,0xba);
    wrOV7660Reg(0x5a ,0x9a);
    wrOV7660Reg(0x5b ,0x22);
    wrOV7660Reg(0x5c ,0xb9);
    wrOV7660Reg(0x5d, 0x9b);
    wrOV7660Reg(0x5e ,0x10);
    wrOV7660Reg(0x5f ,0xe0);
    wrOV7660Reg(0x60 ,0x85);// ;05 for advanced AWB
    wrOV7660Reg(0x61 ,0x60);
    wrOV7660Reg(0x9f ,0x9d);
    wrOV7660Reg(0xa0 ,0xa0);  //

  
	for(i=0;i<CHANGE_REG_NUM;i++)
	{
		if( 0==wrOV7660Reg(change_reg[i][0],change_reg[i][1]))
		{
			return 0;
		}
	}

//OV7660_config_window(0,0,320,240);// set 240*320
	OV7660_config_window(384,56,128,128);// set 240*320
	//OV7660_config_window(280,18,320,240);// set 240*320
	return 0x01; //ok
} 


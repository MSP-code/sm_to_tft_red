
#include "ov7660.h"
#include "altera_avalon_pio_regs.h"


#include "system.h"
#include "altera_nios2_qsys_irq.h"
#include "sys/alt_irq.h"

#include "delay.h"
#include <stdio.h>
#include <math.h>

#include "alt_types.h"
#include "unistd.h"

#include "scr01.h"
#include "LCD.h"


#define VS_int_in_IRQ 1
#define VS_int_in_BASE 0x4003180
#define VS_int_in_IRQ_INTERRUPT_CONTROLLER_ID 0



int cadr_count=0;

unsigned char value;
volatile int edge_capture;
unsigned int	X,Y,R, Rf_in,flag_p;
float		fX, fY, fXp, fYp, fR;
char Xs[6],Ys[6],Rs[1],Xps[6],Yps[6];


void init_button_pio();
void odval_interrupts(void* context);


void init_button_pio() {
    /* Recast the edge_capture pointer to match the alt_irq_register() function
     * prototype. */
    void* edge_capture_ptr = (void*) &edge_capture;
    /* Enable first  button interrupts. */
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(VS_int_in_BASE, 0x3);
    /* Reset the edge capture register. */
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(VS_int_in_BASE, 0x3);
    /* Register the interrupt handler. */
    alt_ic_isr_register(VS_int_in_IRQ_INTERRUPT_CONTROLLER_ID, VS_int_in_IRQ, odval_interrupts, edge_capture_ptr,0X0 );
}


void odval_interrupts(void* context)

{
	int temp;

    volatile int* edge_capture_ptr = (volatile int*) context; // volatile variable to avoid optimization...
    *edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(VS_int_in_BASE);    // Store edge capture register in *context.
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(VS_int_in_BASE, 3);     // Reset edge capture register/1
    temp=IORD_ALTERA_AVALON_PIO_DATA(VS_int_in_BASE);
    switch (temp)
    {
    case 0:
    			IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,1);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_1ENA_BASE,0);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_2STROBE_BASE,1);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_2STROBE_BASE,0);

    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_MUX_BASE,2);
    	    	X=IORD_ALTERA_AVALON_PIO_DATA(SM_DATA_IN_BASE);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_MUX_BASE,1);
    	    	Y=IORD_ALTERA_AVALON_PIO_DATA(SM_DATA_IN_BASE);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_MUX_BASE,0);
    	    	R=IORD_ALTERA_AVALON_PIO_DATA(SM_DATA_IN_BASE);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_MUX_BASE,3);
    	    	Rf_in=IORD_ALTERA_AVALON_PIO_DATA(SM_DATA_IN_BASE);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_1CLR_BASE,1);
    	    	IOWR_ALTERA_AVALON_PIO_DATA(SM_1CLR_BASE,0);
    	    	flag_p=1;


    	     Address_set(56,96,183,223);

    	   LCD_SetCursor(56,223);
    	   // LCD_SetCursor(0,0);
    	    LCD_Write_COM(0x0022);
    		//LCD_Write_DATA(BLACK);//add one pixel for pixel staffing*/

    	    IOWR_ALTERA_AVALON_PIO_DATA(SM_1ENA_BASE,1);

    	    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,2);
    break;
    case 1:
    	IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,1);
    	LCD_write_english_string(112,10,Xs,WHITE,BLACK);
    	LCD_write_english_string(112,30,Ys,WHITE,BLACK);
    	LCD_write_english_string(202,10,Rs,WHITE,BLACK);
    	LCD_write_english_string(112,190,Xps,WHITE,BLACK);
    	LCD_write_english_string(112,210,Yps,WHITE,BLACK);

    	    	       Address_set(56,96,183,223);

    	    	    LCD_SetCursor(56,223);
    	    	   // LCD_SetCursor(0,0);
    	    	    LCD_Write_COM(0x0022);
    	    		//LCD_Write_DATA(BLACK);//add one pixel for pixel staffing

    	IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,2);
    break;
      }

    cadr_count++;

}
//CPUР ВµР’В РўвЂ�Р ВµР’В®Р вЂ№Р С‘Р’В¶РІвЂћСћ//
int main(void)
{
    volatile int tempx;
	unsigned int i, i1, Rprint;
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);  //Р В¶РІвЂћвЂ“РІР‚вЂњР В·РЎвЂўР вЂ Р С—РЎв„ўРЎпїЅР В¶Р С“Р С“Р ВµР’В¦Р РЏР ВµР’В¤РІР‚Сњ
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,1); ///////////////////////
    LCD_Init(); //Р ВµР’В РўвЂ�Р ВµР’В®Р вЂ№Р С‘Р’В¶РІвЂћСћLCD
    Address_set(0,0,239,319);   //Р В¶РІР‚В°РЎС›Р В·Р’В¦Р’В»LCDР ВµРІР‚вЂњРЎС™Р В¶РЎвЂ�Р Р‹
    Pant(LBLUE);    //Р В¶РІР‚РЋР’В¦Р Т‘РЎпїЅР вЂ№Р В¶Р вЂ№РІР‚вЂњР ВµР вЂ°РІР‚Сљ
     /////////////////////////////////////////////////////////

    LCD_write_english_string(30,10,"  Combination Method  2014-09-15",BLACK,RED);
    LCD_write_english_string(30,30,"FPGA & SPFD5408B+ TFT FOR OV7660",BLACK,RED);
    LCD_write_english_string(30,50,"FPGA  Ready!",BLACK,RED);
    printf("Combination Method  2014-09-15\n");
    printf("Created by SignallerK\n");
    printf("START system!\n");

    LCD_write_english_string(30,116,"OV7660 Init...",BLACK,RED);
    printf("START OV7660 !\n");


    while(1!=OV7660_init())
        LCD_write_english_string(30,116,"OV7660 Init......",BLACK,RED);//Р ВµР’В РўвЂ�Р ВµР’В®Р вЂ№Р С‘Р’В¶РІвЂћСћov7670
    LCD_write_english_string(30,136,"OV7660 Ready!",BLACK,RED);
    LCD_write_english_string(30,156,"SYSTEM OK!",BLACK,RED);
    for(i1=0;i1<3;i1++)
        delayms(90000);





    Address_set(0,0,239,319);

    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,0);  //Р В¶РІвЂћвЂ“РІР‚вЂњР В·РЎвЂўР вЂ Р С—РЎв„ўРЎпїЅР В¶Р С“Р С“Р ВµР’В¦Р РЏР ВµР’В¤РІР‚Сњ
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RD_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RS_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(LCD_RESET_BASE,1);

    delayms(90000);


    Address_set(0,0,239,319);

    Pant(BLACK);
    LCD_write_english_string(96,10,"X=",WHITE,BLACK);
    LCD_write_english_string(96,30,"Y=",WHITE,BLACK);
    LCD_write_english_string(88,190,"Xp=",WHITE,BLACK);
    LCD_write_english_string(88,210,"Yp=",WHITE,BLACK);
    LCD_write_english_string(186,10,"r=",WHITE,BLACK);

    Address_set(50,90,189,229);
    for(i=0;i<19600;i++)
                {
               	LCD_Write_DATA(WHITE);

                 }
    Address_set(56,96,183,223);



    IOWR_ALTERA_AVALON_PIO_DATA(LCD_CS_BASE,1);//LCD_CS =1;  //Р ВµР в‚¬Р вЂ¦Р В¶РІР‚СћРІР‚СћР С—РЎв„ўРЎпїЅР В¶Р С“Р С“Р ВµР’В¦Р РЏР ВµР’В¤РІР‚Сњ
    LCD_Init();
    printf("camera start!\n");
    //delayms(90000);
  //  Address_set(0,0,239,319);
    Address_set(56,96,183,223);
    //start SM
    IOWR_ALTERA_AVALON_PIO_DATA(SM_1CLR_BASE,1);
    IOWR_ALTERA_AVALON_PIO_DATA(SM_1CLR_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(SM_2STROBE_BASE,0);
    IOWR_ALTERA_AVALON_PIO_DATA(SM_1ENA_BASE,1);
    X=0;
    Y=0;
    R=0;
    //
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE,2);
    init_button_pio();



       //enable hw lcd control
do{
tempx++;
fX=*(float*)&X;
fY=*(float*)&Y;
fR=*(float*)&Rf_in;
if ((fR>=0.60)&&(fR<=0.90)&&(R<250))
	{
	 Rprint=1;
	sprintf(Rs,"%d", 1);
sprintf(Xs,"%06.2f", fX);
sprintf(Ys,"%06.2f", fY);
sprintf(Xps,"%06.2f", fXp);
sprintf(Yps,"%06.2f", fYp);

	}
else
	{
	 Rprint=0;
	sprintf(Rs,"%d", 0);
	}

if(flag_p)
{
	flag_p=0;
   printf("Frame # %d\n",cadr_count);
  /* printf("%f\n", fX);
   printf("%f\n", fY);
   printf("%f\n", fR);*/
   printf("X= %f, Y= %f\n",fX ,fY);
   printf("R = %d\n", Rprint);
  // printf("C = %d\n", R);
  fXp=fX*1.1-fXp*0.1;
  fYp=fY*1.1-fYp*0.1;

  if (__isnanf(fXp) || __isnanf(fYp))//check if prognozing is nan, if yes give 0.0
  {
	  fXp=fYp=0.0;
  }
 /* printf("%f\n", fXp);
  printf("%f\n", fYp);*/
  printf("Xp= %f, Yp= %f\n\n",fXp, fYp);

}
}
    while(1);

    return 0;
}


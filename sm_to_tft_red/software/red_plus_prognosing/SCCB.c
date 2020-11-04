#include "SCCB.h"
#include <stdio.h>
#include <sys/unistd.h>
#include <io.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "alt_types.h"
#include "ov7660.h"
#include "delay.h"

#define DELAY_TIME 100
/*-----------------------------------------------
   ����: start����,SCCB����ʼ�ź�
   ����: ��
 ����ֵ: ��
      SDA -------_________
     SCL ------------____ 
-----------------------------------------------
*/
void startSCCB(void)
{
    IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, OUT);
    SIO_D_SET;     //�����߸ߵ�ƽ
    usleep(DELAY_TIME);
    SIO_C_SET;     //��ʱ���߸ߵ�ʱ���������ɸ�����
    usleep(DELAY_TIME);
 
    SIO_D_CLR;
    usleep(DELAY_TIME);

    SIO_C_CLR;   //�����߻ָ��͵�ƽ��������������Ҫ
    usleep(DELAY_TIME);
}
/*
-----------------------------------------------
   ����: stop����,SCCB��ֹͣ�ź�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
 /*   SDA _________--------
      SCL ____------------- */
void stopSCCB(void)
{
    IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, OUT);  
    SIO_D_CLR;
    usleep(DELAY_TIME);
    SIO_C_SET;
    usleep(DELAY_TIME);
    SIO_D_SET;
    usleep(DELAY_TIME);
}
/*
-----------------------------------------------
   ����: noAck,����������ȡ�е����һ����������
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
/*   SDA ____zzzzzzzzzzzzz
      SCL ____------_______ */
void noAck(void)
{
    IOWR_ALTERA_AVALON_PIO_DIRECTION(SDA_BASE, IN);
    
    SIO_D_SET;
    usleep(DELAY_TIME);
    
    SIO_C_SET;
    usleep(DELAY_TIME);
    
    SIO_C_CLR;
   usleep(DELAY_TIME);
    
    SIO_D_CLR;
    usleep(DELAY_TIME);
}
/*
-----------------------------------------------
   ����: д��һ���ֽڵ����ݵ�SCCB
   ����: д������
 ����ֵ: ���ͳɹ�����1������ʧ�ܷ���0
-----------------------------------------------
*/
/*                 MSB
    SDA  ______-------------__________
  
    SCL  _________-------_____________ */ 
unsigned char   SCCBwriteByte( unsigned char m_data )
{
    unsigned char j,tem;

    for(j=0;j<8;j++) //ѭ��8�η�������
    {
        if((m_data<<j)&0x80)
        {
            SIO_D_SET;
        }
        else
        {
            SIO_D_CLR;
        }
        usleep(DELAY_TIME);
        SIO_C_SET;
        usleep(DELAY_TIME);
        SIO_C_CLR;
        usleep(DELAY_TIME);

    }
    usleep(DELAY_TIME);
    
    SIO_D_IN;/*����SDAΪ����*/
    usleep(DELAY_TIME);
    SIO_C_SET;
    usleep(DELAY_TIME);
    if(SIO_D_STATE)
    {
        tem=0;   //SDA=1����ʧ�ܣ�����0
    }
    else
    {
        tem=1;   //SDA=0���ͳɹ�������1
    }
    SIO_C_CLR;
    usleep(DELAY_TIME);  
        SIO_D_OUT;/*����SDAΪ���*/

    return(tem); 
}

/*
-----------------------------------------------
   ����: һ���ֽ����ݶ�ȡ���ҷ���
   ����: ��
 ����ֵ: ��ȡ��������
-----------------------------------------------
*/
unsigned char SCCBreadByte(void)
{
    unsigned char read,j;
    read=0x00;
    
    SIO_D_IN;/*����SDAΪ����*/
    usleep(DELAY_TIME);
    for(j=8;j>0;j--) //ѭ��8�ν�������
    {            
        usleep(DELAY_TIME);
        SIO_C_SET;
        usleep(DELAY_TIME);
        read=read<<1;
        if(SIO_D_STATE) 
        {
            read=read+1;
        }
        SIO_C_CLR;
        usleep(DELAY_TIME);
    }   
    return(read);
}

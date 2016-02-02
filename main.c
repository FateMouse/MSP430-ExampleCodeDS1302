#include  <msp430x14x.h>
#include  "12864.h"
#include  "DS1302.h"

/*ʱ�ӳ�ʼ��*/
void Clock_init()
{
   unsigned char t;
   BCSCTL1 = RSEL0 + RSEL1 + RSEL2;         // XT2on, max RSEL
   BCSCTL1&=~XT2OFF;                        //��XT2����
   do
   {
      IFG1 &= ~OFIFG;                       // �������ʧЧ��־
      for (t = 255; t > 0; t--);            // ��ʱ���ȴ�XT2����
   }
   while ((IFG1 & OFIFG) != 0);             // �ж�XT2�Ƿ�����
   
   BCSCTL2 |= SELS+SELM_2;                  // SMCLK = XT2
}

// д���ݣ���λ��ǰ����λ�ں�

void chuli_DS1302(unsigned char X,unsigned char Y,unsigned char show_time)
{
  unsigned char temp1=0,temp2=0;
  temp1=show_time/16+0x30;
  temp2=show_time%16+0x30; // Ҫ��ʾ�����ݵĸ�λ��ʮλ
  Display_number(X,Y,temp1);
  LCD_WDAT(temp2);   
}
/*������ʾ����*/
void day_show(unsigned char day)
{
  unsigned char temp_day;
  temp_day=day%16;
  switch(temp_day)
  {
     case 1: 
             Display(3,7,"һ");
             break;
             
     case 2: 
             Display(3,7,"��");
             break;
             
     case 3: 
             Display(3,7,"��");
             break;
             
     case 4: 
             Display(3,7,"��");
             break;
             
     case 5: 
             Display(3,7,"��");
             break;
             
     case 6: 
             Display(3,7,"��");
             break;
             
     case 7: 
             Display(3,7,"��");
             break;
     default:break;
             
  }
  
}
/*������ʾʱ��*/
void Time_DS1302()                 // ����ʱ�䲢��ʾ
{
    chuli_DS1302(1,1,time[6]);     //��
    chuli_DS1302(1,3,time[4]);     //��
    chuli_DS1302(1,5,time[3]);     //��
    chuli_DS1302(2,2,time[2]);     //ʱ
    chuli_DS1302(2,4,time[1]);     //��
    chuli_DS1302(2,6,time[0]);     //��
   // chuli_DS1302(3,7,time[5]);     //����  ����
    day_show(time[5]);          
                
}
void  main( void )
{

  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer to prevent time out reset
  Clock_init();                 // ʱ�ӳ�ʼ��

  LCD_init();                   //Һ����ʼ��
 
  P1DIR=0x01;                   // ʱ����� IO
  P2DIR=0x40;                   // ��λIO
   
  DS1302_init();                // ʱ�ӳ�ʼ��

  LCD_show();                   // Һ����ʼ����ʾ 
  
  while(1)
  {
     DS1302_readt();            // ��ʱ�Ӳ�����ʾ
     Time_DS1302();
   
  }
  
}

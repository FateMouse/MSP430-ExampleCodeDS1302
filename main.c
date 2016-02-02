#include  <msp430x14x.h>
#include  "12864.h"
#include  "DS1302.h"

/*时钟初始化*/
void Clock_init()
{
   unsigned char t;
   BCSCTL1 = RSEL0 + RSEL1 + RSEL2;         // XT2on, max RSEL
   BCSCTL1&=~XT2OFF;                        //打开XT2振荡器
   do
   {
      IFG1 &= ~OFIFG;                       // 清除振荡器失效标志
      for (t = 255; t > 0; t--);            // 延时，等待XT2起振
   }
   while ((IFG1 & OFIFG) != 0);             // 判断XT2是否起振
   
   BCSCTL2 |= SELS+SELM_2;                  // SMCLK = XT2
}

// 写数据，低位在前，高位在后

void chuli_DS1302(unsigned char X,unsigned char Y,unsigned char show_time)
{
  unsigned char temp1=0,temp2=0;
  temp1=show_time/16+0x30;
  temp2=show_time%16+0x30; // 要显示的数据的个位和十位
  Display_number(X,Y,temp1);
  LCD_WDAT(temp2);   
}
/*星期显示处理*/
void day_show(unsigned char day)
{
  unsigned char temp_day;
  temp_day=day%16;
  switch(temp_day)
  {
     case 1: 
             Display(3,7,"一");
             break;
             
     case 2: 
             Display(3,7,"二");
             break;
             
     case 3: 
             Display(3,7,"三");
             break;
             
     case 4: 
             Display(3,7,"四");
             break;
             
     case 5: 
             Display(3,7,"五");
             break;
             
     case 6: 
             Display(3,7,"六");
             break;
             
     case 7: 
             Display(3,7,"日");
             break;
     default:break;
             
  }
  
}
/*处理显示时间*/
void Time_DS1302()                 // 处理时间并显示
{
    chuli_DS1302(1,1,time[6]);     //年
    chuli_DS1302(1,3,time[4]);     //月
    chuli_DS1302(1,5,time[3]);     //日
    chuli_DS1302(2,2,time[2]);     //时
    chuli_DS1302(2,4,time[1]);     //分
    chuli_DS1302(2,6,time[0]);     //秒
   // chuli_DS1302(3,7,time[5]);     //星期  数字
    day_show(time[5]);          
                
}
void  main( void )
{

  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer to prevent time out reset
  Clock_init();                 // 时钟初始化

  LCD_init();                   //液晶初始化
 
  P1DIR=0x01;                   // 时钟输出 IO
  P2DIR=0x40;                   // 复位IO
   
  DS1302_init();                // 时钟初始化

  LCD_show();                   // 液晶初始化显示 
  
  while(1)
  {
     DS1302_readt();            // 读时钟并且显示
     Time_DS1302();
   
  }
  
}


#define  LCD_RS_High   P6OUT|=0x04   // LCD_RS  高电平   显示数据         P62
#define  LCD_RS_Low    P6OUT&=0xfb   // LCD_RS  低电平   指令数据   


 
#define  LCD_RW_High   P6OUT|=0x10   // LCD_RW  高电平   数据读到DB0_DB7   P64
#define  LCD_RW_Low    P6OUT&=0xef   // LCD_RW  低电平   DB0_DB7 数据写入IR DR


#define  LCD_EN_High   P6OUT|=0x08   // LCD_EN  高电平   高有效            P63
#define  LCD_EN_Low    P6OUT&=0xf7   // LCD_EN  低电平   使能信号

#define LCD_PSB_High   P3OUT|=0x01;  //  并口   高电平
#define LCD_PSB_Low    P3OUT&=0xfe;  //  串口   低电平    P30

//P67 悬空

void delay_ms(unsigned int timer)
{
  unsigned int i;
    for(i=0;i<1000;i--)
       for(;timer>0;timer--)
         ;
}


unsigned char lcd_busy()
 {                          
    unsigned char result;
    
     P4DIR=0x00;    
     LCD_RS_Low;          //  指令数据
     LCD_RW_High;
     LCD_EN_High;
        

     result = P4IN&0x80;   // 读取数据口数据
     LCD_EN_Low; 
     
     return(result); 
 }
/*写命令到液晶*/
void LCD_WCMD(unsigned char cmd)
{                          
  while(lcd_busy());

     P4DIR=0xff;          // OUT;
     LCD_RS_Low;          //  指令数据
     LCD_RW_Low;
     LCD_EN_High;
     P4OUT = cmd;
    

     LCD_EN_Low; 
}
/*写数据到液晶*/
void LCD_WDAT(unsigned char dat)
{                          
   while(lcd_busy());
   
     P4DIR=0xff;           // OUT;
     LCD_RS_High;          //  数据
     LCD_RW_Low;
     
     LCD_EN_High;
     P4OUT = dat;
     
    
     LCD_EN_Low; 
}
/*显示的字符串*/
void Display(unsigned char X,unsigned char Y,unsigned char *string)
{

   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}

     LCD_WCMD(X+Y);
   
   while(*string )
    {                         //显示字符
      LCD_WDAT(*string++);
    }

}
void Display_number(unsigned char X,unsigned char Y,unsigned char number)
{
    if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}

     LCD_WCMD(X+Y);
     LCD_WDAT(number);
}

/*液晶初始化*/
void LCD_init()
{
  
   P6DIR=0x1c;
   P3DIR=0x01;
   LCD_PSB_High;                 // 液晶显示  并口方式  
   LCD_WCMD(0x34);               //扩充指令操作
   LCD_WCMD(0x30);               //基本指令操作
   LCD_WCMD(0x0C);               //显示开，关光标
   LCD_WCMD(0x01);               //清除LCD的显示内容
      
}
void LCD_show()
{
  Display(0,3,"日历");   // 第一行显示： 日历
  Display(1,0,"20");     // 第二行显示：年月日
  Display(1,2,"年");
  Display(1,4,"月");
  Display(1,6,"日");
   
  Display(2,3,"时");    // 第三行显示：时分秒
  Display(2,5,"分");  
  Display(2,7,"秒");
  
  Display(3,5,"星期");  // 第四行显示：星期
}
  
  
  

#define  DS1302_SCLK_High   P1OUT|=0x01     // 时钟 高
#define  DS1302_SCLK_Low    P1OUT&=0xfe     // 低

#define  DS1302_RST_High    P2OUT|=0x40     //复位 高
#define  DS1302_RST_Low     P2OUT&=0xbf

#define  DS1302_DataIO_High P1OUT|=0x02    // 高电平
#define  DS1302_DataIO_Low  P1OUT&=0xfd    // Data  低电平   P11数据IO


unsigned char time[7]={0};   // 读出的时间值
unsigned char addr[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  // 读地址的命令

unsigned char Read_Ds1302(unsigned char command)            // 返回读出的数据
{
  unsigned char i,Data_temp=0;
         
  P1DIR|=0x02;              // 输出口，输出命令
  
  DS1302_RST_Low;
  DS1302_SCLK_Low;
  DS1302_RST_High;
  
  for(i=0;i<8;i++)
  { 
    DS1302_SCLK_Low;
    if(command&0x01)
        DS1302_DataIO_High;
    else
        DS1302_DataIO_Low;
    
     DS1302_SCLK_High;   // 高电平
     command>>=1;

  }
  
   P1DIR&=0xfd;          // 设置数据IO 为输入对应的数据 
   for(i=0;i<8;i++)
  {
    
     DS1302_SCLK_Low;
     if(P1IN&0x02)
        Data_temp|=0x01<<i;
      DS1302_SCLK_High;    // 高电平
     
  }
   DS1302_RST_Low;
   return Data_temp;
}

void Write_Ds1302(unsigned char command,unsigned char data)
{
  unsigned char i;

  
  P1DIR|=0x02;            // 输出口，输出命令
  
  DS1302_RST_Low;
  DS1302_SCLK_Low; 
  DS1302_RST_High;
  
  for(i=0;i<8;i++)
  {
     DS1302_SCLK_Low;
    if(command&0x01)
        DS1302_DataIO_High;
     else
        DS1302_DataIO_Low;
     
    
     DS1302_SCLK_High;   // 高电平 
     command>>=1;
  }
  for(i=0;i<8;i++)
  {
      if(data&0x01)
        DS1302_DataIO_High;
     else
        DS1302_DataIO_Low;
     
      DS1302_SCLK_Low;
      DS1302_SCLK_High;   // 高电平
      data>>=1;    
  }
   DS1302_RST_Low;
}
/*时钟赋初值*/
void DS1302_init()
{
   Write_Ds1302(0x8e,0x00);       // 允许写入
   
   Write_Ds1302(0x80,0x00);       //振荡启动，SEC 开始计时
   
   Write_Ds1302(0x82,0x59);       // Min   分
   Write_Ds1302(0x84,0x13);       //HR     时
   Write_Ds1302(0x86,0x13);       //Date   日
   Write_Ds1302(0x88,0x11);       //Mon   月
   Write_Ds1302(0x8A,0x07);       //Day   星期
   Write_Ds1302(0x8C,0x11);       //Year   年
   
   Write_Ds1302(0x8e,0x80);       // 禁止写入
}
void DS1302_readt() // 读取的时间值
{
  unsigned char i;
  
  for(i=0;i<7;i++)
  {
    time[i]=Read_Ds1302(addr[i]);
    delay_ms(1);
  }
  
}

#define  DS1302_SCLK_High   P1OUT|=0x01     // ʱ�� ��
#define  DS1302_SCLK_Low    P1OUT&=0xfe     // ��

#define  DS1302_RST_High    P2OUT|=0x40     //��λ ��
#define  DS1302_RST_Low     P2OUT&=0xbf

#define  DS1302_DataIO_High P1OUT|=0x02    // �ߵ�ƽ
#define  DS1302_DataIO_Low  P1OUT&=0xfd    // Data  �͵�ƽ   P11����IO


unsigned char time[7]={0};   // ������ʱ��ֵ
unsigned char addr[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};  // ����ַ������

unsigned char Read_Ds1302(unsigned char command)            // ���ض���������
{
  unsigned char i,Data_temp=0;
         
  P1DIR|=0x02;              // ����ڣ��������
  
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
    
     DS1302_SCLK_High;   // �ߵ�ƽ
     command>>=1;

  }
  
   P1DIR&=0xfd;          // ��������IO Ϊ�����Ӧ������ 
   for(i=0;i<8;i++)
  {
    
     DS1302_SCLK_Low;
     if(P1IN&0x02)
        Data_temp|=0x01<<i;
      DS1302_SCLK_High;    // �ߵ�ƽ
     
  }
   DS1302_RST_Low;
   return Data_temp;
}

void Write_Ds1302(unsigned char command,unsigned char data)
{
  unsigned char i;

  
  P1DIR|=0x02;            // ����ڣ��������
  
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
     
    
     DS1302_SCLK_High;   // �ߵ�ƽ 
     command>>=1;
  }
  for(i=0;i<8;i++)
  {
      if(data&0x01)
        DS1302_DataIO_High;
     else
        DS1302_DataIO_Low;
     
      DS1302_SCLK_Low;
      DS1302_SCLK_High;   // �ߵ�ƽ
      data>>=1;    
  }
   DS1302_RST_Low;
}
/*ʱ�Ӹ���ֵ*/
void DS1302_init()
{
   Write_Ds1302(0x8e,0x00);       // ����д��
   
   Write_Ds1302(0x80,0x00);       //��������SEC ��ʼ��ʱ
   
   Write_Ds1302(0x82,0x59);       // Min   ��
   Write_Ds1302(0x84,0x13);       //HR     ʱ
   Write_Ds1302(0x86,0x13);       //Date   ��
   Write_Ds1302(0x88,0x11);       //Mon   ��
   Write_Ds1302(0x8A,0x07);       //Day   ����
   Write_Ds1302(0x8C,0x11);       //Year   ��
   
   Write_Ds1302(0x8e,0x80);       // ��ֹд��
}
void DS1302_readt() // ��ȡ��ʱ��ֵ
{
  unsigned char i;
  
  for(i=0;i<7;i++)
  {
    time[i]=Read_Ds1302(addr[i]);
    delay_ms(1);
  }
  
}

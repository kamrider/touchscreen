#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  

#include "w25qxx.h"
#include "touch.h"
#include "GBK_LibDrive.h"	
 
 
/************************************************************************/

//������ʵ��   --�⺯���汾
//STM32F4����-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com
 
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************/



//�����Ļ�������Ͻ���ʾ"RST"
void Load_Drow_Dialog(void)
{
	GBK_LibFont_Test();//�ֿ���ʾ����
//	LCD_Clear(WHITE);	//����   
 	POINT_COLOR=RED;	//��������Ϊ��ɫ 
	LCD_ShowString(lcddev.width-24,0,200,16,16,RED,"RST");//��ʾ��������
  POINT_COLOR=RED;	//���û�����ɫ 
	
}



/************************************************************************/

//���败�������Ժ���
 
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************/


void rtp_test(void)
{
	u8 key;
	u8 i=0;	  
	while(1)
	{
		
	 	key=KEY_Scan(0);
		
		tp_dev.scan(0); 	
		
		if(tp_dev.sta&TP_PRES_DOWN)			//������������
		{	
		 	if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
			{	
				if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)
					Load_Drow_Dialog();//���
				else 
					TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],RED);		//��ͼ	  			   
			}
		}
		else delay_ms(10);	//û�а������µ�ʱ�� 	  
		
		if(key==KEY0_PRES)	//KEY0����,��ִ��У׼����
		{
			LCD_Clear(WHITE);  //����
		  TP_Adjust();  	   //��ĻУ׼  
			Load_Drow_Dialog();
		}
		
		i++;
		if(i%20==0)
		{
		  LED1=!LED1;//LED������ָʾϵͳ������
		}
		
	}
}




/************************************************************************/

//���败��������
 
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************/

	
int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ�� 
	KEY_Init(); 				//������ʼ��  
	
	
	W25QXX_Init();			//W25QXX��ʼ��
	
  POINT_COLOR=RED; 
	
	while(W25QXX_ReadID()!=W25Q16)								//��ⲻ��W25QXX
	{
		LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,150,200,16,16,RED,"Please Check!      ");
		delay_ms(500);
		LED1=!LED1;		//DS0��˸
	}
	LCD_ShowString(30,150,200,16,16,RED,"W25Q16 Ready!"); 
	
	GBK_Lib_Init();       //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ���� 
	
	tp_dev.init();				//��������ʼ��
 	
	LCD_Clear(WHITE);//�����Ļ
	
	LCD_ShowString(16,20,200,16,16,RED,"mcudev STM32F4");	
	LCD_ShowString(16,40,200,16,16,RED,"TOUCH TEST");	
	LCD_ShowString(16,60,200,16,16,RED,"mcudev.taobao.com");
	LCD_ShowString(16,80,200,16,16,RED,"2019/1/15");
   
//	LCD_ShowString(30,100,200,16,16,RED,"Press KEY0 to Adjust");
	
  //ʹ�����ֿ���Ļ�����Խ���������ʾ
		
	GBK_Show_Str(16,120,240,32,"�ֿ����-32",32,BLUE,WHITE,0);	
	GBK_Show_Str(16,160,240,24,"2.8/3.2��Һ����-24",24,BLUE,WHITE,0);	
	GBK_Show_Str(16,190,240,16,"��ƣ���Խ����-16",16,BLUE,WHITE,0);	
	GBK_Show_Str(16,210,240,12,"From: mcudev.taobao.com-12",12,BLUE,WHITE,0);	
  
	LCD_ShowString(16,230,240,16,16,RED,"Press KEY0 to Adjust");//����������ʾ
	
	delay_ms(1500);
 	Load_Drow_Dialog();	 	
	
	rtp_test(); 					//����������
	
	
}




















/************************************************************************/

//���败��������
 
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************/


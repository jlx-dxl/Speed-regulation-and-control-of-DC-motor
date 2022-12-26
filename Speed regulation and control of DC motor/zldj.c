#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit IN1=P1^6;
sbit IN2=P1^7;
sbit ENA=P1^5;
sbit KEY0=P2^0;
sbit KEY1=P2^1;
sbit KEY2=P2^2;
sbit KEY3=P2^3;
sbit KEY4=P2^4;
sbit R=P2^5;
sbit Y=P2^6;
sbit G=P2^7;
sbit LED1=P1^0;
sbit LED2=P1^1;
sbit LED3=P1^2;
sbit LED4=P1^3;
sbit led=P1^4;

bit flag=0;
bit sign=1;
uint num=0;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};



void delay(uint n)
{
	 uint i,j;
	for(i=n;i>0;i--)
	for(j=0;j<110;j++);
}


void initial()
{
	IN1=0;
	IN2=0;
	ENA=0;
	num=0;
	TMOD=0X01;
	TL0=0XFF;
	TH0=0XFF;
	EA=1;
	EX0=1;
	ET0=1;
	IT0=1;
	TR0=1;
}



void display(bit flag,uint n)
{
	uint v;
	uchar qian,bai,shi,ge;
	v=(uint)(n*535.0/255);
	qian=v/1000;
	bai=(v-1000*qian)/100;
	shi=v%100/10;
	ge=v%10;
	
	LED1=0;
	if(flag==1)
		P0=table[0];
	else
		P0=0X40;
	delay(10);
	LED1=1;
	
	LED2=0;
	P0=table[bai];
	delay(10);
	LED2=1;
	
	LED3=0;
	P0=table[shi];
	delay(10);
	LED3=1;
	
	LED4=0;
	P0=table[ge];
	delay(10);
	LED4=1;
}


void main()
{
	initial();
	while(1)
	{
		display(sign,num);
	}
}

void int0() interrupt 0
{
	if(KEY0==0)
	{
		delay(10);
		if(KEY0==0)
		{
			flag=~flag;
			if(flag==0)
			{
				num=0;
				P2=0xff;
				ENA=0;
				IN1=0;
				IN2=0;
				G=0;
				sign=1;
			}
			else
			{
				P2=0xff;
				num=100;
				IN1=0;
				IN2=1;
				R=0;
				sign=1;
			}
			while(!KEY0);
		}
	}
	if(KEY1==0)
	{
		delay(10);
		if(KEY1==0)
		{
			P2=0XFF;
			//ENA=1;
			IN1=0;
			IN2=1;
			R=0;
			sign=1;			
		}
		while(!KEY1);
	}
		if(KEY2==0)
	{
		delay(10);
		if(KEY2==0)
		{
			P2=0XFF;
			//ENA=1;
			IN1=1;
			IN2=0;
			Y=0;
			sign=0;			
		}
		while(!KEY2);
	}
		if(KEY3==0)
	{
		delay(10);
		if(KEY3==0)
		{
			num+=5;
      if(num>=255)
         num=255;				
		}
		while(!KEY3);
	}
			if(KEY4==0)
	{
		delay(10);
		if(KEY4==0)
		{
			num-=5;
      if(num<=0)
         num=0;				
		}
		while(!KEY4);
	}
}



void itt0()interrupt 1
{
	ENA=~ENA;
	TL0=0XFF;
	led=~led;
	if(ENA==1)
		TH0=255-num;
	else
		TH0=num;
}
 



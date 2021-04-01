#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdlib.h>
#include <time.h>
unsigned char data[2];
unsigned char ma7doan[10]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
unsigned char kitu[2]={0xC9,0xB6};
#define BT1 11
int r;
time_t t;

int xuat_data(unsigned char address,unsigned char value )
{
	data[0]=address;
	data[1]=value;
	wiringPiSPIDataRW(0,data,2);
}
int init(void)
{
	//set che do hoat dong cho max 7219
	// display on-off
	xuat_data(0x0F,0);
	//decode mode--> BCD cho 8 chu so
	xuat_data(0x09,0);
	//intensity -> 90%
	xuat_data(0x0A,0x00);
	//scan limit 8 chu so
	xuat_data(0x0B,07);
	//shutdown --> no 
	xuat_data(0x0C,1);
	return 0;
}

void xo_so()
{
	if(digitalRead(BT1)==1)
	{
	// Khoi tao bo sinh so ngau nhien 
	srand((unsigned) time(&t));
	// random 3 so
	srand(time(NULL));
	for(int i=0;i<6;i++)
	{
	r = 0+ rand() % (9+1-0);
	xuat_data(i+2,ma7doan[r]);
	}
	}
}

int main()
{	

	wiringPiSetupPhys();
	pinMode(BT1,INPUT);
	wiringPiSPISetup(0,5000000);
	init();
	wiringPiISR(BT1,INT_EDGE_BOTH,&xo_so);

	xuat_data(0x01,kitu[0]);
	xuat_data(0x08,kitu[1]);

	xo_so();

	return 0;
}
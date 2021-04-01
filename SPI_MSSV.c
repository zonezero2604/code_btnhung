#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
unsigned char data[2];
unsigned char address[8]={1,2,3,4,5,6,7,8};
unsigned char value[8]={5,4,1,6,4,1,8,1};
int xuat_data(unsigned char address1,unsigned char value1 )
{
	data[0]=address1;// data[0] 8 bit
 	data[1]=value1;
	wiringPiSPIDataRW(0,data,2);
}
int init(void)
{
	//thiet lap giao tiep SPI
	wiringPiSPISetup(0,5000000);
	//set che do hoat dong cho max 7219
	// display test on-off
	xuat_data(0x0F,0);
	//decode mode--> BCD cho 8 chu so
	xuat_data(0x09,0xFF);
	//intensity -> 90%
	xuat_data(0x0A,0x0E);
	//scan limit 8 chu so
	xuat_data(0x0B,0x07);
	//shutdown --> no 
	xuat_data(0x0C,1);
	return 0;
}
int main()
{
	init();
	

	for(int i=0;i<8;i++)
	{
		xuat_data(address[i],value[i]);
	}

	return 0;
}

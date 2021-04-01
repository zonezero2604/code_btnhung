#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
unsigned char data[2];
unsigned char address[8]={1,2,3,4,5,6,7,8};
int n;
int xuat_data(unsigned char address1,unsigned char value1 )
{
	data[0]=address1;
	data[1]=value1;
	wiringPiSPIDataRW(0,data,2);
}
int init(void)
{
	//set che do hoat dong cho max 7219
	// display on-off
	xuat_data(0x0F,0);
	//decode mode--> BCD cho 8 chu so
	xuat_data(0x09,0xFF);
	//intensity -> 90%
	xuat_data(0x0A,0x06);
	//shutdown --> no 
	xuat_data(0x0C,1);
	return 0;
}
void hien_thi(int num)
{	
	if(num == 0) 
	{	
		xuat_data(0x0B,0);//???????? 0x0B,0x02
		xuat_data(1,0);// ??????????????? test cho tắt hết ???
		delay(500);
		return; /// để làm j ???
	}
	
	int count=0;
	n = num;
	
	// dem so 
	while(n!=0)
	{	
		n=n/10; // 1/10 = 0
		count++;
	}
	
	//scan limit 8 chu so
	if (count > 0) 
	{
		xuat_data(0x0B,count-1);
	}
	
	for(int i=0;i<count;i++)
	{
		xuat_data(i+1,num%10);// lấy số hàng đơn vị của num
		num/=10; // xóa số hàng đơn vị
		
	}
	
}
int main()
{	
	//thiet lap giao tiep SPI
	wiringPiSPISetup(0,5000000);
	init();
	for (int i = 0; i < 10000; i++) 
	{
		hien_thi(i);
		delay(500);
	}
	
	
}



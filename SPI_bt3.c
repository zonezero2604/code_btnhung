#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
unsigned char data[2];
unsigned char ma7doan[10]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B};
int thoigian[6];
int i;
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
	xuat_data(0x0A,0x06);
	//scan limit 8 chu so
	xuat_data(0x0B,07);
	//shutdown --> no 
	xuat_data(0x0C,1);
	return 0;
}
void hien_thi()
{
	for(int gio=thoigian[0]*10+thoigian[1];gio<24;gio++)
	{
		xuat_data(0x08,ma7doan[gio/10]);
		xuat_data(0x07,ma7doan[gio%10]);
		for(int phut=thoigian[2]*10+thoigian[3];phut<60;phut++)
		{
			xuat_data(0x05,ma7doan[phut/10]);
			xuat_data(0x04,ma7doan[phut%10]);
			for(int giay=thoigian[4]*10+thoigian[5];giay<60;giay++)
			{
				xuat_data(0x02,ma7doan[giay/10]);
				xuat_data(0x01,ma7doan[giay%10]);
				delay(100);
			}
		}
	}
}
void set_start_time()
{
	printf("Vui long nhap thoi gian bat dau:\n"); 
	for(i=0;i<6;i++)
	{
		scanf("%d",&thoigian[i]);
		//Hàm scanf() được sử dụng cho đầu vào. Nó đọc dữ liệu đầu vào từ bàn điều khiển.
		//scanf("format string", argument_list);đọc số nguyên từ console và lưu trữ giá trị đã cho trong biến thoi gian 
	}
}

int main()
{	
	
	wiringPiSPISetup(0,5000000);
	set_start_time();
	init();
	xuat_data(0x06,0x01);///?
	xuat_data(0x03,0x01);//?
	hien_thi();
	return 0;
}


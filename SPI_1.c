//# include <wiringPiSPI.h>
//khởi tạo spi- wiringPiSPISetup(bộ spi0/1, tốc độ tối đa thiết bị ngoại vi cho phép kết nối)
//wiringPiSPIDataRW(chanel, dạng biến gửi đi (con trỏ,MẢNG),
 //độ dài data gửi đi tính theo byte)

#inclue <stdio.h> // thường có
#inclue <wiringPi.h>
#include <wiringPiSPI.h>
int main(void)
{
	//tạo 1 biến 100 phần tử
	unsigned char buffer[100];
	wiringPiSPISetup(1, 500000);
	// data gửi buffer 0-1-2-3...
	//gửi 1 1 byte thì phải gán giá trị cho buffer 0
	buffer[0] = 0x76;
	wiringPiSPIDataRW(1,buffer,1);

	return 0;
}
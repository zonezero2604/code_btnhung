#inclue <stdio.h> // thường có
#inclue <wiringPi.h>
#include <wiringPiSPI.h>

unsigned char data[2]; //mỗi lần gửi 16 bit - biến global
uint16_t D;// khai báo biến D 16 bit - cấp chính xác vùng nhớ là 16 bit

int main(void)
{
	//khởi tạo spi
	wiringPiSPISetup(spi_chanel, 10000000); // gửi đi vs clk 10tr bit/s
	// set chế độ hoạt động cho mcp4921 - ban đầu 0 có điện áp
	//set chế độ hoạt động cho mcp 4921 muốn lúc đầu là data[0]=0011 0000 data[1]=00000000	
	data[0]=0x30;
	data[1]=0;
	wiringPiSPIDataRW(spi_chanel,data,2);

	//tiếp theo liên tục gửi giá trị cho ic
	while(true)
	{
		for(int i=0;i<100;i++)
		{
			//tính giá trị D theo i D=deltaD*i
			// gán giá trị D cho data 0 và data 1
			//lưu ý D 12 bit dato0 8 bit data 1 8 bit 
			D = 2949/100*i //16bit
			data[0] = (D>>8)|0x30; // loại bỏ 8 bit mức thấp giữ lại 8 bit mức cao và | 0x30
			data[1] = D;// khi gán 1 giá trị 16 bit xuống giá trị 8 bit thì 8 bit này chỉ lấy 8bit thấp
			wiringPiSPIDataRW(spi_chanel,data,2);
			delay(1);
		}
	}
	return 0;
}
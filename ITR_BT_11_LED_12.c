#inclue <stdio.h> // thường có
#inclue <wiringPi.h>

#define Led 12
#define BT 11

void xuly_ngat()
{
	if(digitalRead(BT)==1)
		digitalWrite(Led,HIGH);
	else
		digitalRead(Led,LOW);

}
int main()
{
	// set up thư viện wiringPi
	wiringPiSetupPhys();

	//Khai Báo IO
	pinMode(Led, OUTPUT);
	pinMode(BT, INPUT);

	//interrupt
	wiriPiISR(BT,INT_EDGE_BOTH, &xuly_ngat );

	// đọc trạng thái nút nhấn bằng interrupts ko dùng if

	//dùng if thì CPU luôn chạy code này thì lag tiêu tốn tài nguyên
	// while(i)
	// {
	// 	if(digitalRead(BT)==1)
	// 		digitalWrite(Led,HIGH);
	// 	else
	// 		digitalRead(Led,LOW);
	// }
	// khi thêm 1 nút nhấn nữa thì lag => muốn xảy ra mượt=> ngắt

	//Để CPU BIẾT ĐƯỢC NGẮT XẢY RA CẦN 2 BƯỚC -
		//b1 mở sự kiện ngắt wiriPiISR(chân ngắt,int edgeType, &hàm xử lý ngắt )
			//int edgeType: int_edge_falling:(ngắt cạnh xuống-tín hiệu đầu vào từ 1 xuống 0) 
						//int_edge_both Cả 2 trường hợp 1-0,0-1 thả nút, nhấn nút

		//b2 viết hàm xử lý ngắt 
}
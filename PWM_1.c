// Thay đổi thời gian T duty cycle (thời gian ở mức 1)
// ras-pi 2 pp tạo xung PWM
	//c1: dùng module ngoại vi phần cứng tích hợp sẵn 
		//pwm0-12,32; pwm1-33,35: tại 1 thời điểm chỉ có 1 trong 2 chân thuộc 1 module hoạt động
		// hoạt động dựa trên clk bên ngoài cấp 19.2MHz
		// 2 mode Balance và Mark:space
			//Balance : chỉnh đc duty cycle ko chỉnh đc chu kỳ pwm (cu kỳ luôn 1024)-duty đi từ 0 -1024
				//vd khi set duty cycle thì nó tự chỉnh chu kỳ và tự co giãn để đạt 50%
			//Mark space có thể chỉnh chu kỳ của pwm bằng cách chỉnh 2 hệ số divisor(hệ số
				//bộ chia) và hệ số range(maximum của duty cycle)
	//http://wiringpi.com/reference/raspberry-pi-specifics/
	//pwmSetMode (int mode) ; -PWM_MODE_BAL or PWM_MODE_MS.
	// pwmSetRange (unsigned int range) ;
	// This sets the range register in the PWM generator. The default is 1024.
	// pwmSetClock (int divisor) ;
	// This sets the divisor for the PWM clock.
	//vd đk động cơ dc 10khz set divisor = 15 , range = 128 (19,2*10^6/(15*128)=10k)

// cd đk 1 đèn led chân 12
#inclue <stdio.h> // thường có
#inclue <wiringPi.h>
#define pwm0 12              //bc1
int main()
{
	// set up thư viện wiringPi
	wiringPiSetupPhys();
	//Khai Báo IO
	pinMode(pwm0, PWM_OUTPUT); //bc2 mặc định là chế độ balace - ko đk đc chuky
	// led sáng 50%
	pwmWrite(pwm0, 512); //(1024*50/100=512)

	//set chế độ hoạt động cho pwm0
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock (15); // chọn giá trị bộ chia
	pwmSetRange (128) ; // (19.2*10^6/(15*128)=10k) 100%duty là 128 (ráng cho range lớn để tạo độ mịn)
	//xuat xung 50%
	pwmWrite(pwm0, 64); // 128/2 = 64 

	return 0;
}
// chạy 1 vòng chương trình , chương trình ngừng nhưng chân 12 vẫn tạo ra xung pwm
	
	
	//c2: dùng phần mềm thư viện  viết sẵn, tạo ra ở mọi chân - cần duy tri cho chương trình hđ
	// tần số pwm chỉ có 100hz  => duty cycle từ 0-100 (100-10ms)
	// còn cso thư viện <softPwm.h>
#inclue <stdio.h> // thường có
#inclue <wiringPi.h>
#inclue <softPwm.h> //có phân luồng => lúc biên dịch cần thêm -lwiringPi -lpthread
#define s_pwm 12
int main()
{
	// set up thư viện wiringPi
	wiringPiSetupPhys();
	//Khai Báo IO
	//softPwmCreate(chân nào,giá trị khởi tạo duty cycle ban đầu 0-100
	//	 ,tần số xung pwm(max của duty cycle)-nên để 100 ); 
	softPwmCreate(s_pwm,30,100 );
	softPwm(s_pwm,70);
	while(1)
	{
		softPwm(s_pwm,70); // nếu ko đổi thì bỏ ở ngoài cx đc
	}
	return 0;
}
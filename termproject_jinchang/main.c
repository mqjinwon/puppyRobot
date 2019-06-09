/*
 * GccApplication1.c
 *
 * Created: 2019-04-21 오후 9:08:05
 * Author : gongdol2
 */ 

#include "mcu_init.h"

//////////////////////////////////////////////////////////////////////
///////////////////////////////변수 설정//////////////////////////////
//////////////////////////////////////////////////////////////////////

int g_cnt = 0; // adc 천천히 받게하려고 한 변수
int g_ADC[8] = {0,}; //adc 전역변수
double u_end = 0;
double u_distance = 0;

unsigned char recvData = 0;

ISR(INT2_vect){
	if ((EICRA & 0b00110000) == 0b00100000)//falling //TCNT1당 0.064ms 34 cm/ms
	{
		u_end=TCNT2;
		u_distance= u_end* 1.088;
		EICRA = (EICRA &0b11001111)| 0b00110000;//라이징으로 바꿈
	}

	else//rising일때
	{
		TCNT2 = 0;
		EICRA =(EICRA &0b11001111)| 0b00100000;//폴링으로 바꿈
	}
}


//제어주기 : 20ms
ISR(TIMER3_OVF_vect){
	
	TCNT3 = 64285; // Bottom 설정
	

	if(recvData == 'a')
	{
		PORTA = ~PORTA;
	}

	TransUart0('S');
	TransNumUart0(GetResistor()); TransUart0(',');
	TransNumUart0(GetCDS()); TransUart0(',');
	TransNumUart0(GetLM35()); TransUart0(',');
	TransNumUart0(GetTHEMISTER()); TransUart0(',');
	TransNumUart0(GetGAS()); TransUart0(',');
	TransNumUart0(GetPOWER()); TransUart0(',');
	TransNumUart0(GetPSD()); TransUart0(',');
	TransNumUart0(GetWATER()); TransUart0(',');
	Trigger();
	TransNumUart0((int)u_distance); TransUart0(',');
	TransUart0('E');


	//모터제어
	OCR1A = 500;
	OCR1B = 500;

	recvData = 0; // 받은 데이터 초기화
}


int main(void)
{
    /* Replace with your application code */
	InitIO();
	InitExtInt();
	InitTimer1(); // 모터제어
	InitTimer2(); // 초음파 시간 재는거
	InitTimer3(); // 제어주기
	InitADC();
	InitUart0();
	InitUart1();
	
	sei();
	
    while (1) 
    {				
		recvData = RecvUart0();
    }

	return 0;
}

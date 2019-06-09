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

ISR()

ISR(INT0_vect){
	
	PORTA = 0x00;
}


ISR(INT1_vect){

	PORTA = 0xFF;	
}

ISR(INT2_vect){
	if ((EICRA & 0b00110000) == 0b00100000)//falling //TCNT1당 0.064ms 34 cm/ms
	{
		u_end=TCNT2;
		u_distance= u_end* 2.176;
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
	g_cnt++;

	//0.5초에 한번씩 실행
	if(g_cnt>25)
	{

		TransNumUart0(GetResistor()); TransUart1(','); TransUart1(' ');		
		TransNumUart1(GetCDS()); TransUart1(','); TransUart1(' ');
		TransNumUart1(GetLM35()); TransUart1(','); TransUart1(' ');
		TransNumUart1(GetTHEMISTER()); TransUart1(','); TransUart1(' ');
		TransNumUart1(GetGAS()); TransUart1(','); TransUart1(' ');
		TransNumUart1(GetPOWER()); TransUart1(','); TransUart1(' ');
		 
		TransUart0('\n');         
		TransUart0('\r');

		g_cnt = 0;
	}
	//Trigger();
	
	//TransNumUart1(u_distance);
	//TransUart1(',');
	//TransNumUart1(u_end);

	//TransUart1(13);

	//모터제어
	OCR1A = 799;
	OCR1B = 799;
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

	//PD 2(echo)
	//PC 0(trigger)
	
    while (1) 
    {			
    }

	return 0;
}

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





ISR(INT0_vect){
	
	PORTA = 0x00;
}


ISR(INT1_vect){

	PORTA = 0xFF;	
}

//제어주기 : 20ms
ISR(TIMER3_OVF_vect){
	
	TCNT3 = 64285; // Bottom 설정
	
	g_cnt++;

	//0.5초에 한번씩 실행
	if(g_cnt>25)
	{

		//TransNumUart1(GetResistor()); TransUart1(','); TransUart1(' ');		
		//TransNumUart1(GetCDS()); TransUart1(','); TransUart1(' ');
		//TransNumUart1(GetLM35()); TransUart1(','); TransUart1(' ');
		//TransNumUart1(GetTHEMISTER()); TransUart1(','); TransUart1(' ');
		TransNumUart1(GetGAS()); TransUart1(','); TransUart1(' ');
		//TransNumUart1(GetPOWER()); TransUart1(','); TransUart1(' ');
		 
		TransUart1('\n');         
		TransUart1('\r');

		/*
		//uart0번도 사용가능!

		adc = GetADC(ADC_MUX_RESISTOR);
		TransNumUart0(adc); TransUart1(','); TransUart0(' ');
				
		adc = GetADC(ADC_MUX_CDS);
		TransNumUart0(adc); TransUart0(','); TransUart0(' ');
				
		adc = GetADC(ADC_MUX_LM35);
		TransNumUart0(adc);	TransUart0(','); TransUart0(' ');

		adc = GetADC(ADC_MUX_THERMISTER);
		TransNumUart0(adc);
				
		TransUart0('\n');
		TransUart0('\r');

		adc = GetADC(ADC_MUX_RESISTOR);
		TransNumUart1(adc); TransUart1(','); TransUart1(' ');
		
		adc = GetADC(ADC_MUX_CDS);
		TransNumUart1(adc); TransUart1(','); TransUart1(' ');
		
		adc = GetADC(ADC_MUX_LM35);
		TransNumUart1(adc);	TransUart1(','); TransUart1(' ');

		adc = GetADC(ADC_MUX_THERMISTER);
		TransNumUart1(adc);
		
		TransUart1('\n');
		TransUart1('\r');
		*/

		g_cnt = 0;
	}


	//모터제어
	OCR1A = 0;
	OCR1B = 0;
}





int main(void)
{
    /* Replace with your application code */
	InitIO();
	InitExtInt();
	InitTimer1(); // 모터제어
	InitTimer3(); // 제어주기
	InitADC();
	InitUart0();
	InitUart1();
	
	sei();
	
    while (1) 
    {		
    }
}


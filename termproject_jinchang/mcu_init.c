/*
* MCU_Init.c
*
* Created: 2019-04-20 오후 3:10:08
* Author: Administrator
*/

#include "mcu_init.h"


//////////////////////////////////////////////////////////////////
//InitIO()
//Initialize Input & Output of Port
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitIO(){

	DDRA = 0xff; //LED
	DDRC = 0xff; //원하는거 넣으면 될듯  //PC0(trigger)
	DDRB = 0x60; // 모터 활성화(OCR1A, OCR1B)
	DDRD = 0x00; //interrupt //PD2(echo)

	PORTC = 0x00; // 0번은 초음파 트리거, 4~7번은 모터 방향
	PORTC = PORTC | 0x50;
	PORTA = 0xff;
}



//////////////////////////////////////////////////////////////////
//InitExtInt()
//Initialize External Interrupt
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitExtInt(){

	cbi(PORTD, 0);
	cbi(PORTD, 1);

	EICRA = INT1_FALLING | INT0_FALLING | INT2_RISING;
	
	EIMSK = INT1_ENABLE | INT0_ENABLE | INT2_ENABLE;
}



//////////////////////////////////////////////////////////////////
//InitTimer0()
//Initialize Timer0
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitTimer0(){
	
	//TO DO
}



//////////////////////////////////////////////////////////////////
//InitTimer1()
//Initialize Timer1
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitTimer1(){

	//1번핀 모터제어로 사용
	TCCR1A = (1<<COM1A1)|(0<<COM1A0)|(1<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(0<<WGM10); // A,B Channel Clear(Compare Match) & Set(OVerflow) ,fast PWM모트
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10); // fast PWM모드 설정

	ICR1 = 800; // TOP값
	OCR1A = 0; // 왼쪽 모터
	OCR1B = 0; // 오른쪽 모터
}



//////////////////////////////////////////////////////////////////
//InitTimer2()
//Initialize Timer2
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitTimer2(){
	
	//normal mode, OC2 disconnected, 1024 prescaler
	TCCR2 = TIMER2_WGM_NORMAL | TIMER2_CS_PRESCALER_1024;
	TCNT2 = 256-156; // 0.01초

	//using timer2 overflow_interrupt
	//TIMSK =  (1<<TOIE2);
}



//////////////////////////////////////////////////////////////////
//InitTimer3()
//Initialize Timer3
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitTimer3(){
	
   //3번핀 제어주기로 사용
   TCCR3A = (0<<WGM31)|(0<<WGM30);  // Normal Mode, prescale 256
   TCCR3B = (0<<WGM33)|(0<<WGM32)|(1<<CS32)|(0<<CS31)|(0<<CS30); // 분주비 256
   ETIMSK = (1<<TOIE3);  // 3번 Overflow Interrupt Enable
   TCNT3 = 64285;
}



//////////////////////////////////////////////////////////////////
//InitADC()
//InitADC
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitADC(){
	
	ADMUX = ADC_REF_SELECTION_AVCC | ADC_ADJUST_RIGHT; //
	ADCSRA = ADC_ENABLE | ADC_PRESCALER_128;
	}



//////////////////////////////////////////////////////////////////
//GetADC()
//GetADC
// Input : adc chanel
// Output : ADC Result
//////////////////////////////////////////////////////////////////
int GetADC(char ch){

	ADMUX = ADC_REF_SELECTION_AVCC | ADC_ADJUST_RIGHT | ch;
	ADCSRA |= ADC_CONVERTION_START; // 변환 완료된 것을 알려주는 플래그
	while(!(ADCSRA & (1<<ADIF)));
	
	return ADC;
}



//////////////////////////////////////////////////////////////////
//InitUart0()
//InitUart0
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitUart0(){

	//TO DO
	sbi(PORTE, 1);
	cbi(PORTE, 0);
	
	UCSR0A = 0x00;
	UCSR0B = USART_RECV_ENABLE | USART_TRANS_ENABLE;
	UCSR0C = USART_CHAR_SIZE_8BIT;
	
	UBRR0L = USART_115200BPS;
}



//////////////////////////////////////////////////////////////////
//InitUart1()
//InitUart1
// Input : None
// Output : None
//////////////////////////////////////////////////////////////////
void InitUart1(){
	
	//TO DO
	DDRD = (DDRD & 0xF3) | 0x08;
	
	UCSR1A = 0x00;
	UCSR1B = USART_RECV_ENABLE | USART_TRANS_ENABLE;
	UCSR1C = USART_CHAR_SIZE_8BIT;
	
	UBRR1L = USART_115200BPS;
}



//////////////////////////////////////////////////////////////////
//TransUart0()
//TransUart0
// Input : Transmit data
// Output : None
//////////////////////////////////////////////////////////////////
void TransUart0(unsigned char data){
	
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data; // 보내는 UDR1
}



//////////////////////////////////////////////////////////////////
//TransUart1()
//TransUart1
// Input : Transmit data
// Output : None
//////////////////////////////////////////////////////////////////
void TransUart1(unsigned char data){
	
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data; // 보내는 UDR1
}



//////////////////////////////////////////////////////////////////
//RecvUart0()
//RecvUart0
// Input : None
// Output : Recved Data
//////////////////////////////////////////////////////////////////
unsigned char RecvUart0(){
	
	while(!(UCSR0A&(1<<RXC0)));
	
	return UDR0;
}



//////////////////////////////////////////////////////////////////
//RecvUart1()
//RecvUart1
// Input : None
// Output : Recved Data
//////////////////////////////////////////////////////////////////
unsigned char RecvUart1(){

	while(!(UCSR1A&(1<<RXC1)));

	return UDR1;
}



//////////////////////////////////////////////////////////////////
//TransNumUart0()
//TransNumUart0
// Input : Number data
// Output : None
//////////////////////////////////////////////////////////////////
void TransNumUart0(int num){
	
	//TO DO
	TransUart0(num/1000 + 48);
	TransUart0((num/100)%100 + 48);
	TransUart0((num/10)%10 + 48);
	TransUart0(num%10 + 48);
}



//////////////////////////////////////////////////////////////////
//TransNumUart1()
//TransNumUart1
// Input : Number data
// Output : None
//////////////////////////////////////////////////////////////////
void TransNumUart1(int num){
	
	//TO DO
	TransUart1(num/1000 + 48);
	TransUart1((num/100)%100 + 48);
	TransUart1((num/10)%10 + 48);
	TransUart1(num%10 + 48);
}



//////////////////////////////////////////////////////////////////
//GetResistor()
//GetResistor
// Input : 
// Output : 0~100 resistor
//////////////////////////////////////////////////////////////////
int GetResistor(){
	int adc = GetADC(ADC_MUX_RESISTOR);
	return adc / 1023. * 100.;
}



//////////////////////////////////////////////////////////////////
//GetCDS()
//GetCDS
// Input : 
// Output : LUX
//////////////////////////////////////////////////////////////////
int GetCDS(){
	int adc = GetADC(ADC_MUX_CDS);
	float vout = 5. * (1./1023) * adc;
	float R_cds = ((4.7 * 5.) / vout) - 4.7;
	float lux = powf(10., 1. - ( (log10(R_cds)-log10(40.)) / 0.8));   //수식을 그대로 쳐서 넣은건데 살짝씩 어플과 값이 맞게 변형 + 단위는 K + 회로, 환경에 따라 값이 많이 달라질수 있다.

	return lux;
}



//////////////////////////////////////////////////////////////////
//GetLM35()
//GetLM35
// Input : 
// Output : temperature
//////////////////////////////////////////////////////////////////
int GetLM35(){
	int adc = GetADC(ADC_MUX_LM35);
	return 5 * ((double)1./1023) * adc * 100;  
}



//////////////////////////////////////////////////////////////////
//GetTHEMISTER()
//GetTHEMISTER
// Input : 
// Output : temperature
//////////////////////////////////////////////////////////////////
int GetTHEMISTER(){
	int adc = GetADC(ADC_MUX_THERMISTER);
	float vout = 5 * ((double)1/1023) * adc;
	float Rth = (5./vout)*4700 - 4700;
	float T = 1 / (1. / (273.15 + 25.) + 1./3650 * log(Rth/1000.) );
	float Tth = T - 273.5 ;   //+a
	return Tth;
}



//////////////////////////////////////////////////////////////////
//GetGAS()
//GetGAS
// Input :
// Output : GAS
//////////////////////////////////////////////////////////////////
int GetGAS(){
	int adc = GetADC(ADC_MUX_GAS);
	return adc;
}



//////////////////////////////////////////////////////////////////
//GetPOWER()
//GetPOWER
// Input :
// Output : pressure
// feature : 800g까지 측정할 수 있다!(오차 +- 50)
//////////////////////////////////////////////////////////////////
int GetPOWER(){
	int adc = GetADC(ADC_MUX_POWER);
	float vout = 5 * ((double)1/1023) * adc;
	float power = powf(4.23, vout);
	if(power >= 10000)
		power = 9999;
	return power;
}
//////////////////////////////////////////////////////////////////
//CalTHEMISTER()
//CalTHEMISTER
// Input :
// Output : temperature
//////////////////////////////////////////////////////////////////

int GetPSD(){
	int adc  = GetADC(ADC_MUX_PSD);
	float vout = 5 * ((double)1/1023) * adc;
	int dis = 28.014*pow(vout,-1.234);

	return dis;
}

double GetWATER(){

	int value = GetADC(ADC_MUX_WATER);
	double depth = 0;
	if(value > 700){
		value = WATER_MAX;
	}
	else if(value < 500){
		value = WATER_MIN;
	}
	depth = (double)(value-WATER_MIN)/(WATER_MAX-WATER_MIN);
	depth = depth/25;

	return depth;

}


//////////////////////////////////////////////////////////////////
//Trigger()
//CalTHEMISTER
// Input :
// Output : 
//////////////////////////////////////////////////////////////////
void Trigger(){
	cbi(PORTC, 0);
	_delay_us(2);
	sbi(PORTC, 0);
	_delay_us(10);
	cbi(PORTC, 0);
}

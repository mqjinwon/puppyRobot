/*
* MCU_Init.h
*
* Created: 2019-04-20 오후 3:02:08
* Author: Administrator
*/

#ifndef _MCU_INIT_H__
#define _MCU_INIT_H__

//////////////////////////////////////////////////////////////////
//include
//////////////////////////////////////////////////////////////////
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

#define F_CPU 16000000UL
#include <util/delay.h>



#define		sbi(PORTX,BitX)	PORTX|= (1<<BitX)	//비트 set	 명령 정의
#define		cbi(PORTX,BitX)	PORTX&=~(1<<BitX)	//비트 clear 명령 정의


//////////////////////////////////////////////////////////////////
//Functions
//////////////////////////////////////////////////////////////////


void InitIO();
void InitExtInt();

void InitTimer0();
void InitTimer1();
void InitTimer2();
void InitTimer3();

void InitADC();
int GetADC(char ch);

void InitUart0();
void InitUart1();

void TransUart0(unsigned char data);
void TransUart1(unsigned char data);

void TransNumUart0(int num);
void TransNumUart1(int num);

unsigned char RecvUart0();
unsigned char RecvUart1();

//센서 변환 함수들
int GetResistor();
int GetCDS();
int GetLM35();
int GetTHEMISTER();
int GetGAS();
int GetPOWER();
int GetPSD();
double GetWATER();
void Trigger();

//////////////////////////////////////////////////////////////////
// enum for Sensor
enum{
	WATER_MAX = 700,
	WATER_MIN = 500
};
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//enum for external interrupt
//EICRA
enum{

	INT0_LOW_LEVEL,
	INT0_RESERVED,
	INT0_FALLING,
	INT0_RISING,
	
	INT1_LOW_LEVEL = 0x00,
	INT1_RESERVED = 0x04,
	INT1_FALLING = 0x08,
	INT1_RISING = 0x0C,
	
	INT2_LOW_LEVEL = 0x00,
	INT2_RESERVED = 0x10,
	INT2_FALLING = 0x20,
	INT2_RISING = 0x30, 
	
	INT3_LOW_LEVEL = 0x00,
	INT3_RESERVED = 0x40,
	INT3_FALLING = 0x80,
	INT3_RISING = 0xC0
};

//EICRB
enum{

	INT4_LOW_LEVEL,
	INT4_TOGGLE,
	INT4_FALLING,
	INT4_RISING,
	
	INT5_LOW_LEVEL = 0x00,
	INT5_TOGGLE = 0x04,
	INT5_FALLING = 0x08,
	INT5_RISING = 0x0C,
	
	INT6_LOW_LEVEL = 0x00,
	INT6_TOGGLE = 0x10,
	INT6_FALLING = 0x20,
	INT6_RISING = 0x30,
	
	INT7_LOW_LEVEL = 0x00,
	INT7_TOGGLE = 0x40,
	INT7_FALLING = 0x80,
	INT7_RISING = 0xC0
};

//EIMSK
enum{

	INT0_ENABLE = 0x01,
	INT1_ENABLE = 0x02,
	INT2_ENABLE = 0x04,
	INT3_ENABLE = 0x08,
	INT4_ENABLE = 0x10,
	INT5_ENABLE = 0x20,
	INT6_ENABLE = 0x40,
	INT7_ENABLE = 0x80
};



//////////////////////////////////////////////////////////////////
//enum for timer0
//TCCR0
enum{
	
	TIMER0_WGM_NORMAL = 0x00,
	TIMER0_WGM_PWM = 0x08,
	TIMER0_WGM_CTC = 0x40,
	TIMER0_WGM_FAST_PWM	= 0x48
};
enum{

	TIMER0_COM_NORMAL = 0x00,
	TIMER0_COM_TOGGLE_OC0 = 0x10,
	TIMER0_COM_RESERVED_OC0 = 0x10,
	TIMER0_COM_CLEAR_OC0 = 0x20,
	TIMER0_COM_SET_OC0 = 0x30
};
enum{

	TIMER0_CS_NO_CLOCK_SOURCE,
	TIMER0_CS_PRESCALER_1,
	TIMER0_CS_PRESCALER_8,
	TIMER0_CS_PRESCALER_32,
	TIMER0_CS_PRESCALER_64,
	TIMER0_CS_PRESCALER_128,
	TIMER0_CS_PRESCALER_256,
	TIMER0_CS_PRESCALER_1024
};


//////////////////////////////////////////////////////////////////
//enum for timer2
//TCCR2
enum{
	
	TIMER2_WGM_NORMAL = 0x00,
	TIMER2_WGM_PWM = 0x08,
	TIMER2_WGM_CTC = 0x40,
	TIMER2_WGM_FAST_PWM	= 0x48
};
enum{

	TIMER2_COM_NORMAL = 0x00,
	TIMER2_COM_TOGGLE_OC0 = 0x10,
	TIMER2_COM_RESERVED_OC0 = 0x10,
	TIMER2_COM_CLEAR_OC0 = 0x20,
	TIMER2_COM_SET_OC0 = 0x30
};
enum{

	TIMER2_CS_NO_CLOCK_SOURCE,
	TIMER2_CS_PRESCALER_1,
	TIMER2_CS_PRESCALER_8,
	TIMER2_CS_PRESCALER_64,
	TIMER2_CS_PRESCALER_256,
	TIMER2_CS_PRESCALER_1024,
	TIMER2_CS_EXTERNAL_CLOCK_T2_FALLING,
	TIMER2_CS_EXTERNAL_CLOCK_T2_RISING
};


//////////////////////////////////////////////////////////////////
//enum for uart
//UCSRA
enum{

	USART_MULTI_PROCESSOR_MODE = 0x01,
	USART_DOUBLE_SPEED = 0x02,
	USART_PARITY_ERROR = 0x04,
	USART_DATA_OVERRUN = 0x08,
	USART_FRAME_ERROR = 0x10,
	USART_UDR_EMPTY = 0x20,
	USART_TRANS_COMPLETE = 0x40,
	USART_RECV_COMPLETE = 0x80
};

//UCSRB
enum{
	USART_CHAR_SIZE_9BIT_B = 0x04,
	USART_TRANS_ENABLE = 0x08,
	USART_RECV_ENABLE = 0x10,
	USART_UDR_EMPTY_INTERRUPT_ENABLE = 0x20,
	USART_TRANS_INTERRUPT_ENABLE = 0x40,
	USART_RECV_INTERRUPT_ENABLE = 0x80
};

//UCSRC
enum{

	USART_SYNC_MODE	= 0x40,
	USART_PARITY_NONE = 0x00,
	USART_PARITY_EVEN = 0x20,
	USART_PARITY_ODD = 0x30,
	USART_STOP_1BIT	= 0x00,
	USART_STOP_2BIT = 0x08,
	USART_CHAR_SIZE_5BIT = 0x00,
	USART_CHAR_SIZE_6BIT = 0x02,
	USART_CHAR_SIZE_7BIT = 0x04,
	USART_CHAR_SIZE_8BIT = 0x06,
	USART_CHAR_SIZE_9BIT_C = 0x06,
	USART_SYNC_CLOCK_RISING = 0x00,
	USART_SYNC_CLOCK_FALLING = 0x01
};

//UBRRL
enum{

	USART_9600BPS = 103,
	USART_115200BPS = 8
};


//////////////////////////////////////////////////////////////////
//enum for adc
//ADMUX
enum{

	ADC_REF_SELECTION_AREF = 0x00,
	ADC_REF_SELECTION_AVCC = 0x40,
	ADC_REF_SELECTION_INTERNAL = 0xC0,
	ADC_ADJUST_RIGHT = 0x00,
	ADC_ADJUST_LEFT = 0x20
};

enum{

	ADC_MUX_RESISTOR,
	ADC_MUX_CDS,
	ADC_MUX_LM35,
	ADC_MUX_THERMISTER,
	ADC_MUX_PSD,
	ADC_MUX_WATER,
	ADC_MUX_GAS, // 6번
	ADC_MUX_POWER // 7번

};

//ADCSRA
enum{

	ADC_INTERRUPT_ENABLE = 0x08,
	ADC_FREE_RUNNING = 0x20,
	ADC_CONVERTION_START = 0x40,
	ADC_ENABLE = 0x80
};
enum{
	ADC_PRESCALER_2,
	ADC_PRESCALER_4 = 2,
	ADC_PRESCALER_8,
	ADC_PRESCALER_16,
	ADC_PRESCALER_32,
	ADC_PRESCALER_64,
	ADC_PRESCALER_128
};

#endif
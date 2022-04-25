/*
 * LCD.c
 *
 * Created: 2022-04-04 오전 10:50:34
 *  Author: YJ
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"

void clcd_cmd(uint8_t cmd)		// Command Setting
{
	RS_CLEAR;
	RW_CLEAR;
	E_SET;
	_delay_us(50);
	LCD_DATA_PORT = cmd;
	_delay_us(50);
	E_CLEAR;
}
void clcd_data(uint8_t data)	// Data In Put
{	
	RS_SET;
	RW_CLEAR;
	E_SET;	
	_delay_us(50);
	LCD_DATA_PORT = data;
	_delay_us(50);
	E_CLEAR;
}

void clcd_init(void)		// CLCD Initialization
{		
	LCD_CONTROL_DDR_SET;	// Control Port DDR set
	LCD_DATA_DDR_SET;		// Data Port DDR set
	_delay_ms(20);			// 4.5V 이상 될 때까지 15ms 이상 대기
	
	/* 인터페이스/디스플레이 설정 */
	clcd_cmd(0x38);			// 8Bit 인터페이스, 두 줄 표시, 문자 5x7 도트
	_delay_ms(2);
	
	/* 화면 ON/OFF 제어*/
	clcd_cmd(0x0c);			// 하위 4Bit		DB3		  DB2	 	  DB1		  DB0	
	_delay_ms(2);			//			    기본    화면 표시   커서 표시  커서 블링크 기능
	
	/* 화면 클리어 */
	clcd_cmd(0x01);			// 0b 0000 0001
	_delay_ms(30);
	
	/* 엔트리 모드 세트*/
	clcd_cmd(0x06);			// 데이터를 쓰거나 읽기를 수행할 때의 동작 모드 결정
	_delay_ms(2);			// DB1 셋
}
void clcd_gotoXY(uint8_t x, uint8_t y)	// CLCD Pos Set
{
	clcd_cmd(0x80 | ((y*0x40) + x));	// 0x80=DDRAM Address, y*0x40=열, x=행
}
void clcd_putc(char c)		// CLCD print 1Byte
{
	clcd_data(c);
	_delay_ms(1);
}
void clcd_puts(char* text)	// CLCD print Bytes
{
	while(*text != '\0'){
		if(*text == '%')
			clcd_putc(*(++text)-'0');
		else
			clcd_putc(*text);
		text++;
	}
}
void clcd_PutsXY(uint8_t x, uint8_t y, char* text)	// CLCD Pos Set and print Bytes
{
	clcd_gotoXY(x, y);
	clcd_puts(text);
}
void clcd_Clear(void)		// LCD Text Clear
{
	RS_CLEAR;
	RW_CLEAR;
	clcd_data(0x01);
	_delay_ms(2);
}

void clcd_CustomFont(uint8_t add, uint8_t font[8])
{
	uint8_t cgram_addr = 0x40 | (0x08*add);
	
	clcd_cmd(cgram_addr);
	_delay_ms(1);
	
	for(int i=0; i<8; i++){
		clcd_data(font[i]);
		_delay_ms(1);
	}
}
void clcd_PutCustomFont(uint8_t add)
{	
	clcd_putc(add);
}
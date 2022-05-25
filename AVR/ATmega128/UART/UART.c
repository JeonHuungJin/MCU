/*
 * UART.c
 *
 * Created: 2022-04-19 오전 10:08:52
 *  Author: YJ
 */ 

#define F_CPU	16000000

#include <avr/io.h>
#include <stdio.h>
#include "UART.h"

void uart_init(uint8_t uart_num, uint8_t rx_isr, uint8_t tx_isr, uint8_t u2x ,uint16_t burr){
	if(uart_num == UART0){
		UCSR0A = u2x<<U2X0;				// 2배속 모드 설정
		UCSR0B = 1<<RXEN0 | 1<<TXEN0;			// 수신, 송신 가능
		UCSR0B |= rx_isr<<RXCIE0 | tx_isr<<TXCIE0;	// 송, 수신 인터럽트 설정
		
		UBRR0H = burr>>8;	// 보오레이트 상위 레지스터
		UBRR0L = burr&0xff;	// 보오레이트 하위 레지스터
		
		#ifdef STDIO_UART0	// STDIO_UART0이 선언 되었다면
			stdin = stdout = stderr = &uart0_stdio;	// 표준 입출력 
		#endif
	}
	else if(uart_num == UART1){
		UCSR1A = u2x<<U2X1;				// 2배속 모드 설정
		UCSR1B = 1<<RXEN1 | 1<<TXEN1;			// 수신, 송신 가능
		UCSR1B |= rx_isr<<RXCIE1 | tx_isr<<TXCIE1;	// 송, 수신 인터럽트 설정
				
		UBRR1H = burr>>8;	// 보오레이트 상위 레지스터
		UBRR1L = burr&0xff;	// 보오레이트 하위 레지스터
		
		#ifdef STDIO_UART1	// STDIO_UART1이 선언 되었다면
			stdin = stdout = stderr = &uart1_stdio;	// 표준 입출력 
		#endif		
	}
}

uint8_t uart0_rx(FILE *stream){
	while(!(UCSR0A & (1<<RXC0)));	// 수신 대기
	return UDR0;					// 수신된 값 반환
}
void uart0_tx(uint8_t data, FILE *stream){
	while(!(UCSR0A & (1<<UDRE0)));	// 송신 준비
	UDR0 = data;					// UDR0에 data 값을 대입함으로 데이터 전송 완료
}
void uart0_tx_str(char *text){
	while(*text != '\0'){
		uart0_tx(*text, NULL);
		text++;
	}
}
void uart0_Clear(){
	uart0_tx(ClearCode, NULL);
}
void uart0_NewLine(){
	uart0_tx_str(NewLineCode);
}

uint8_t uart1_rx(FILE *stream){
	while(!(UCSR1A & (1<<RXC1)));	// 수신 대기
	return UDR1;			// 수신된 값 반환
}
void uart1_tx(uint8_t data, FILE *stream){
	while(!(UCSR1A & (1<<UDRE1)));	// 송신 준비
	UDR1 = data;			// UDR0에 data 값을 대입함으로 데이터 전송 완료
}
void uart1_tx_str(char *text){
	while(*text != '\0'){
		uart1_tx(*text, NULL);
		text++;
	}
}
void uart1_Clear(){
	uart1_tx(ClearCode, NULL);
}
void uart1_NewLine(){
	uart1_tx_str(NewLineCode);
}

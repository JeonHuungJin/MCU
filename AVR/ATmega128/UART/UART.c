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

void uart_init(uint8_t uart_num, uint8_t isr, uint8_t u2x ,uint16_t burr){
	if(uart_num == UART0){
		UCSR0A = u2x<<U2X0;						// 2배속 모드 설정
		UCSR0B = 1<<RXEN0 | 1<<TXEN0;			// 수신, 송신 가능
		UCSR0B |= isr<<RXCIE0 | isr<<TXCIE0;	// 송, 수신 인터럽트 설정
		
		UBRR0H = burr>>8;
		UBRR0L = burr&0xff;
		
		#ifdef STDIO_UART0
			stdin = stdout = stderr = &uart0_stdio;
		#endif
	}
	else if(uart_num == UART1){
		UCSR1A = u2x<<U2X1;
		UCSR1B = 1<<RXEN1 | 1<<TXEN1;
		UCSR1B |= isr<<RXCIE1 | isr<<TXCIE1;	// 송, 수신 인터럽트 설정
				
		UBRR1H = burr>>8;
		UBRR1L = burr&0xff;
		
		#ifdef STDIO_UART1
			stdin = stdout = stderr = &uart1_stdio;
		#endif		
	}
}

uint8_t uart0_rx(FILE *stream){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
void uart0_tx(uint8_t data, FILE *stream){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
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
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}
void uart1_tx(uint8_t data, FILE *stream){
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data;
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

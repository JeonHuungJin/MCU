/*
 * UART.h
 *
 * Created: 2022-04-19 오전 10:08:44
 *  Author: YJ
 */ 


#ifndef UART_H_
#define UART_H_

#define UART0			0
#define UART1			1

#define TX_ISR_DISABLE		0
#define TX_ISR_ENABLE		1

#define RX_ISR_DISABLE		0
#define RX_ISR_ENABLE		1

#define SPEED_NORMAL		0
#define SPEED_DOUBLE		1

#define ClearCode		'\f'
#define NewLineCode		"\n\r"

enum _NORMAL_BURR{
	NORMAL_2400 = 416,
	NORMAL_4800 = 207,
	NORMAL_9600 = 103,
	NORMAL_14400 = 68,
	NORMAL_19200 = 51,
	NORMAL_28800 = 34,
	NORMAL_38400 = 25,
	NORMAL_57600 = 16,
	NORMAL_76800 = 12,
	NORMAL_115200 = 8,
	NORMAL_230400 = 3,
	NORMAL_250000 = 3,
};

enum _DOUBLE_BURR_1{
	DOUBLE_2400 = 832,
	DOUBLE_4800 = 416,
	DOUBLE_9600 = 207,
	DOUBLE_14400 = 138,
	DOUBLE_19200 = 103,
	DOUBLE_28800 = 68,
	DOUBLE_38400 = 51,
	DOUBLE_57600 = 34,
	DOUBLE_76800 = 25,
	DOUBLE_115200 = 16,
	DOUBLE_230400 = 8,
	DOUBLE_250000 = 7,
};

/* UART Initialization Function
 * uart_num: UART0 or UART1		=> 유아트 포트 선택
 * isr: ISR_DISABLE or ISR_ENABLE	=> 인터럽트 사용 선택
 * u2x: SPEED_NORMAL or SPEED_DOUBLE	=> 두배속 모드 사용 선택
 * burr: _NORMAL_BURR or _DOUBLE_BURR_1	=> 보오레이트 설정
 */
void uart_init(uint8_t uart_num, uint8_t rx_isr, uint8_t tx_isr, uint8_t u2x ,uint16_t burr);

uint8_t uart0_rx(FILE *stream);			// receive uart0
void uart0_tx(uint8_t data, FILE *stream);	// transmit uart0
void uart0_tx_str(char *text);			// transmit str uart0
void uart0_Clear();				// Hyper Terminal Window Clear uart0
void uart0_NewLine();				// Hyper Terminal New Line uart0

uint8_t uart1_rx(FILE *stream);			// receive uart1
void uart1_tx(uint8_t data, FILE *stream);	// transmit uart1
void uart1_tx_str(char *text);			// transmit str uart1
void uart1_Clear();				// Hyper Terminal Window Clear uart1
void uart1_NewLine();				// Hyper Terminal New Line uart1

/*
 * 표준 입출력 설정
 * 둘중 하나만 설정 가능
 */
#define STDIO_UART0		// define 하면 표준 입출력으로 설정됨
//#define STDIO_UART1		// define 하면 표준 입출력으로 설정됨

#ifdef STDIO_UART0
	static FILE uart0_stdio = FDEV_SETUP_STREAM(uart0_tx, uart0_rx, _FDEV_SETUP_RW);
#endif

#ifdef STDIO_UART1
	static FILE uart1_stdio = FDEV_SETUP_STREAM(uart1_tx, uart1_rx, _FDEV_SETUP_RW);
#endif

#endif /* UART_H_ */

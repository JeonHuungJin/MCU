/*
 * LCD.h
 *
 * Created: 2022-04-04 오전 10:50:22
 *  Author: YJ
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_CONTROL_DDR		DDRB
#define LCD_DATA_DDR		DDRA

#define LCD_CONTROL_PORT	PORTB
#define LCD_DATA_PORT		PORTA

#define RS_PIN				PB0		// High: Data send	/	Low: command send
#define RW_PIN				PB1		// High: Read		/	Low: Write
#define E_PIN				PB2		// H->L: Data Enable

#define LCD_CONTROL_DDR_SET	LCD_CONTROL_DDR|=(1<<RS_PIN)|(1<<RW_PIN)|(1<<E_PIN)
#define LCD_DATA_DDR_SET	LCD_DATA_DDR|=0xff;

#define RS_SET				LCD_CONTROL_PORT|=(1<<RS_PIN)
#define RW_SET				LCD_CONTROL_PORT|=(1<<RW_PIN)
#define E_SET				LCD_CONTROL_PORT|=(1<<E_PIN)

#define RS_CLEAR			LCD_CONTROL_PORT&=~(1<<RS_PIN)
#define RW_CLEAR			LCD_CONTROL_PORT&=~(1<<RW_PIN)
#define E_CLEAR				LCD_CONTROL_PORT&=~(1<<E_PIN)

#define CLCD_ROW_SIZE		16
#define CLCD_COL_SIZE		2

typedef enum _CUSTOM_FONT_ADDRES {
	FONT0,
	FONT1,
	FONT2,
	FONT3,
	FONT4,
	FONT5,
	FONT6,
	FONT7,
};

void clcd_cmd(uint8_t cmd);
void clcd_data(uint8_t data);
void clcd_init(void);
void clcd_gotoXY(uint8_t x, uint8_t y);
void clcd_putc(char c);
void clcd_puts(char* text);
void clcd_PutsXY(uint8_t x, uint8_t y, char* text);
void clcd_Clear(void);

void clcd_CustomFont(uint8_t add, uint8_t font[8]);
void clcd_PutCustomFont(uint8_t font);
#endif /* LCD_H_ */
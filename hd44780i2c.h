/* 
 * File:   hd44780i2c.h
 * Author: dinusha
 *
 * Created on December 16, 2015, 11:16 PM
 */

#ifndef HD44780I2C_H
#define	HD44780I2C_H

#include <stdint.h>

#define HD44780I2C_ADDR 0x20

//#define lcd_data      PORTB
//#define lcd_data_tris TRISB
#define lcd_en        0x1
#define lcd_rs        0x0
//#define lcd_rw        RB6
#define lcd_busy      0x7

//bit rs_flag = 0;
uint8_t HD44780_DATA = 0;


void hd44780_pulse(void);
void hd44780_init(void);
void hd44780_clear(void);
void hd44780_write(uint8_t, uint8_t);
void hd44780_busy(void);
void hd44780_putchar(uint8_t);
void hd44780_putchar_at(uint8_t, uint8_t);
void hd44780_newline();
void hd44780_puts(uint8_t *);
void hd44780_puts_at(uint8_t *, uint8_t);
void hd44780_clear();
void hd44780_lighton();
void hd44780_lightoff();
//void hd44780_printstr( char *, unsigned char );
//void hd44780_printchr( char, unsigned char );
//void hd44780_printint( int, unsigned char );
//void hd44780_newline(void);
//void hd44780_printdecimal( int, int, unsigned char );
//void hd44780_block_erase( unsigned char, unsigned char );

#endif	/* HD44780I2C_H */


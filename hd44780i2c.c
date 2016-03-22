/*
* <one line to give the program's name and a brief idea of what it does.>
* Copyright (C)2015  D.N. Amerasinghe
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <xc.h>
//#include <stdio.h>

#include "i2c.h"
#include "hd44780i2c.h"

uint8_t light_status = 0x00;

void hd44780_pulse()
{
//	lcd_en = 1;
//	__delay_us(1);
//	lcd_en = 0;
}

void hd44780_init()
{
    uint8_t ack = 1;
    
    i2c_start();
    i2c_send_controlbyte(HD44780I2C_ADDR, 0);
    ack = i2c_read_ack();
    i2c_send_data( 0b0000000 );
    i2c_read_ack();
    i2c_stop();
    
    //__delay_ms(5);
    
	// Setting lcd_port as output
	//lcd_data_tris = 0x00;
	//lcd_data = 0x00;
	// Delay for more than 15ms 
	__delay_ms(20);
    
    i2c_start();
    i2c_send_controlbyte(HD44780I2C_ADDR, 0);
    ack = i2c_read_ack();
    i2c_send_data( 0b00100011 );
    i2c_read_ack();
    i2c_send_data( 0b00000011 );
    i2c_read_ack();
    i2c_stop();
    //printf("-------------------------\r\n");
    //printf("HD44780 ACK %d\r\n", ack);
    __delay_ms(5);
    
    i2c_start();
    i2c_send_controlbyte(HD44780I2C_ADDR, 0);
    ack = i2c_read_ack();
    i2c_send_data( 0b00100011 );
    i2c_read_ack();
    i2c_send_data( 0b00000011 );
    i2c_read_ack();
    i2c_stop();
    __delay_us(120);
    
    i2c_start();
    i2c_send_controlbyte(HD44780I2C_ADDR, 0);
    ack = i2c_read_ack();
    i2c_send_data( 0b00100011 );
    i2c_read_ack();
    i2c_send_data( 0b00000011 );
    i2c_read_ack();
    i2c_stop();
    __delay_ms(5);
    
    i2c_start();
    i2c_send_controlbyte(HD44780I2C_ADDR, 0);
    ack = i2c_read_ack();
    
    i2c_send_data( 0b00100010 );
    i2c_read_ack();
    i2c_send_data( 0b00000010 );
    i2c_read_ack();
    
//    i2c_send_data( 0b00100010 );
//    i2c_read_ack();
//    i2c_send_data( 0b00000010 );
//    i2c_read_ack();
//    
//    i2c_send_data( 0b00101100 );
//    i2c_read_ack();
//    i2c_send_data( 0b00001100 );
//    i2c_read_ack();
//    
//    i2c_send_data( 0b00100000 );
//    i2c_read_ack();
//    i2c_send_data( 0b00000000 );
//    i2c_read_ack();
//    
//    i2c_send_data( 0b00101000 );
//    i2c_read_ack();
//    i2c_send_data( 0b00001000 );
//    i2c_read_ack();
//    
//    i2c_send_data( 0b00100000 );
//    i2c_read_ack();
//    i2c_send_data( 0b00000000 );
//    i2c_read_ack();
//    
//    i2c_send_data( 0b00100001 );
//    i2c_read_ack();
//    i2c_send_data( 0b00000001 );
//    i2c_read_ack();
//    
//    i2c_send_data( 0b00100000 );
//    i2c_read_ack();
//    i2c_send_data( 0b00000000 );
//    i2c_read_ack();
//    
//    i2c_send_data( 0b00101110 );
//    i2c_read_ack();
//    i2c_send_data( 0b00001110 );
//    i2c_read_ack();
    
//   
//    
//    i2c_send_data( 0b00100110 );
//    i2c_read_ack();
//    i2c_send_data( 0b00000110 );
//    i2c_read_ack();
   
    
    //i2c_send_data( 0b00110100 );
    //i2c_read_ack();
    //i2c_send_data( 0b00010100 );
    //i2c_read_ack();
    
    //i2c_send_data( 0b00111000 );
    //i2c_read_ack();
    //i2c_send_data( 0b00011000 );
    //i2c_read_ack();
    
    //i2c_send_data( 0b00000000 );
    //i2c_read_ack();
    
    i2c_stop();
    
    __delay_ms(5);
    

    
//    i2c_start();
//    //printf("XXXXXXXXXXXXXX");
//    i2c_send_controlbyte(HD44780I2C_ADDR, 0);
//    ack = i2c_read_ack();
//    i2c_send_data( 0b001000 );
//    i2c_read_ack();
//    i2c_send_data( 0b001010 );
//    i2c_read_ack();
//    i2c_stop();
    
//	lcd_data = 0b00000011;
//	hd44780_pulse();
//	__delay_ms(5);
//	lcd_data = 0b00000011;
//	hd44780_pulse();
//	__delay_us(120);
//	lcd_data = 0b00000011;
//	hd44780_pulse();
//	//__delay_ms(5);
//	hd44780_busy();
//	// Setting function 4bit
//	lcd_data = 0b00000010;
//	hd44780_pulse();
//	//__delay_ms(5);
//	hd44780_busy();
//	// Data is now to be sent as 4bit
//
    //hd44780_write( 0b00101100, 0 );
	//hd44780_write( 0b00001000, 0 );
	//hd44780_write( 0b00001111, 0 );
	//hd44780_write( 0b00000001, 0 );
	//hd44780_write( 0b00000110, 0 );
    
    
	hd44780_write( 0b00101000, 0 );
	//hd44780_write( 0b00001111 );
	hd44780_write( 0b00001100, 0 );
	hd44780_write( 0b00000001, 0 );
	hd44780_write( 0b00000110, 0 );
    
//    hd44780_putchar( 'U' );
//    hd44780_putchar( 'D' );
//    hd44780_putchar( 'E' );
//    hd44780_putchar( 'S' );
//    hd44780_putchar( 'H' );
//    hd44780_putchar( 'I' );
//    hd44780_putchar( 'K' );
//    hd44780_putchar( 'A' );
//    hd44780_write( 0xC0, 0 );
//    hd44780_putchar( 'D' );
//    hd44780_putchar( 'I' );
//    hd44780_putchar( 'N' );
//    hd44780_putchar( 'U' );
//    hd44780_putchar( 'S' );
//    hd44780_putchar( 'H' );
//    hd44780_putchar( 'A' );
    //hd44780_write( 0b01001000, 1 );
}

void hd44780_write( uint8_t bt, uint8_t  rs_flag)
{
	uint8_t tmp1, tmp2;

	tmp1 = bt & 0xF0;
	tmp1 = tmp1 >> 4;
    tmp2 = bt & 0x0F;
    
    if(rs_flag == 1){
        tmp1 = tmp1 | 0x10;
		tmp2 = tmp2 | 0x10;
	}
	// Sending upper nibble first
    i2c_start();
    i2c_send_controlbyte(HD44780I2C_ADDR, 0);
    i2c_read_ack();
    i2c_send_data( light_status | 0b00100000 | tmp1 );
    i2c_read_ack();
    i2c_send_data( light_status | 0b00000000 | tmp1 );
    i2c_read_ack();
    
	// Sending low nibble   
    i2c_send_data( light_status | 0b00100000 | tmp2 );
    i2c_read_ack();
    i2c_send_data( light_status | 0b00000000 | tmp2 );
    uint8_t ack = i2c_read_ack();
    
    i2c_send_data( light_status | 0b00000000 | (tmp2 & ~(1 << 4)) );
    i2c_read_ack();

    i2c_stop();
    //printf("WRITE ACK %d\r\n", ack);
    //printf("WRITE DATA (0x%x, 0x%x)\r\n", tmp1, tmp2);

	// should check busy flag here
	__delay_ms(5);
	//hd44780_busy();
}


void hd44780_putchar(uint8_t ch)
{
    hd44780_write( ch, 1 );
}

void hd44780_newline()
{
    hd44780_write( 0xC0, 0 );
}

void hd44780_putchar_at(uint8_t ch, uint8_t loc)
{
    hd44780_write( 0x80 | loc, 0 );
    hd44780_write( ch, 1 );
}

void hd44780_puts(uint8_t *ch)
{
    while( *ch != '\0' ){
        if( *ch == '\n' ){
            hd44780_write( 0xC0, 0 );
        }else if(*ch == '\r'){
            hd44780_write( 0x80, 0 );
        }else{
            hd44780_write( *ch, 1 );
        }
        ch++;
    }
}

void hd44780_puts_at(uint8_t *ch, uint8_t loc)
{
    hd44780_write( 0x80 | loc, 0 );
    hd44780_puts(ch);
}

void hd44780_clear()
{
    hd44780_write( 0b00000001, 0 );
}

void hd44780_lighton()
{
    light_status = 0b10000000;
}

void hd44780_lightoff()
{
    light_status = 0;
}
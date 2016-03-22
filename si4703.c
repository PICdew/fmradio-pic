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
#include <stdint.h>
#include <string.h>


#include "uart.h"
#include "i2c.h"
#include "si4703.h"

#define SI4703_I2C_ADDR 0x10

#define SI4703_RST	     PORTCbits.RC1
#define SI4703_RST_TRIS	 TRISCbits.TRISC1
#define SI4703_SDIO      PORTCbits.RC4
#define SI4703_SDIO_TRIS TRISCbits.TRISC4

#define BANDSPACING 100/1000


uint16_t si4703_regs[16] = {0};

void si4703_setup_2wire()
{
	SI4703_SDIO = 0;
    //gpio_value( SDIO, GPIO_LO );
	__delay_us(1000);
    SI4703_RST = 0;
	//gpio_value( RST, GPIO_LO );
	__delay_us(1000);
    SI4703_RST = 1;
	//gpio_value( RST, GPIO_HI );
    __delay_us(100000);
}


void si4703_init()
{
    uint8_t ack = 1;
    uint8_t device_id = 0, chip_rev = 0, chip_number = 0;
	uint16_t manu_id = 0, firmware_ver = 0;
    uint8_t buff[16] = {0};
    
    SI4703_RST  = 1;
    SI4703_SDIO = 1;
    
    SI4703_RST_TRIS  = 0;
    SI4703_SDIO_TRIS = 0;
    si4703_setup_2wire();
    
    //SI4703_SDIO_TRIS = 1;
    //SI4703_RST_TRIS  = 1;
    
    // Set i2c actions
    i2c_init();
    //i2c_start();
    //printf("XXXXXXXXXXXXXX");
    
    si4703_read_regs(si4703_regs);
	//si4703_print_regs(si4703_regs);

	device_id    = (si4703_regs[0] & 0xF000) >> 12;
	manu_id      = si4703_regs[0] & 0x0FFF;
	chip_rev     = (si4703_regs[1] >> 10) & 0x3F;
	chip_number  = (si4703_regs[1] >> 6) & 0x0F;
	firmware_ver = si4703_regs[1] & 0x3F;
    
    //printf("Device ID = %x\r\n", (si4703_regs[0] & 0xF000) >> 12);
    
    //if( device_id == 0x01 && manu_id == 0x242  ){
		
		//printf("Device Found.\r\n");
		//printf("Chip Rev. %x\n", si4703_regs[01]);
		//printf("Chip Number %x\r\n", chip_number);
		//printf("Chip Rev. %x\r\n", chip_rev);
	//}else{
		//printf("Device not found. Exiting....\r\n");
		//exit(-1);
	//}
    
    //buff[10] = 0x81;	
    si4703_regs[0x07] = 0x8100;
    si4703_write_regs(si4703_regs);

	__delay_us(500000);
    
    si4703_read_regs(si4703_regs);

	si4703_regs[0x02] = 0x4001;	


    si4703_write_regs(si4703_regs);
    __delay_us(120000);
    
    si4703_read_regs(si4703_regs);
    //volume
    //si4703_regs[0x5] = 0x000F & 0x0009;
    //band spacing
    si4703_regs[0x5] |= 0x0010;
    
    si4703_set_volume(0x0e);
    
    si4703_regs[0x6] |= 0x0011;
    si4703_write_regs(si4703_regs);
    si4703_read_regs(si4703_regs);
    //si4703_print_regs(si4703_regs);
    // Enabling RDS
	si4703_regs[0x4] |= 0x1000;
	si4703_write_regs(si4703_regs);
    
    //si4703_tune(989);
    si4703_tune(875);
    //si4703_seek(0);
    //si4703_seek(0);
    //si4703_seek(1);
    //si4703_seek(1);
    //si4703_print_regs(si4703_regs);
}

void si4703_read_regs(uint16_t *r)
{
    uint8_t i = 0, tmp = 1, buff[32];
    
    //i2c_init();
    di();
    i2c_start();
    //printf("XXXXXXXXXXXXXX");
    i2c_send_controlbyte(SI4703_I2C_ADDR, 1);
    i2c_read_ack();
    
    for(i=0;i<32;i++){
        buff[i] = i2c_read_data();
        if(i < 31)
            i2c_send_ack();
        else
            i2c_send_nack();
    }
    
    i2c_stop();
    
    ei();
    
    //printf("ACK = %d\r\n", tmp);
	
	uint8_t x = 0xA;
	for(i=0;i<16;i++){
		//printf("0x%x\r\n", buff[i]);
		*(r + x) = (uint16_t)buff[i * 2] << 8 | buff[(i * 2) + 1];

		if( x == 0xF ){
			x = 0;
		}else{
			x++;
		}

		//printf("0x%x\n", *(r + i));
	}
}

void si4703_write_regs(uint16_t *r)
{
    uint8_t i;
    
    di();
    i2c_start();
    //printf("XXXXXXXXXXXXXX");
    i2c_send_controlbyte(SI4703_I2C_ADDR, 0);
    i2c_read_ack();
    //printf("%x\r\n", *(r+0x03));
    for(i=0x02;i<0x08;i++){
        //High byte first
        i2c_send_data( (*(r + i) >> 8) );
        i2c_read_ack();
        i2c_send_data( *(r + i) & 0x00FF );
        i2c_read_ack();
    }
    
    i2c_stop();
    ei();
}

//void si4703_print_regs(uint16_t *r)
//{
//	int i;
//	printf("=========================================\r\n");
//	for(i=0;i<16;i++){
//		printf("0x%x - 0x%x\r\n", i, *(r + i));
//	}
//	printf("=========================================\r\n");
//}

void si4703_tune(uint16_t freq)
{
	//int chn = 883;
	//chn *= 10;
	//chn -= 875;
	//chn /= 2;
	uint16_t chn = freq - 875;
	

	si4703_regs[0x3] = 0x8000 | chn;
	si4703_write_regs(si4703_regs);
	__delay_us(100000);
	//si4703_regs[0x3] = 0x0000 | chn;
	si4703_regs[0x3] = (~0x8000) & chn;
	si4703_write_regs(si4703_regs);
    
    si4703_read_regs(si4703_regs);
}

void si4703_set_volume(uint8_t val)
{
	//si4703_regs[0x5] = 0x000A;
	si4703_regs[0x5] |= (0x0F & val);
	si4703_write_regs(si4703_regs);
	si4703_read_regs(si4703_regs);
}

void si4703_volume_up()
{
    si4703_read_regs(si4703_regs);
	uint8_t cvol = si4703_regs[0x5] & 0x000F;
	cvol = ++cvol % 0xF;


	si4703_regs[0x5] |= cvol;
	si4703_write_regs(si4703_regs);
}

void si4703_volume_down()
{
    si4703_read_regs(si4703_regs);
	uint8_t cvol = si4703_regs[0x5] & 0x000F;
    if(cvol > 0)
        cvol--;
	
	si4703_regs[0x5] |= cvol;
	si4703_write_regs(si4703_regs);
}

uint16_t si4703_getrssi()
{
    uint8_t buff[2];
    
    di();
    i2c_start();
    //printf("XXXXXXXXXXXXXX");
    i2c_send_controlbyte(SI4703_I2C_ADDR, 1);
    i2c_read_ack();
    
    buff[0] = i2c_read_data();
    i2c_send_ack();

    buff[1] = i2c_read_data();
    i2c_send_nack();

    
    i2c_stop();
    
    ei();

    return ((buff[0] << 8 | buff[1]) & 0x01FF);
}

uint16_t si4703_getchannel()
{
    return (si4703_regs[0xB] & 0x03FF);
}

void si4703_powerdown()
{
	si4703_regs[0x7] |= 1 << 14;
	si4703_write_regs(si4703_regs);
	si4703_regs[0x4] |= 0x002A;
	si4703_write_regs(si4703_regs);
	si4703_regs[0x2] &= 0xBFFF;
	si4703_write_regs(si4703_regs);
	si4703_regs[0x2] = 0x0041;
	si4703_write_regs(si4703_regs);
	__delay_us(100000);
}

void si4703_mute()
{
	si4703_read_regs(si4703_regs);
	si4703_regs[0x2] = si4703_regs[0x2] ^ 0x4000;
	si4703_write_regs(si4703_regs);
}

void si4703_seek(uint8_t seekdown)
{
    si4703_read_regs(si4703_regs);
    //Start seek
    si4703_regs[0x2] &= ~(0x0400);
    si4703_regs[0x2] |= (0x0200 | 0x0100);
    if(seekdown)
        si4703_regs[0x2] &= ~(0x0200);
    
    
    si4703_write_regs(si4703_regs);
    si4703_read_regs(si4703_regs);
     
    while( !(si4703_regs[0xA] & (0x4000)) && !(si4703_regs[0xA] & (0x2000)) ){
        //printf("SEEKING\r\n");
        si4703_read_regs(si4703_regs);
        
        __delay_ms(60);
    }
    
    //Setting seek = 0 and clearing STC
    si4703_regs[0x2] &= ~(0x0100);
    si4703_regs[0xA] &= ~(0x4000);
    si4703_write_regs(si4703_regs);
}
void si4703_get_rds(uint8_t *buff)
{
    strncpy(buff, &si4703_regs[0xC], 2);
    //strncpy(buff, si4703_regs[0xC], 16);
}
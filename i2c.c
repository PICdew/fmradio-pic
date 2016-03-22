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
#include <stdio.h>

#include "i2c.h"

static uint8_t tries;

void i2c_init()
{
    //I2C SDA and SCL pins as inputs
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;

    //Configuring MSSP module as master mode
    SSPCON = 0b00101000;
    //Configuring i2c levels and slew rate as standard
    SSPSTAT = 0b10000000;
    //Configuring the baud rate
    SSPADD = (FOSC_SPEED / (4 * BAUD)) - 1;
    //Wait for stabilization
    __delay_ms(10);
}

void i2c_start()
{
    PIR1bits.SSPIF = 0;
    SSPCON2bits.SEN = 1;
    tries = 0;
    while( !PIR1bits.SSPIF && tries++ < 50 ){
        __delay_us(1);
    } //Wait for SSPIF to go back to high

//    if( tries == 50 ){
//        printf("I2C Error: Start Timeout\r\n");
//        return;
//    }
}

void i2c_stop()
{
    if( i2c_check_overflow() ){
        //printf("I2C Warning: Buffer overflow\r\n");
        i2c_enable();
    }else{
        PIR1bits.SSPIF = 0;
        SSPCON2bits.PEN = 1;
        tries = 0;
        while( !PIR1bits.SSPIF && tries++ < 50 ){
            __delay_us(1);
        } //Wait for SSPIF to go back to high

//        if( tries == 50 ){
//            printf("I2C Error: Stop Timeout\r\n");
//            return;
//        }
    }
}

void i2c_send_controlbyte( uint8_t addr, uint8_t rw_bit )
{
    PIR1bits.SSPIF = 0;
    SSPBUF = (addr << 1) | (rw_bit & 1);
    tries = 0;
    while( !PIR1bits.SSPIF && tries++ < 50 ){
        __delay_us(1);
    } //Wait for SSPIF to go back to high
    if( tries == 50 ){
        //printf("I2C Error: Control Byte Timeout\r\n");
        return;
    }
}

void i2c_send_data( uint8_t dta )
{
    PIR1bits.SSPIF = 0;
    SSPBUF = dta;
    tries = 0;
    
    while( !PIR1bits.SSPIF && tries++ < 50 ){
        __delay_us(1);
    } //Wait for SSPIF to go back to high
    if( tries == 50 ){
        //printf("I2C Error: Send Data Timeout\r\n");
        return;
    }
}

uint8_t i2c_read_data()
{
    //uint8_t dta;

    PIR1bits.SSPIF = 0;
    SSPCON2bits.RCEN = 1;
    tries = 0;
    while( !PIR1bits.SSPIF && tries++ < 50 ){
        __delay_us(1);
    } //Wait for SSPIF to go back to high
    //dta = SSPBUF;
    if( tries == 50 ){
        //printf("I2C Error: Read Data Timeout\r\n");
        return 0;
    }
    
    return SSPBUF;
}


void i2c_send_repstart()
{
    PIR1bits.SSPIF = 0;
    SSPCON2bits.RSEN = 1;
    tries = 0;
    while( !PIR1bits.SSPIF && tries++ < 50 ){
        __delay_us(1);
    } //Wait for SSPIF to go back to high
    
    if( tries == 50 ){
        //printf("I2C Error: Repeat Start Timeout\r\n");
        return;
    }
}

void i2c_send_ack()
{
    PIR1bits.SSPIF = 0;
    SSPCON2bits.ACKDT = 0;
    SSPCON2bits.ACKEN = 1;
    tries = 0;
    while( !PIR1bits.SSPIF && tries++ < 50 ){
        __delay_us(1);
    } //Wait for SSPIF to go back to high
    if( tries == 50 ){
        //printf("I2C Error: ACK Timeout\r\n");
        return;
    }
}

void i2c_send_nack()
{
    PIR1bits.SSPIF = 0;
    SSPCON2bits.ACKDT = 1;
    SSPCON2bits.ACKEN = 1;
    tries = 0;
    while( !PIR1bits.SSPIF && tries++ < 50 ){
        __delay_us(1);
    } //Wait for SSPIF to go back to high
    if( tries == 50 ){
        //printf("I2C Error: Timeout\r\n");
        return;
    }
}

uint8_t i2c_read_ack()
{
    return SSPCON2bits.ACKSTAT;
}

uint8_t i2c_check_overflow()
{
    return SSPCONbits.SSPOV;
}

void i2c_enable()
{
    SSPCONbits.SSPEN = 1;
}

uint8_t i2c_bus_busy()
{
    return !(PORTCbits.RC3 && PORTCbits.RC4);
}
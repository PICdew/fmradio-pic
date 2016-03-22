/*
* This is the main program.
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
#include <stdio.h>
#include <stdlib.h>

#include "uart.h"
#include "i2c.h"
#include "si4703.h"
#include "hd44780i2c.h"

#define _XTAL_FREQ      20000000 // 20MHz Clock


#pragma config BOREN = ON, CPD = OFF, FOSC = HS, WDTE = OFF, CP = OFF, LVP = OFF, PWRTE = ON

uint16_t rssi = 0;
uint8_t scale = 0;
//uint8_t buff[16] = {0};

eeprom uint16_t last_channel;

void init()
{
    //Disabling the A2D converter
    ADCON0bits.ADON = 0;

    //PORTC = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 0;
   
    PORTBbits.RB2 = 0;
    
    //Enabling Timer 1 interrupt
    T1CONbits.TMR1ON  = 1;
    T1CONbits.T1CKPS0 = 1; //
    T1CONbits.T1CKPS1 = 1;
    
    PIE1bits.TMR1IE  = 1;
    INTCONbits.PEIE  = 1;
    INTCONbits.GIE   = 1;
}

void interrupt isr()
{
    if(PIR1bits.TMR1IF){
        scale++;
        //Send data in 15s interval
        //if( scale == 20 ){
            
            //scale = 0;
        //}
        //uint16_t rssi = si4703_getrssi();
        
        //printf("RSSI = %d\r\n", rssi);
        
//        if(rssi & 0x0100){
//            //printf("Stereo\r\n");
//            PORTBbits.RB2 = 1;
//        }else{
//            //printf("Mono\r\n");
//            PORTBbits.RB2 = 0;
//        }
       //if( scale == 20 ){
           //last_channel = si4703_getchannel();
       //}
        
       if( scale == 70 ){
            hd44780_lightoff();
            
            //PIE1bits.TMR1IE  = 0;
            //PIR1bits.TMR1IF = 0;
            
            scale = 0;
       }
        

        
        //hd44780_puts_at(buff, 0); 
        // Re-enabling interrupt
        PIR1bits.TMR1IF = 0;
    }
}

uint8_t debounce(uint8_t port, uint8_t pin)
{
    uint8_t count = 0;
    
    while( !(port & (1 << pin)) && count < 5 ){
        //PORTBbits.RB2 = 0;
        __delay_ms(10);
        count++;
    }
    
    if(count == 5){
        return 1;
    }else{
        return 0;
    }
}

int main(int argc, char** argv)
{
    uint8_t btn_pressed = 1;
    uint8_t buff[16] = {0};
    //uint8_t buff[16] = {0};
    uint16_t channel = 0;
    uint8_t whole = 0, frac = 0;

    init();
    uart_init();
    
    si4703_init();
    
    hd44780_init();
    
    //hd44780_putchar_at('X', 8);
    //sprintf(buff, "%s\n", "TEST");
    //hd44780_puts("TEST STRING\n");
    //hd44780_puts("TEST STRING");
    //hd44780_puts(buff);        
    
    hd44780_lighton();
    
    si4703_tune( last_channel + 875 );

    while(1){
        
        rssi = si4703_getrssi();
        
        //if( scale == 1 ){
        sprintf(buff, "%d", rssi & 0x00FF);
        hd44780_puts_at(buff, 14);
            
        //si4703_get_rds(buff);
        //sprintf(buff, "%s", buff);
        //hd44780_newline();
        //hd44780_puts_at(buff, 0);
            //scale = 0;
        //}
        
        
        
        if(rssi & 0x0100){
            //printf("Stereo\r\n");
            PORTBbits.RB2 = 1;
        }else{
            //printf("Mono\r\n");
            PORTBbits.RB2 = 0;
        }
        //printf("RSSI = %d\r\n", rssi);
        
//        if(rssi & 0x0100){
//            //printf("Stereo\r\n");
//            PORTBbits.RB2 = 1;
//        }else{
//            //printf("Mono\r\n");
//            PORTBbits.RB2 = 0;
//        }
        
        if(debounce(PORTB, 1)){
            btn_pressed = 1;
            //PORTBbits.RB2 = 0;
            //btn1_pressed = 1;
            hd44780_lighton();
            //TMR1 = 0;
            scale = 0;
            si4703_seek(0);
            //last_channel = si4703_getchannel();
            //continue;
            //__delay_ms(200);
            //while( debounce(PORTB, RB1) );
        }
        if(debounce(PORTB, 0)){
            //printf("RB0 pressed\r\n");
            btn_pressed = 1;
            hd44780_lighton();
            //TMR1 = 0;
            scale = 0;
            si4703_seek(1);
            //last_channel = si4703_getchannel();
        }
        

        if(!btn_pressed)
            continue;
            
        
        channel = si4703_getchannel();
        float chn = ((channel * 0.1) + 87.5);
        whole = chn;
        float f1 = chn - whole;
        frac = (uint8_t)(f1 * 10);
        //whole = ((channel * 0.1) + 875)/10;
        //F = S x C + L
        //sprintf(buff, "%f", ((channel * 0.1) + 875)/10);
        sprintf(buff, "%d.%dMhz ", whole, frac);
        //hd44780_clear();
        hd44780_puts_at(buff, 4);

        
        //__delay_ms(200);
       last_channel = si4703_getchannel(); 
       btn_pressed = 0;
       
    }

    return (EXIT_SUCCESS);
}
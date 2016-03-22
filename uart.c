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
#include <stdio.h>
#include <stdlib.h>

#include "uart.h"

void uart_init()
{
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    //SPBRG = 0x19;       //9600 baud rate
    //TXEN = 1;
    //BRGH = 1;
    //SPEN = 1;
    //CREN = 1;
    TXREG = 0;
    RCREG = 0;
    SPBRG = 0x40;
    TXSTA = 0x24;
    RCSTA = 0x90;
}

void putchar(char data)
{
    while( !TXIF )
        continue;
    TXREG = data;
}

char getchar()
{
    while( !RCIF )
        continue;
    return RCREG;
}

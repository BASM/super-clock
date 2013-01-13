/*
 * uart.c  - uart utils
 * Creation Date: 2012-05-20
 *
 * Copyright (C) 2012 Leonid Myravjev (asm@asm.pp.ru)
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include <stdio.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include "config.h"

void uart_bchar(char c){
      while ( !( UCSR0A & (1<<UDRE0)) );
      UDR0 = c;
}

static int bchar_put(char ch, FILE* file)
{
  uart_bchar(ch);
  return 0;
}

static FILE uart_stdout=FDEV_SETUP_STREAM(bchar_put, NULL, _FDEV_SETUP_WRITE);



int uart_init(){
#ifndef F_CPU
#error Please set F_CPU!
#endif
  UCSR0A = 0;
  UCSR0B = 0x18;
  UCSR0C = 0x06;

//#define BAUD 115200
#define BAUD 9600
#include <util/setbaud.h>
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif
}

int uart_stdio(){
    stdout=&uart_stdout;
    stderr=&uart_stdout;
  //FIXME add stdio
}

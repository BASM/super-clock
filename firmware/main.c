/*
 * main.c  - Main of firmware
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

#include "config.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "uart.h"
#include "leds.h"


int main(void)
{
    wdt_disable();
    cli();

    DDRD=0xFE;
    DDRB=0xFf;
    uart_init();
    uart_stdio();

    char sec,min,hour;
    sec=min=0;
    unsigned char num=0;
    hour=0;
    min=36;
    sec=0;

    for(;;){    /* main event loop */
 /*
      leds_put(8);
      leds_put(8);
      leds_put(8);
      leds_put(8);
  */
    char m=num%2;
    if(m){
      sec+=1;
      if(sec>=60){
        sec=0;
        min+=1;
      }
      if(min>=60){
        min=0;
        hour+=1;
      }
      if(hour>=24){
        hour=0;
      }
    }
    leds_put(hour/10,m);
    leds_put(hour%10,m);
    leds_put(min/10,m);
    leds_put(min%10,m);
     /*
    leds_put(num*m);
    leds_put((16-num)*m);
    leds_put(num*m);
    leds_put((16-num)*m);
    */
    num++;
    if(num > 16) num = 0;
    leds_strobe();

    //printf("Hello world\r\n");
    _delay_ms(500);
    }
    return 0;
}


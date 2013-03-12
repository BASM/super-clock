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
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "uart.h"
#include "leds.h"

#include <ir.h>

static char sec,min,hour;
//#define DIVER 10 // FIXME Fo= Fclc / (2 * N * (1 + OCR1A)) it is 10, but we set 20.
#define DIVER 6000
static unsigned int count =0;
static unsigned long time=0;

ir_event ev;

ISR(TIMER2_COMPA_vect)
{
  static int oldpin=0;

  ev.time = time*(1000/6);

  int pin= (PIND>>2)& 0x01;
  if(pin != oldpin){
    ev.stat = !pin;
    //printf("Pin change (to: %i) %i.\r\n",ev.stat, time);
    ir_set_event(&ev);
    time=0;
    oldpin=pin;
  }
  if(time<393)
    time++;

  if(++count>=DIVER){
    //printf("Time: %2.2i:%2.2i:%2.2i\n\r", hour,min,sec);
    count=0;
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
}

int hexdump(unsigned char* buff, int size)
{
  int i;
  for(i=0; i<size; i++){
    if(((i%16)==0)){
      printf("\n\r%4.4x ", i); 
    }
    printf("%2.2x ", buff[i]);
  }
  printf("\n\r");
  return 0;
}



int ir_dumpresult(char* array, int size)
{
  unsigned char a,b,c,d;
  a=array[0];
  b=array[1];
  c=array[2];
  d=array[3];

  if (a==0x40){
    if(b==0xff){
      if ( (c==0x01) && (d==0xfe) ) hour = (hour+1)%24;
      if ( (c==0x04) && (d==0xfb) ) hour = (hour+23)%24;

      if ( (c==0x02) && (d==0xfd) ) min = (min+1)%60;
      if ( (c==0x05) && (d==0xfa) ) min = (min+59)%60;

      if ( (c==0x03) && (d==0xfc) ) sec = (sec+1)%60;
      if ( (c==0x06) && (d==0xf9) ) sec = (sec+59)%60;
    }
  }
  return 0;
}

int main(void)
{
    wdt_disable();
    cli();

    DDRC=0xFE;

    DDRD=0xFA;//P2 input
    PORTD=0xFF;//pullup
    DDRB=0xFf;
    uart_init();
    uart_stdio();

    ///set time
    char buff[10];
    strcpy(buff, __TIME__);
    buff[2]='\0';
    buff[5]='\0';

    hour=atoi(&buff[0]);
    min=atoi(&buff[3]);
    sec=atoi(&buff[6]);

    timer2();
    sei();
    int m=0;
    /////EXTERNAL LIBS INIT

    ir_init();

    ////////////////////////
    for(;;){    /* main event loop */

    leds_put(hour/10,m);
    leds_put(hour%10,m);
    leds_put(min/10,m);
    leds_put(min%10,m);
    leds_put(sec/10,m);
    leds_put(sec%10,m);
    leds_strobe();
    _delay_ms(1);

    leds_put(17,m);
    leds_put(17,m);
    leds_put(17,m);
    leds_put(17,m);
    leds_put(17,m);
    leds_put(17,m);
    leds_put(17,m);
    leds_strobe();

    _delay_ms(10);
    }
    return 0;
}


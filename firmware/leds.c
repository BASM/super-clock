/*
 * leds.c  - Driver for led screen
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

#define clk(i)  ({if(i){PORTB |= 0x2;}else{PORTB &= ~0x2;}})
#define data(i) ({if(i){PORTB |= 0x1;}else{PORTB &= ~0x1;}})
#define str(i)  ({if(i){PORTB |= 0x4;}else{PORTB &= ~0x4;}})
#define drop()  ({PORTB &= ~0x3;})

#define wait() _delay_us(1);

static int putcode(unsigned char num)
{
  int i=8;
  while(i--){
    data((num>>i)&1);
    wait();
    clk(1);
    wait();
    drop();
  }
}

int leds_put(unsigned char num, unsigned char dot){
#define DOTNUM (1<<7)
    // 0 -- '-'
    // 1 -- left up
    // 2 -- up
    // 3 -- rigth up
    // 4 -- left down
    // 5 -- down
    // 6 -- rigth down
    //    .   RD  D   LD  RU  U   LU  -
    // 0  0   1   1   1   1   1   1   0
    // 1  0   1   0   0   1   0   0   0
    // 2  0   0   1   1   1   1   0   1
    // 3  0   1   1   0   1   1   0   1
    // 4  0   1   0   0   1   0   1   1
    // 5  0   1   1   0   0   1   1   1
    // 6  0   1   1   1   0   1   1   1
    // 7  0   1   0   0   1   1   0   0
    // 8  0   1   1   1   1   1   1   1
    // 9  0   1   1   0   1   1   1   1
    // A  0   1   0   1   1   1   1   1
    // B  0   1   1   1   1   1   1   1
    // C  0   0   1   1   0   1   1   0
    // D  0   1   1   1   1   1   1   0
    // E  0   0   1   1   0   1   1   1
    // F  0   0   0   1   0   1   1   1
    // -  0   0   0   0   0   0   0   1
      //                 0    1     2     3     4     5     6     7     8     9
      //                 -   
  unsigned char ARA[]={0x7e, 0x48, 0x3d, 0x6d, 0x4b, 0x67, 0x77, 0x4c, 0x7f, 0x6f,
      //                
      //                 A    B     C     D     E     F     -
                       0x5f, 0x7f, 0x36, 0x7e, 0x37, 0x17, 0x01, 0x00};

  if(num>sizeof(ARA))
    return -1;

  if(dot)  putcode(ARA[num]|DOTNUM);
  else     putcode(ARA[num]);

  return 0;
}

int leds_strobe(){
  str(1);
  wait();
  str(0);
  return 0;
}

#if 0 // FIXME test
int main(void)
{
    wdt_disable();
    cli();

    DDRD=0xFE;
    DDRB=0xFf;
    uart_init();
    uart_stdio();
    str(1);

    unsigned char num=0;
    for(;;){    /* main event loop */

      putnum(num++);
      if(num > 12) num = 0;
      str(0);
      wait();
      str(1);
      wait();
      str(0);

      //printf("Hello world\r\n");
      _delay_ms(200);
    }
    return 0;
}
#endif

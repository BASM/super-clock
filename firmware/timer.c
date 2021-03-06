/*
 * timer.c - support function for timers working
 * Creation Date: 2011-05-08
 *
 * Copyright (C) 2011 Leonid Myravjev (asm@asm.pp.ru)
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
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include <avr/power.h>

#include "timer.h"
#include "support.h"

int timer0()
{
    //// 8 bit timer programming....
    // Diver 8 (20000 kHZ / 8 => 2500 kHz)
    //  needed 36 kHz.
    // 2500 / 36.0 => 69.444 (0x45)
    //
    // TCCR0A
    //  7 - COMOA1
    //  6 - COMOA0
    //  5 - COMOB1
    //  4 - COMOB0
    //  3,2
    //  1 - WGMO1
    //  0 - WGMO0
    // 0b000100
    
    // for TCCR0A --
    // 0b01000011 -- TIMER 0 (OC0A in toggle mode), TIMER 1 is off 
    //         ||- WGM00 == 1 -- it needed ;-)
    //         |- WGM01 == 0 TOP <-> BOTTOM
    //                     1 BOTTOM <-> TOP
    // for
    //         | WGM02 == 1 -- its toggle OC0A it comapre match
    //
    //
    // // DDR must be set (its set)
    //*
    TCCR0A=0x43;
    //TCCR0B
    // 0b??--1101
    //   ||   | 010 -- clk/8
    //   ||   \ 101 -- clk/1024
    //   ||FOC0B
    //   |FOC0A
    TCCR0B=0x0a;//0b00001010
    TIMSK0=0x00;//no needed interrupt
    OCR0A=20;//0x29;
    power_timer0_enable();

    DDRBIT(D, 6, 1);//=0xFD;
    //*/
    return 0;
}

int timer1()
{
    //// 16 bit timer programming....
    // TCCR0A
    //  7 - COMOA1
    //  6 - COMOA0
    //  5 - COMOB1
    //  4 - COMOB0
    //  3,2
    //  1 - WGMO1
    //  0 - WGMO0
    // 0b000100
    
    // for TCCR0A --
    // 0b01000011 -- TIMER 0 (OC0A in toggle mode), TIMER 1 is off 
    //         ||- WGM00 == 1 -- it needed ;-)
    //         |- WGM01 == 0 TOP <-> BOTTOM
    //                     1 BOTTOM <-> TOP
    // for
    //         | WGM02 == 1 -- its toggle OC0A it comapre match
    //
    //
    // // DDR must be set (its set)
    //*
    TCCR1A=0x00;
    //TCCR0B
    // CS12,11,10
    //  0 0 0 -- stoped
    //  0 0 1 -- 1
    //  0 1 0 -- 8
    //  0 1 1 -- 64
    //  1 0 0 -- 256
    //  1 0 1 -- 1024
    //  1 1 0 -- ext1
    //  1 1 1 -- ext2
    TCCR1B=0x0B;//0b00001011
    //                   \\\ 64
    //                  |ctc mode

    //FIXME
    TIMSK1=0x02;//COMPARE A
    OCR1A=9374;
    power_timer1_enable();


    return 0;
}

int timer2()
{   //FOR timer 2
    //power_timer1_enable();

    // 12 000 000 / 1024 / 2dc6 == 1 Hz
    TCCR2A=0x02;
    TCCR2B=0x02;//Diver /8

    //OCR2A=250;
    OCR2A=249;

    TIMSK2=0x02;//COMPARE A

    ASSR=1<<5|1<<6;
    //TCCR0B
    // 0b??--1101
    //   ||   | 010 -- clk/8
    //   ||   \ 101 -- clk/1024
    //   ||FOC0B
    //   |FOC0A

    power_timer2_enable();

    //DDRBIT(D, 6, 1);//=0xFD;
  

  return 0;
}



int timer_off()
{

  return 0;
}

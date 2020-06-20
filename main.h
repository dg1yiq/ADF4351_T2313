#ifndef F_CPU
#define F_CPU 1000000
#endif

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/cpufunc.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

//Prototypen

#define nop() asm volatile("nop")
void writePLL(uint32_t pll_word);

//Definition LED's
#define     ADF_PORT    PORTB
#define     ADF_DDR     DDRB
//#define     ADF_CE      PB3   Nichts
#define     ADF_LE      PB5
#define     ADF_DATA    PB7
#define     ADF_CLK     PB6

#endif

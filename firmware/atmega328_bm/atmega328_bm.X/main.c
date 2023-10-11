/*
 * File:   main.c
 * Author: knightleo
 *
 * Created on September 29, 2023, 6:57 PM
 */

#include <util/delay.h>
#include <avr/io.h>
#include <xc.h>

#define F_CPU 16000000

void config() {
    DDRB = 0b00100000;
}

int main(void) {
    config();
    while(1) {
        PORTB = 0b00100000; // liga
        _delay_ms(500);
        PORTB = 0b00000000; // desliga
        _delay_ms(500);
    }
}

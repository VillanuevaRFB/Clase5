#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main (void){
    ADMUX|=(1<<REFS0)|(1<<MUX1)|(1<<ADLAR);
    ADCSRA|=(1<<ADEN)|(1<<ADPS2);
    DDRD|=0xFC;
    DDRB|=0x0F;
    char alow;
    char ahigh;
    while(1){
        ADCSRA|=(1<<ADSC);
        while(!(ADCSRA&(1<<ADIF)));
        alow=ADCL;
        ahigh=ADCH;
        ADCSRA|=(1<<ADIF);
        PORTD&=~(0xFC);
        PORTB&=~(0x0F);
        PORTB|=((ahigh>>4)&0x0F);
        PORTD|=((ahigh<<4)&0xF0)|((alow>>4)&0x0C);
    }
}
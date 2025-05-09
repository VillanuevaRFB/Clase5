#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*
//ejercicio 2
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
}*/

void config_IE0(void){
    EIMSK|=(1<<INT0);
    EICRA|=(1<<ISC01);
    DDRB&=~0X10;
    PORTB|=0X10;
}
void select_channel(char channel){
    if(channel<=15){
        ADMUX&=0xF0;
        ADMUX|=channel;
    }
}
char canal=0;
ISR(INT0_vect){
    canal++;
    select_channel(canal);
    if(canal>2){
        canal=0;
    }
}

int main (void){
    ADMUX|=(1<<REFS0);
    ADCSRA|=(1<<ADEN)|(1<<ADPS2);
    select_channel(0);
    DDRD&=~0x04;
    DDRD|=0xF8;
    DDRB|=0x1F;
    char alow;
    char ahigh;
    config_IE0();
    sei();
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
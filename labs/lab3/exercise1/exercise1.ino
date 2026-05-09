#include <avr/io.h>
#include <util/delay.h>

void timer0_init(){
    TCCR0B |= (1 << CS00) | (1 << CS02); // 1024
    TCNT0 = 0; // counter=0
    TIMSK0 |= (1 << TOIE0); // overflow
}

volatile uint8_t total_overflow = 0;

int main(void){
    DDRC |= (1 << PC0);
    PORTC |= (1 << PC0);   
    timer0_init();
    sei();
    while(1){
      if(total_overflow >= 30){ // (16/1024)*10^6*.5/256
        if(TCNT0 >= 132){ //256-...=132.5
                PORTC ^= (1 << PC0);
                TCNT0 = 0;
                total_overflow = 0;
            }
        }
    }
} 

ISR(TIMER0_OVF_vect){
    total_overflow++;
}
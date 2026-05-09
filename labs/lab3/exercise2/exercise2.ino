#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void timer0_init(){
    TCCR0B |= (1 << CS02); // 256
    TCNT0 = 0; // counter=0
    TIMSK0 |= (1 << TOIE0); // overflow
}

volatile uint8_t total_overflow = 0;
volatile uint8_t count = 0;
int main(void){
  	Serial.begin(9600);
    DDRC |= (1 << PC0);
    PORTC |= (1 << PC0);   
    timer0_init();
    sei();
    while(1){
      if(total_overflow >= 244){ // (16/256)*10^6*1/256
        if(TCNT0 >= 36){ //256-...=36
                PORTC ^= (1 << PC0);
                TCNT0 = 0;
                total_overflow = 0;
				Serial.print("count = ");
    		  	Serial.println(count);
        		count++;
          		if(count==10)
                  count=0;
            }
        }
    }
} 

ISR(TIMER0_OVF_vect){
    total_overflow++;
}
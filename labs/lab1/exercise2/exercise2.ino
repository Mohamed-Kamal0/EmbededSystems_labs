#include <avr/io.h>
#include <util/delay.h>
void setup() {
  DDRB = DDRB & ~(1<<PB0);
  DDRB = DDRB & ~(1<<PB1);
  DDRC = DDRC | (1<<PC0);
  DDRC = DDRC | (1<<PC1);
}

void loop() {
  if(PINB & ~(1<<PB0)){
    PORTC=PORTC | (1<<PC0);
  }else{
    PORTC=PORTC & ~(1<<PC0);
  }
  if(PINB & ~(1<<PB1)){
    PORTC=PORTC | (1<<PC1);
  }else{
    PORTC=PORTC & ~(1<<PC1);
  }
}
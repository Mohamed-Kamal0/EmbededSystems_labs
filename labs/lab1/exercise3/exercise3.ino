#include <avr/io.h>
#include <util/delay.h>
void setup() {
  DDRB = DDRB & ~(1<<PB0);
  DDRC = DDRC | (1<<PC0);
}
int lastState=0;
void loop() {
  int currState=PINB & ~(1<<PB0)?1:0;
  if(lastState==0&&currState==1){
    _delay_ms(50);
    PORTC=PORTC ^ (1<<PC0);
  }
  lastState=currState;
}s
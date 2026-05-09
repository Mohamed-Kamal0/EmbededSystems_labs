#include <avr/io.h>
#include <util/delay.h>
void setup() {
  DDRD = 4;
  PORTD = PORTD & ~(1 << PD6);
}

void loop() {
  _delay_ms(1000);
  PORTD = PORTD ^ (1 << PD6);
}
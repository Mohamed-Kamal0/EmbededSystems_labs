#include <avr/io.h>
#include <util/delay.h>
void setup() {
  DDRD = DDRD & ~(1<<PD2);
  DDRC = DDRC | (1<<PC0);
  // 3. Configure INT0 to trigger on a RISING EDGE
  // EICRA (External Interrupt Control Register A) controls how the interrupt triggers.
  // Setting both ISC01 and ISC00 to 1 makes it trigger when the signal goes LOW to HIGH.
  EICRA=EICRA | (1<<ISC01) | (1<<ISC00);
  // 4. Enable the INT0 interrupt specifically
  // EIMSK (External Interrupt Mask Register) turns on individual external interrupts.
  EIMSK=EIMSK | (1<<INT0);
  sei();
}
int state=0;
void loop() {
  if(state){
    PORTC=PORTC^(1<<PC0);
    state=0;
  }
}
ISR(INT0_vect){
  state=1;
}
  
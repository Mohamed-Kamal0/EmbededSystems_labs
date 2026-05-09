#include <avr/io.h>
#include <util/delay.h>

void timer1_init(){
    TCCR1A = 0;                              // Clear TCCR1A
    TCCR1B |= (1 << WGM12) | (1 << CS12);     // CTC mode, prescaler 256
    TCNT1 = 0;                               // Initialize counter register to 0
    OCR1A = 62499;                           // Compare value for 1 second interval
}

uint8_t count = 0;

int main(void){ 
    Serial.begin(9600);
    
    // Set Port C Pin 0 (PC0 / Analog 0) as an output pin
    DDRC |= (1 << PC0);
    
    // Set PC0 HIGH initially to ensure we can toggle it
    PORTC &= ~(1 << PC0);   
    
    // Initialize Timer 1
    timer1_init();
    
    while(1){
        // Check if the timer has reached the target OCR1A value
        if (TIFR1 & (1 << OCF1A)) { 
            
            // Toggle the LED state on PC0
            PORTC ^= (1 << PC0);
            
            // Print count to Serial Monitor
            Serial.print("count = ");
            Serial.println(count);
            
            count++;
            if (count == 10) {
                count = 0;
            }
            // CORRECT FLAG CLEARING: Direct assignment clears only OCF1A
            TIFR1 = (1 << OCF1A);
        }
       
    }
}
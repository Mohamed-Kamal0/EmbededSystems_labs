#include <avr/io.h>
#include <util/delay.h>

void adc_init()
{
    // AREF = AVcc
    ADMUX = (1<<REFS0);

    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE);
    sei();
}
uint8_t AdcConversion_flag=0;
int16_t adc_read(uint8_t ch)
{
    // select the corresponding channel 0~5
    // ANDing with 7 will always keep the value
    // of ch between 0 and 5
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing

    // start single conversion
    // write 1 to ADSC
    ADCSRA |= (1<<ADSC); 
    
    // wait for conversion to complete
    // ADSC becomes 0 again
    // till then, run loop continuously
    if(AdcConversion_flag==1){
        return (ADC);
    }
    return -1;
}

void setup() {
    DDRC = DDRC & ~(1<<PC0);
    DDRB = DDRB | (1<<PB0)| (1<<PB1)| (1<<PB2)| (1<<PB3);
    PORTB = 0;
    adc_init();
    Serial.begin(9600);
}

void loop() {
    // FIXED: Declared the variable type (uint16_t)
    uint16_t adc_result0 = adc_read(0);  // read adc value at PC0
    if(adc_result0>0){
         Serial.println(adc_result0);
    // condition for led to turn on or off
    if(adc_result0 >= 256){
        PORTB |= (1<<PB0);
    } else {
        PORTB &= ~(1<<PB0);
    }
    
    if(adc_result0 >= 512){
        PORTB |= (1<<PB1);
    } else {
        PORTB &= ~(1<<PB1);
    }
    
    if(adc_result0 >= 768){
        PORTB |= (1<<PB2);
    } else {
        PORTB &= ~(1<<PB2);
    }
    
    if(adc_result0 >= 1022){
        PORTB |= (1<<PB3);
    } else {
        PORTB &= ~(1<<PB3);
    }
    }
   
}
ISR(ADC_vect){
    AdcConversion_flag=1;
}
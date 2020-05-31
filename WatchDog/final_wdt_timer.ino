#include <avr/wdt.h>

int count=0;
void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Starting");
  cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
  

}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  count+=1;
  
}

 
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(count);
  if(count<=5)
  {
    Serial.println("hey");
    
  }
  else{
    watchdogSetup();
    while(1);
  }
}

void watchdogSetup(void) 
{
  cli();// disable all interrupts 
  wdt_reset(); // reset the WDT timer
  WDTCSR |= B00011000; // Enter Watchdog Conﬁguration mode
  WDTCSR = B01001110;//Setting the watch dog timer to 32ms
  sei(); //re enabling interrupts
}

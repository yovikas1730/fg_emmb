#include <avr/wdt.h>
unsigned int count_sub=0;
unsigned int count_sub1=0;
unsigned int count_master=0;
unsigned int flag=0; 

void setup() {
    Serial.begin(9600);
    Serial.println("Arduino Starting");
    watch_dog_timer(5);    //calling the watch_dog_timer()
}
 
void loop() {
   
}
void watch_dog_timer(int tim)
{
  cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15625;// = (16*10^6) / (1*1024) - 1 (must be <65536)....to be changed for 1ms
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
  
  if(tim<=100)
  {
    flag=0;
  }
  else
  {
    flag=1;
  }
  timer(tim);
}
ISR(TIMER1_COMPA_vect){
//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  count_sub+=1;
  Serial.println(count_sub);
  if(count_sub==100)
  {
    count_sub1+=1;
    count_sub=0;
  }
}
void timer(int tim1)
{
  while(true)
  
  { if(flag==0)
    {
      count_master=count_sub;
    }
    else
    {
      count_master=count_sub1;
    }
    Serial.println(count_master);
    if(count_master<=tim1)
    {
      Serial.println("hey");
    }
    else
    {
      watchdogSetup();
      while(1);
    }
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

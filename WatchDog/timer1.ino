#include<avr/wdt.h> /* Header for watchdog timers in AVR */

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  Serial.println("Watchdog Demo Starting");
  pinMode(13, OUTPUT);
  wdt_disable();  /* Disable the watchdog and wait for more than 2 seconds */
  delay(3000);  /* Done so that the Arduino doesn't keep resetting infinitely in case of wrong configuration */
  wdt_enable(WDTO_2S);  /* Enable the watchdog with a timeout of 2 seconds */
}

void loop() {
  for(int i = 0; i<20; i++) /* Blink LED for some time */ 
  {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    wdt_reset();  /* Reset the watchdog */
  }
  while(1); /* Infinite loop. Will cause watchdog timeout and system reset. */
}

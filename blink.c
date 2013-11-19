#include <stdio.h>
#include <wiringPi.h>

#define	LED	16

int main (void)
{
  printf ("Raspberry Pi blink\n") ;
  wiringPiSetupGpio () ;
  pinMode (LED, OUTPUT) ;
    digitalWrite (LED, LOW) ;
  for (;;)
  {
    digitalWrite (LED, HIGH) ;
    delay (500) ;
    digitalWrite (LED, LOW) ;
    delay (500) ;
  }
  return 0 ;
}

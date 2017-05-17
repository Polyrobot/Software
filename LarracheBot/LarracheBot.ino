#include <avr/io.h>
#include <util/delay.h>

#include "config.h"
#include "usart.h"

#define PLED  PORTB
#define LED   7

int main(void)
{
  DDRB = 0xFF;
  
  USART_Init(207, 1, 0);
  Send_String("LarracheBOT " VERSION "\n", 0);
  
  for(;;)
  {
    PLED ^= (1 << LED);
    _delay_ms(500);
  }

  return 0;
}


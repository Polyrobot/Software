#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "config.h"
#include "moteurs.h"
#include "usart.h"

#define PLED  PORTB
#define LED   7

int main(void)
{
  DDRB = 0xFF;

  // Initialisation USART0: 9600 8N1
  USART_Init(207, 1, 0);
  Send_String("LarracheBOT..." VERSION "\n", 0);

  MOTEURS_Init();
  Send_String("Moteurs.......OK", 0);

  sei();
  
  for(;;)
  {
    // Code de test
    PLED ^= (1 << LED);
    _delay_ms(125);
  }

  return 0;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------------------------------------------

//**************************
//*  GESTION INTERRUPTION  *
//**************************

ISR(USART0_RX_vect)
{
   // Code de test reception USART   
   unsigned char tmp_data = USART_Receive(0);
   if(tmp_data == 'v')
      Send_String("LarracheBOT " VERSION "\n", 0);
}

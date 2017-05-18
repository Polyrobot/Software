#include <avr/io.h>

#include "config.h"
#include "usart.h"

// Envoi un caratere sur USARTx
void Send_Char(char data, uint8_t numusart)
{
  USART_Transmit(data, numusart);
}

// Envoi une chaine de caratere sur USARTx
void Send_String(char *string, uint8_t numusart)
{
  uint8_t ind = 0;
  while(string[ind] != 0)
  {
    USART_Transmit(string[ind], numusart);
    ind++;
  } 
}

// Init USARTx
void USART_Init(uint16_t ubrr, uint8_t u2x, uint8_t numusart)
{
  if(numusart == 0)
  {
    // Set Baud Rate
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
  
    // Registre configuration A: Vitesse x2
    if(u2x == 1)
    {
      UCSR0A |= (1 << U2X0);
    }
    else
    {
     UCSR0A &= ~(1 << U2X0);
    }
  
    // Registre configuration B: Enable TX/RX
    UCSR0B |= (1 << RXCIE0) | (1 << RXEN0)|(1 << TXEN0);
    UCSR0B &= ~(1 << UCSZ02);
  
    // Registre configuration C: 8N1
    UCSR0C = 0x06;
   }

   if(numusart == 1)
   {
    // Set Baud Rate
    UBRR1H = (unsigned char)(ubrr>>8);
    UBRR1L = (unsigned char)ubrr;
  
    // Registre configuration A: Vitesse x2
    if(u2x == 1)
    {
      UCSR1A |= (1 << U2X1);
    }
    else
    {
     UCSR1A &= ~(1 << U2X1);
    }
  
    // Registre configuration B: Enable TX/RX
    UCSR1B |= (1 << RXCIE1) | (1 << RXEN1)|(1 << TXEN1);
    UCSR1B &= ~(1 << UCSZ12);
  
    // Registre configuration C: 8N1
    UCSR1C = 0x06;
   }

   if(numusart == 2)
  {
    // Set Baud Rate
    UBRR2H = (unsigned char)(ubrr>>8);
    UBRR2L = (unsigned char)ubrr;
  
    // Registre configuration A: Vitesse x2
    if(u2x == 1)
    {
      UCSR2A |= (1 << U2X2);
    }
    else
    {
     UCSR2A &= ~(1 << U2X2);
    }
  
    // Registre configuration B: Enable TX/RX
    UCSR2B |= (1 << RXCIE2) | (1 << RXEN2)|(1 << TXEN2);
    UCSR2B &= ~(1 << UCSZ22);
  
    // Registre configuration C: 8N1
    UCSR2C = 0x06;
   }

   if(numusart == 3)
  {
    // Set Baud Rate
    UBRR3H = (unsigned char)(ubrr>>8);
    UBRR3L = (unsigned char)ubrr;
  
    // Registre configuration A: Vitesse x2
    if(u2x == 1)
    {
      UCSR3A |= (1 << U2X3);
    }
    else
    {
     UCSR3A &= ~(1 << U2X3);
    }
  
    // Registre configuration B: Enable TX/RX
    UCSR3B |= (1 << RXCIE3) | (1 << RXEN3)|(1 << TXEN3);
    UCSR3B &= ~(1 << UCSZ32);
  
    // Registre configuration C: 8N1
    UCSR3C = 0x06;
   }
}

// 
void USART_Transmit(unsigned char data, uint8_t numusart)
{
  switch(numusart)
  {
    case 0:
        while (!(UCSR0A & (1<<UDRE0)));  
        UDR0 = data;
        break;
    case 1:
        while (!(UCSR1A & (1<<UDRE1)));  
        UDR1 = data;
        break;
    case 2:
        while (!(UCSR2A & (1<<UDRE2)));  
        UDR2 = data;
        break;
    case 3:
        while (!(UCSR3A & (1<<UDRE3)));  
        UDR2 = data;
        break;        
  }  
}

// Recoi un caractere sur USARTx
unsigned char USART_Receive(uint8_t numusart)
{
  if(numusart == 0)
  {
    while (!(UCSR0A & (1<<RXC0)));  
    return UDR0;
  }
  
  if(numusart == 1)
  {
    while (!(UCSR1A & (1<<RXC1)));  
    return UDR1;
  }
  
  if(numusart == 2)
  {
    while (!(UCSR2A & (1<<RXC2)));  
    return UDR2;
  }
  
  if(numusart == 3)
  {
    while (!(UCSR3A & (1<<RXC3)));  
    return UDR3;
  }
}

void USART_Flush(uint8_t numusart)
{
  unsigned char dummy;
  switch(numusart)
  {
    case 0:
        while (UCSR0A & (1<<RXC0)) dummy = UDR0;
        break;
    case 1:
        while (UCSR1A & (1<<RXC1)) dummy = UDR1;
        break;
    case 2:
        while (UCSR2A & (1<<RXC2)) dummy = UDR2;
        break;
    case 3:
        while (UCSR3A & (1<<RXC3)) dummy = UDR3;
        break;        
  }  
}




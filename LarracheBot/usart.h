#ifndef USART_H_
#define USART_H_

void Send_Char(char data, uint8_t numusart);
void Send_String(char *string, uint8_t numusart);

void USART_Init(uint16_t ubrr, uint8_t u2x, uint8_t numusart);
void USART_Transmit(unsigned char data, uint8_t numusart);
unsigned char USART_Receive(uint8_t numusart);
void USART_Flush(uint8_t numusart);

#endif /* USART_H_ */


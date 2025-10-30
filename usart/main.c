#include <stm32f10x.h>

void delay_ms(uint16_t t);
void usart1_sendbyte(unsigned char c);
void usart1_sendstring(char s[]);
uint8_t usart1_receivebyte(void);
uint8_t receivedbyte;

int main(){
	//USART1 enable, PA enable & Alternate function enable
	RCC->APB2ENR |= (1 << 14)|(1 << 2)|(1 << 0);
	//PA10=RX1 input with pullup
	GPIOA->CRH &= ~((1 << 9)|(1 << 8));//reset
	GPIOA->CRH |= (1 << 10); 	//floating input
	
	//PA9=TX1 output open drain,alt. func.
	GPIOA->CRH |= (1 << 7)|(1 << 6); //alternate open drain
	GPIOA->CRH |= (1 << 5)|(1 << 4); //50 Mhz
	
	//configure USART1
	USART1->CR1 |= ((1 << 13)|(1 << 3)|(1 << 2)); //enable: usart, transmit & receive
	USART1->BRR = 7500;	//baud rate 72,000,000/9,600 = 7,500
	usart1_sendbyte('\n');
	usart1_sendstring("enter character:");  
	delay_ms(1000);
	while(1){
			receivedbyte = usart1_receivebyte();
			usart1_sendbyte(receivedbyte);    
	}
}

void usart1_sendbyte(unsigned char c){
	USART1->DR = c;
	while((USART1->SR&(1<<6))==0); //while not transmitted
	USART1->SR &= ~(1<<6); //reset for a new transmision
}
void usart1_sendstring(char s[]){
	int i = 0;
  while (i < 64)
  {
	  if (s[i] == '\0') break;
	  usart1_sendbyte(s[i++]);
  }
}

uint8_t usart1_receivebyte(){
	while((USART1->SR & (1 << 5)) == 0);//while data not received
	return USART1->DR;
}

void delay_ms(uint16_t t){
	volatile unsigned long l=0;
	for(uint16_t i = 0; i < t;i++)
	for(l = 0;l < 6000;l++)
	{
	}
}
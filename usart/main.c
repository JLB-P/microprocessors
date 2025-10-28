#include <stm32f10x.h>

void delay_ms(uint16_t t);
void usart1_sendbyte(unsigned char c);

int main(){
	//USART1 enable, PA enable & Alternate function enable
	RCC->APB2ENR |= (1 << 14)|(1 << 2)|(1 << 0);
	//PA10=RX1 input with pullup
	GPIOA->CRH &= ~((1 << 9)|(1 << 8));//reset
	GPIOA->CRH |= (1 << 11); 	//with pull-up
	GPIOA->ODR |= (1 << 10);	//activate pull-up
	
	//PA9=TX1 output open drain,alt. func.
	GPIOA->CRH |= (1 << 7)|(1 << 6); //alternate open drain
	GPIOA->CRH |= (1 << 5)|(1 << 4); //50 Mhz
	
	//configure USART1
	USART1->CR1 |= ((1 << 13)|(1 << 3)|(1 << 2)); //enable: usart, transmit & receive
	USART1->BRR = 7500;	//baud rate 72,000,000/9,600 = 7,500
	while(1){
		usart1_sendbyte('H');
		usart1_sendbyte('o');
		usart1_sendbyte('l');
		usart1_sendbyte('a');
		usart1_sendbyte('\n');
		usart1_sendbyte('\r');
		delay_ms(1000);     
	}
}

void usart1_sendbyte(unsigned char c){
	USART1->DR = c;
	while((USART1->SR&(1<<6))==0); //while not transmision complete
	USART1->SR &= ~(1<<6); //reset for a new transmision
}
void delay_ms(uint16_t t){
	volatile unsigned long l=0;
	for(uint16_t i = 0; i < t;i++)
	for(l = 0;l < 6000;l++)
	{
	}
}
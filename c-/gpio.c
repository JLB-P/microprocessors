#include <stm32f10x.h>

void init_portc(void)
{
	RCC->APB2ENR |= 1 << 4; //activa reloj
	GPIOC->CRH |= 1 << 21;
	GPIOC->CRH &= ~(1 << 20);
	GPIOC->CRH &= ~((1 << 22)|(1 << 23));
}

void init_ports(void)
{
	//Enable clock for GPIOC, GPIOB and Alternate Function
	RCC->APB2ENR |= ((1 << 4) | (1 << 3) | (1 << 0));
		
	// Configure PC13 pin as output push-pull maximum speed 10MHz
	GPIOC->CRH &= ~((1 << 23) | (1 << 22));
	GPIOC->CRH |= (1 << 20);
			
	// Configure PB0 pin as input pull up or pull down
	GPIOB->CRL &= ~((1 << 3) | (1 << 2));
	GPIOB->CRL &= ~((1 << 1) | (1 << 0));
	GPIOB->CRL |= (1 << 3);
	
	//Activate PB0 pull up
	GPIOB->ODR |= (1 << 0);
}
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
	
	//use I2C ****************************
	//enable i2c-2
	RCC->APB1ENR |= (1 << 22);	
	//reset PB11 and PB10
	GPIOB->CRH &= ~((1 << 13) | (1 << 12));
	GPIOB->CRH &= ~((1 << 9) | (1 << 8));
	//set PB11 and PB10 as AF Output 50MHz Open-Drain
	GPIOB->CRH |= ((1 << 13) | (1 << 12));	//output 50MHz
	GPIOB->CRH |= ((1 << 9) | (1 << 8));
	GPIOB->CRH |= ((1 << 15) | (1 << 14));	//alternate function open-drain
	GPIOB->CRH |= ((1 << 11) | (1 << 10));
	
	//use of LED ****************************
	//configure PC13 pin as output push-pull maximum speed 10MHz
	GPIOC->CRH &= ~((1 << 23) | (1 << 22));
	GPIOC->CRH |= (1 << 20);
	
	//use of EXTI ***************************
	//configure PB0 pin as input pull up or pull down
	GPIOB->CRL &= ~((1 << 3) | (1 << 2));
	GPIOB->CRL &= ~((1 << 1) | (1 << 0));
	GPIOB->CRL |= (1 << 3);	
	//activate PB0 pull up
	GPIOB->ODR |= (1 << 0);
}
#include <stm32f10x.h>

void init_portc(void)
{
	RCC->APB2ENR |= 1 << 4; //activa reloj
	GPIOC->CRH |= 1 << 21;
	GPIOC->CRH &= ~(1 << 20);
	GPIOC->CRH &= ~((1 << 22)|(1 << 23));
}
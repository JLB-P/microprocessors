#include <stm32f10x.h>
#include "delay.h"

void led_on_off(void)
{
	GPIOC ->ODR |= 1 << 13;
	delay_ms(100);
	GPIOC ->ODR &= ~(1 << 13);
	delay_ms(100);
}
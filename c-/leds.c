#include <stm32f10x.h>

void delay_msx(uint16_t t);

void led_on_off(void)
{
	for (int x=0; x<3; x++){
	GPIOC ->ODR |= 1 << 13;
	delay_msx(100);
	GPIOC ->ODR &= ~(1 << 13);
	delay_msx(200);}
}

void delay_msx(uint16_t t){
	volatile unsigned long l=0;
	for(uint16_t i = 0; i < t;i++)
	for(l = 0;l < 6000;l++)
	{
	}
}
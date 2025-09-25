#include "gpio.h"
#include "leds.h"
#include "delay.h"

int main(void)
{
	init_portc();
	delay_init();
	while(1)
	{
		led_on_off();
	}
}
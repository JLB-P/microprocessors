#include "gpio.h"
#include "ext_in.h"
#include "i2c.h"

int main()
{

	//init_portc();
	init_ports();
	init_exti();
	init_i2c();
	start_i2c();
	/*..*/
	stop_i2c();
	while(1){

	}
}
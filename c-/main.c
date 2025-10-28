#include "gpio.h"
#include "ext_in.h"
#include "i2c.h"

int main()
{

	init_ports();
	init_exti();
	init_i2c();
	wait_i2c();
	start_i2c();
	adress_i2c(0x3c,0);
	
	/*..*/
	//stop_i2c();
	while(1){
		adress_i2c(0x3c,0);
	}
}
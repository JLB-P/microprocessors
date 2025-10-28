#include "stm32f10x.h"
#include "i2c.h"

void init_i2c(void){
	/*tasks done in gpio.c
		1. enable GPIOB clock and alternate functions
		2. enable I2C interface 2
		3. reset PB11(sda)&PB10(scl)
		4. set PB11 & PB10
	*/
	//software reset pulse
	I2C2->CR1 |= (1 << 15);			//reset i2c
	I2C2->CR1 &= ~(1 << 15);	//release the reset
	
	//set Peripheral clock freq
	//I2C2->CR2 = 0x08;	// set f=8Mhz
	I2C2->CR2 = 0x0020;	// set f=32Mhz
	
	//Mode (100Khz->400Khz)
	//I2C2->CCR &= ~(1 << 15);	// standard speed mode
	I2C2->CCR = 0x00B4;
	
	//I2C2->TRISE = 0x09;	//rise time(RM0008 pag 783)
	I2C2->TRISE = 37;
	//peripheral enable
	I2C2->CR1 |= (1 << 0);
}

void wait_i2c(){
	while((I2C2->SR2&(1 << 1)) != 0);
}

//************************
void start_i2c(void){
	I2C2->CR1 |= (1 << 8);		// start transmission
	while(!(I2C2->SR1 & (1<<0))); // wait until ready
}

void stop_i2c(void){
	I2C2->CR1 |= (1 << 9);
}

void adress_i2c(uint8_t address, uint8_t r_w) // 1(read)_0(write) 
{
	I2C2->DR = (address|r_w);
	// wait for the acknowledge
	while((I2C2->SR1 & I2C_SR1_ADDR)==0);
	
	while(I2C2->SR1 & I2C_SR1_ADDR){
		if((I2C2->SR1 & I2C_SR1_ADDR)==0)
			break;
	}
}

void data_i2c(uint8_t data)
{
	// confirm that TXE = 0 before sending
	while((I2C2->SR1 & I2C_SR1_TXE) == 0);
	I2C2->DR = data; // load the data
	// wait until data is sent
	while((I2C2->SR1 & I2C_SR1_TXE) == 0);
}

// write data via I2C
void write_i2c(uint8_t address, uint8_t data[], uint64_t length)
{
	uint64_t i = 0;
	start_i2c();
	adress_i2c(address, 0);
	
	for(i=0; i<length; i++) // send all bytes in data
	{
		data_i2c(data[i]);
	}
	stop_i2c();
}
/*
steps to program USART:
- Enable clocks for GPIOs and USART.
- Configure Control Register: 1 stop bit, no
parity, 
- Set baudrate (BRR register).
- Select alternate function output for UARTn_Tx
UARTn_Rx as input.
- Write a byte to UARTn Data Register.
- Monitor TC bit of Status Register (UARTn_SR)
and wait for trnasmission to complete.
*/

#include <stm32f10x.h>
#include "delay.h"

void usart1_sendbyte(uint16_t data){
	USART1->DR = data;
	while((USART1->SR&(1<<6))==0);
	USART1->SR &= ~(1<<6);
}

void usart1_sendstring(char s[]){
	int i = 0;
	while(i < 64){
		if (s[i] == '\0') break;
		usart1_sendbyte(s[i++]);
	}
}

void usart1_polling(){
	USART1->CR1 |= (1 << 2 | 1 << 3 | 1 << 13); //enable rx,tx and USART
	/* Example Baud rate 9600
	BRR = fpclk/bayd rate = 72,000,000/9600 = 7,500 */
	USART1->BRR = 7500;
	while(1){
		usart1_sendbyte('H');
		usart1_sendbyte('o');
		usart1_sendbyte('l');
		usart1_sendbyte('a');
		usart1_sendstring("USART");
		usart1_sendbyte('\n');
		usart1_sendbyte('\r');
	}
}

void usart1_w_interrupt(){
	USART1->CR1 |= (1 << 2 | 1 << 3 | 1 << 13); //enable rx,tx and USART
	/* Example Baud rate 9600
	BRR = fpclk/bayd rate = 72,000,000/9600 = 7,500 */
	USART1->BRR = 7500; //set baudrate
	//USART1->CR1 |= (1 << 7);	//TXE enable interrupt
	NVIC_EnableIRQ(USART1_IRQn);//enable global interrupts
}

void USART1_IRQHandler(){
	if(USART1->CR1 & USART1->SR & USART_SR_TXE) {
        uint8_t c = 'A';
        USART1->CR1 &= ~USART_CR1_TXEIE;
				USART1->DR = c;
	}
}

void usart1_via_dma(){
	char msg[]="Hola DMA";
	RCC->AHBENR = (1 << 0); //DMA1 clock enable
	RCC->APB2ENR |= 0xFC | (1 << 14); //enable GPIO clk

	//USART1 init
	GPIOA->ODR |= (1 << 10);	//pull up
	GPIOA->CRH = 0x444448B4;	//Rx=input with pull up
														//Tx1=output alternate
	USART1->BRR = 7500;		//72Mhz/9600=7500
	USART1->CR1 = 0x200C;	//enable transmit and receive
	USART1->CR3 = (1 << 7);	//DMA1 transmision enamble
	
	DMA1_Channel4->CPAR = (uint32_t) &USART1->DR; //to
	DMA1_Channel4->CMAR = (uint32_t) msg; 				//from
	DMA1_Channel4 ->CNDTR = 12;	//12 bytes
	DMA1_Channel4->CCR = (1 << 7)|(1 << 4);	//mem inc, read from mem
	DMA1_Channel4->CCR |= 1;	//enable channel 4
}
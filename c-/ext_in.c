#include <stm32f10x.h>
#include "leds.h"

/*
	Select PB0 as the input for external interrupt.
	On each rising edge, an interrupt is generated.
	Interrupt service routine toggles Led on PC13(IRQHandler).
*/
volatile int8_t int0_flag = 0;

void EXTI0_IRQHandler(){
	EXTI->PR = (1 << 0); //clear pending flag
	int0_flag = 1;
	led_on_off();
	}

void init_exti(void){
	/*delay_init();
	AFIO->EXTICR 
	AFIO->EXTICR[1] = 1 << 0;	//selects PB4 for line 4 
	EXTI->FTSR = (1 << 4);		//interrupt on falling edge
	EXTI->IMR = (1 << 4);			//enable interrupt EXTI4
	NVIC_EnableIRQ(EXTI4_IRQn);	//enable interrupt EXTI4*/
	
/*Note 1
	EXTICR is defined as array structure EXTICR[4]
	so 	EXTICR[0] <=> EXTICR1 in reference manual
			EXTICR[1] <=> EXTICR2 in reference manual
			EXTICR[2] <=> EXTICR3 in reference manual
			EXTICR[3] <=> EXTICR4 in reference manual	*/
/*Note 2
	Select pin for external interrupt, example PB0
	identify (pag 210 RM0008) external interrupt line (EXTI0 for PB0)
	and register numer EXTICR1 for EXTI0
	so we have to use AFIO->EXTICR[0] at programming level*/
	
	//Configure EXTI******************
	//select PB0 source input for EXTI0 (pag 191 RM0008)
	AFIO->EXTICR[0] &= ~((1 << 3)|(1 << 2)|(1 << 1)|(1 << 0));
	AFIO->EXTICR[0] |= (1 << 0);
	//select trigger on rising edge (pag 213 RM0008)
	EXTI->RTSR |= (1 << 0);
	//enable EXTI0 
	EXTI->IMR |= (1 << 0);
	//clear pending flag
	EXTI->PR |= (1 << 0);	
	
	//enable the interrupt line at NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);
}

#include<stdint.h>
/*
*	R -> PF1
*	G -> PF2
*	B -> PF3
*/

/*
*	Base Address and Offsets of the Registers
*
*	Clock Gating Control Register -> 0x400FE000 + 0x608 -> RCGCGPIO
*	GPIO Digital Enable Register	-> 0x40025000 + 0x51C	-> GPIODEN
*	GPIO Direction Register 			-> 0x40025000 + 0x400	-> GPIODIR
*	GPIO Data Register						-> 0x40025000 + 0x3FC	-> GPIODATA
*/

#define RCGCGPIO		(*((volatile uint32_t *)0x400FE608U))
#define GPIOBASE    0x40025000U
#define GPIODEN     (*((volatile uint32_t *)(GPIOBASE + 0x51CU)))
#define GPIODIR     (*((volatile uint32_t *)(GPIOBASE + 0x400U)))
#define GPIODATA    (*((volatile uint32_t *)(GPIOBASE + 0x3FCU)))


void delay(int time){
	int volatile counter = 0;
        while (counter < time) {
            ++counter;
        }
}



int main(void) {
	
		RCGCGPIO = 0x20U; 															/*Enabling Clock For Port F on Clock Gating Register*/

		GPIODEN = 0x0EU;																/*Enabling the PINs for Digital Input or Output*/

		GPIODIR = 0x0EU; 															  /*Setting the PINs as Digital Output*/
	

    while (1) {
        GPIODATA = 0x02U;													/*Turning ON the RED Led*/

				delay(1000000);

        GPIODATA = 0x00U;													/*Turing OFF the RED Led*/
			
        delay(1000000);

    }
    //return 0; // unreachable code
}

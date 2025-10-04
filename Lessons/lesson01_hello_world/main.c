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

void delay(int time){
	int volatile counter = 0;
        while (counter < time) {
            ++counter;
        }
}



int main(void) {
	
		uint32_t* RCGCGPIO = (uint32_t *)0x400FE608U;
		*RCGCGPIO = 0x20U; 															/*Enabling Clock For Port F on Clock Gating Register*/
		
		uint32_t* GPIODEN = (uint32_t *)0x4002551CU;
		*GPIODEN = 0x0EU;																/*Enabling the PINs for Digital Input or Output*/
	
		uint32_t* GPIODIR = (uint32_t *)0x40025400U;
		*GPIODIR = 0x0EU; 															/*Setting the PINs as Digital Output*/
	
		uint32_t* GPIODATA = (uint32_t *)0x400253FCU;

    while (1) {
        *GPIODATA = 0x02U;													/*Turning ON the RED Led*/

				delay(1000000);

        *GPIODATA = 0x00U;													/*Turing OFF the RED Led*/
			
        delay(1000000);

    }
    //return 0; // unreachable code
}

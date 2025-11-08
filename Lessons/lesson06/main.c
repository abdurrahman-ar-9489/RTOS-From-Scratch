#include <stdint.h>
#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

/* Read Only Data */

const uint8_t a;
const uint8_t b;

/*Global Initialized variables -> .data*/
uint8_t x = 'A';
uint32_t y = 1;

/*Global Uninitialized variables -> .bss*/

uint8_t c;
uint16_t d;



int main(void) {

    SYSCTL->GPIOHSCTL |= (1U << 5); /* enable AHB for GPIOF */
    SYSCTL->RCGC2 |= (1U << 5);  /* enable clock for GPIOF */

    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    /* start with turning all LEDs off */
    GPIOF_AHB->DATA_Bits[LED_RED | LED_BLUE | LED_GREEN] = 0;

    while (1) {
        //*((unsigned long volatile *)(0x40025000 + (LED_RED << 2))) = LED_RED;
        //*(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;
        //GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED; APB access
        GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;

        delay(1000000);

        GPIOF_AHB->DATA_Bits[LED_RED] = 0;
        
        delay(1000000);

    }
    //return 0;
}
 
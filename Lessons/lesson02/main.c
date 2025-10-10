#include "tm4c.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

void delay(int time){
	int volatile counter = 0;
        while (counter < time) {
            ++counter;
        }
}

int main(void) {

    GPIO_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);

    /* start with turning all LEDs off (note the use of array []) */
    GPIO_PORTF_DATA_BITS_R[LED_RED | LED_BLUE | LED_GREEN] = 0;

    while (1) {
        //*((unsigned long volatile *)(0x40025000 + (LED_RED << 2))) = LED_RED;
        //*(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;
        GPIO_PORTF_DATA_BITS_R[LED_RED] = LED_RED;

        delay(1000000);

        GPIO_PORTF_DATA_BITS_R[LED_RED] = 0;
        
        delay(1000000);

    }
    //return 0; // unreachable code
}

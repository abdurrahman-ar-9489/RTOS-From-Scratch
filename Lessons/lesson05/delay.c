#include "delay.h"

void delay(int time){
	int volatile counter = 0;
        while (counter < time) {
            ++counter;
        }
}
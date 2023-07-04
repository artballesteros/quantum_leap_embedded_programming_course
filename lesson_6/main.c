#include "tm4c123gh6pm.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

void waitFor (int delay) {
  int volatile counter = 0; // ensures the compiler doesn't optimize away this wait
  while (counter < delay)   // by requiring that it always reads counter value from 
    counter++;              // memory and not some register
}

int main() {
  
    /* bitwise assignment is a useful idiom with changing register values.
       It allows one to keep old register values intact without overwriting them.
       Make sure that the registers have read/write permission otherwise you 
       wouldn't be able to do this. You can find out by reading the data sheets.
    */
    
    SYSCTL_RCGCGPIO_R |= (1U << 5); /* enable clock for GPIO port F */
    GPIO_PORTF_DIR_R  |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_DEN_R  |= (LED_RED | LED_BLUE | LED_GREEN);
    
    int counter = 0;
    /* loop will make board blink with colors forever! */
    while (1) {
      waitFor(100000);
      GPIO_PORTF_DATA_R = (++counter & 0b1110) % 16;
      waitFor(100000);
    }

    return 0;
}

#include "tm4c123gh6pm.h"

void waitFor (int delay) {
  int volatile counter = 0; // ensures the compiler doesn't optimize away this wait
  while (counter < delay)   // by requiring that it always reads counter value from 
    counter++;              // memory and not some register
}

int main() {
    
    SYSCTL_RCGCGPIO_R = 0x20U;
    GPIO_PORTF_DIR_R = 0x0EU;
    GPIO_PORTF_DEN_R = 0x0EU;
    
    int counter = 0;
    /* loop will make board blink with colors forever! */
    while (1) {
      waitFor(100000);
      GPIO_PORTF_DATA_R = (++counter & 0b1110) % 16;
      waitFor(100000);
    }

    return 0;
}

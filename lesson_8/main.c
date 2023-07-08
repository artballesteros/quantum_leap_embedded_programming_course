#include "tm4c123gh6pm.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)
#define LED_RESET 0

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
    
    SYSCTL_RCGCGPIO_R  |= (1U << 5); /* enable clock for GPIO port F */
    SYSCTL_GPIOHBCTL_R |= (1U << 5); /* enable use of Advance High Performance Bus (AHB) to GPIOF, default (APB) is slower */
    
    GPIO_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIO_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
    
    int counter = 0;
    /* loop will make board blink with colors forever! */
    while (1) {
      waitFor(100000);
      //GPIO_PORTF_AHB_DATA_R = (++counter & 0b1110) % 16; 
      // ^ still better than below; uses 3 less instructions :) and doesn't require reset
      // since it just overwrites previously set bits
      //GPIO_PORTF_AHB_DATA_R = LED_RESET;
      //waitFor(100000);
      /*
      GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
      waitFor(1000000);
      GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
      waitFor(1000000);
      GPIO_PORTF_AHB_DATA_BITS_R[LED_GREEN] = LED_GREEN;
      
      attempt to use the hardwares address line masking to reduce load-modify-store cycle to
      just load-store; read page 654 of datasheet for more info. Below uses
      less instructions than above 3 array reads/writes.
      
      Note that because the previously set bits aren't erased, the colors we
      see won't be red-green-blue but red-(red+green)+(red+green+blue). This
      confused me for some time so I left note here to remind myself. 

      If you run run the code now, the colors will visibly change because we now
      reset the LED using the special address mask at GPIO_PORTF_DATA_R (0x4002534C)

      UPDATE: replaced above RESET with belows.. which is personally more elegant
      */

      int LED_VALUE = ++counter & 0b1110;
      GPIO_PORTF_AHB_DATA_BITS_R[LED_VALUE] = LED_VALUE;
      waitFor(100000);
      GPIO_PORTF_AHB_DATA_BITS_R[LED_VALUE] = LED_RESET;
      waitFor(100000);
    }

    return 0;
}

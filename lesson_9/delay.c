#include "delay.h"

void waitFor(int delay) {
  int volatile counter = 0; // ensures the compiler doesn't optimize away this wait
  while (counter < delay)   // by requiring that it always reads counter value from 
    counter++;              // memory and not some register
}
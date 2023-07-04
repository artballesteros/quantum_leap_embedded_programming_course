
#define RCGCGPIO (*((unsigned int *)0x400fe608U)) // clock gating control

#define GPIOF_BASE 0x40025000U
#define GPIOF_DIR  (*((unsigned int *)(GPIOF_BASE + 0x400U)))
#define GPIOF_DEN  (*((unsigned int *)(GPIOF_BASE + 0x51CU)))
#define GPIOF_DATA (*((unsigned int *)(GPIOF_BASE + 0X3FCU)))

void waitFor (int delay) {
  int counter = 0;
  while (counter < delay)
    counter++;
}

int main() {
    
    RCGCGPIO = 0x20U;
    GPIOF_DIR = 0x0EU;
    GPIOF_DEN = 0x0EU;
    
    int counter = 0;
    /* loop will make board blink with colors forever! */
    while (1) {
      waitFor(1000000);
      GPIOF_DATA = (++counter & 0b1110) % 16;
      waitFor(1000000);
    }

    return 0;
}

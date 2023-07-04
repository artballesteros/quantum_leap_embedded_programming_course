
#define GPIO_PORT7_GATE_CLK ((unsigned int *)0x400fe608U)
#define GPIOF_PIN_DIR ((unsigned int *)0x40025400U)
#define DIGITAL_FN_REG ((unsigned int *)0x4002551CU)
#define LED_REG ((unsigned int *)0x400253fcU)

void waitFor (int delay) {
  int counter = 0;
  while (counter < delay)
    counter++;
}

int main() {
    
    *GPIO_PORT7_GATE_CLK = 0x20U;
    *GPIOF_PIN_DIR = 0x0eU;
    *DIGITAL_FN_REG = 0x0eU;
    
  
    int counter = 0;
    while (1) {
      waitFor(1000000);
      *LED_REG = (++counter & 0b1110) % 16;
      waitFor(1000000);
    }

    return 0;
}

/* startup code for TM4C MCU */

/* set to const to ensure that this vector table starts at 0x0 in read-only 
memory (ROM); stays in RAM otherwise. */ 
int const __vector_table[] @ ".intvec" = { 
    0x20004000,
    0x9
};
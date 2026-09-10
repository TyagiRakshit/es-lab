#include <stdint.h>
#include "LPC17xx.h"

int main(void)
{
    // Use 'volatile' so the compiler doesn't optimize away the delay loops
    volatile uint32_t delay;//Prevents Keil/GCC compilers from deleting the empty for loops during build optimization.
    SystemInit();
    SystemCoreClockUpdate();

    // Configure P0.4 as GPIO
    LPC_PINCON->PINSEL0 &= ~(3 << 8); 

    // Set P0.4 direction as output
    LPC_GPIO0->FIODIR |= (1 << 4);

    while(1)
    {
        LPC_GPIO0->FIOSET = (1 << 4);                // Set P0.4 HIGH
        for (delay = 0; delay < 100000; delay++);    // Delay

        LPC_GPIO0->FIOCLR = (1 << 4);                // Set P0.4 LOW
        for (delay = 0; delay < 100000; delay++);    // Delay
    }

    return 0;
}
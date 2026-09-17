#include <stdint.h>
#include "LPC17xx.h"

// Approximate delay function
void delay_ms(uint32_t count)
{
    volatile uint32_t i, j;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < 6000; j++); 
    }
}

int main(void)
{
    uint8_t count = 0;

    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL0 &= ~(0xFFFF); 

    LPC_PINCON->PINSEL3 &= ~(3 << 14);

    LPC_GPIO0->FIODIR |= (0xFF << 0);   // Set P0.0 to P0.7 as Outputs
    LPC_GPIO1->FIODIR &= ~(1 << 23);   // Set P1.23 as Input

    LPC_PINCON->PINMODE3 &= ~(3 << 14);

    while (1)
    {
        LPC_GPIO0->FIOCLR = (0xFF << 0);

        LPC_GPIO0->FIOSET = (count << 0);
        if ((LPC_GPIO1->FIOPIN & (1 << 23)) != 0)
        {
            count++; // Up Counter
        }
        else
        {
            count--; // Down Counter
        }

        // Delay between count steps
        delay_ms(250);
    }

    return 0;
}
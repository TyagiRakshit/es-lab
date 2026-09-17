#include <stdint.h>
#include "LPC17xx.h"

void delay_ms(uint32_t count)
{
    volatile uint32_t i, j;
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < 6000; j++); // Approximate millisecond delay
    }
}

int main(void)
{
    uint8_t count = 0;

    SystemInit();
    SystemCoreClockUpdate();
    LPC_PINCON->PINSEL0 &= ~(0xFFFF); 
    LPC_GPIO0->FIODIR |= (0xFF << 0); // Sets lowest 8 bits as outputs

    while (1)
    {
        LPC_GPIO0->FIOCLR = (0xFF << 0);
        LPC_GPIO0->FIOSET = (count << 0);
        delay_ms(200);
        count++;
    }

    return 0;
}
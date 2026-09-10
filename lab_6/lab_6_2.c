//Write an embedded C program to turn ON the LED when the switch connected to P2.12 is pressed and turn OFF the LED when the switch is released.
#include <stdint.h>
#include "LPC17xx.h"

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();
    LPC_PINCON->PINSEL0 &= ~(3 << 8);    // P0.4 as GPIO
    LPC_PINCON->PINSEL4 &= ~(3 << 24);   // P2.12 as GPIO
    LPC_GPIO0->FIODIR |= (1 << 4);       // P0.4 as OUTPUT LED
    LPC_GPIO2->FIODIR &= ~(1 << 12);     // P2.12 as INPUT Switch
    LPC_PINCON->PINMODE4 &= ~(3 << 24);

    while (1)
    {
        if ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0)
        {
            LPC_GPIO0->FIOSET = (1 << 4); // Turn LED ON
        }
        else
        {
            LPC_GPIO0->FIOCLR = (1 << 4); // Turn LED OFF
        }
    }

    return 0;
}
//WE USED LPC_GPIO0->FIODIR |= (1 << 4); INSTEAD OF LPC_GPIO0->FIODIR = 1 << 4; AS WITHOUT THE (|=) IT WOUDD OVERWRITE ALL THE OTHER 31 PINS OUT OF 32 BIT TO BE ZERO 
//use |= (to set bits) and &= ~ (to clear bits) whenever you want to change a specific pin without affecting others.
//Use = only when you intentionally want to reset/initialize every pin on the port at once.
//LPC_PINCON->PINSEL0 = 0;
//LPC_PINCON->PINSEL4 = 0;
//What it does: Sets all 32 bits of PINSEL0 and PINSEL4 to 0.
//The Risk: In the LPC1768, every pin gets 2 bits in a PINSEL register to select its function (00 = GPIO, 01 = Primary alt function, 10 = Second alt function, etc.).
//Writing = 0 forces all 16 pins associated with that register back to standard GPIO mode. If you configured UART, SPI, or PWM on another pin in that port earlier in your code,
//PINSEL0 = 0 will instantly disconnect those peripherals and break them.
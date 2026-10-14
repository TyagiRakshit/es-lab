#include <LPC17xx.h>

unsigned char SEVENSEG[2] = {0x3F, 0x06};

unsigned int SEGSEL[4] =
{
    0xF87FFFFF,
    0xF8FFFFFF,
    0xF97FFFFF,
    0xF9FFFFFF
};

void delay(void)
{
    volatile unsigned int j;
    for(j = 0; j < 1000; j++);
}

int main(void)
{
    unsigned int i, ring = 0, count = 0;

    SystemInit();
    SystemCoreClockUpdate();

    // P0.4-P0.11: segment output
    LPC_PINCON->PINSEL0 &= 0xFF0000FF;
    LPC_GPIO0->FIODIR |= 0x00000FF0;

    // P1.23-P1.26: digit selection
    LPC_PINCON->PINSEL3 &= 0xFFC03FFF;
    LPC_GPIO1->FIODIR |= 0x07800000;

    while(1)
    {
        for(i = 0; i < 4; i++)
        {
            LPC_GPIO1->FIOPIN = SEGSEL[i];

            if(i == ring)
                LPC_GPIO0->FIOPIN = SEVENSEG[1] << 4;
            else
                LPC_GPIO0->FIOPIN = SEVENSEG[0] << 4;

            delay();
        }

        count++;

        if(count >= 250)
        {
            count = 0;
            ring++;

            if(ring == 4)
                ring = 0;
        }
    }
}

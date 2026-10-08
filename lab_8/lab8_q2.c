#include <LPC17xx.h>

#define FIRSTSEG   0xF87FFFFF
#define SECONDSEG  0xF8FFFFFF
#define THIRDSEG   0xF97FFFFF
#define FOURTHSEG  0xF9FFFFFF

unsigned int digit_count = 0;
unsigned int count = 0;

unsigned char value[4] = {0, 0, 0, 1};

unsigned char binaryseg[2] =
{
    0x3F,
    0x06
};

void delay(void)
{
    int i;

    for(i = 0; i < 10000; i++);
}

void increment(void)
{
    unsigned char temp;

    temp = value[3];

    value[3] = value[2];
    value[2] = value[1];
    value[1] = value[0];
    value[0] = temp;
}

void display(void)
{
    unsigned int select;
    unsigned int seg;

    if(digit_count == 0)
        select = FIRSTSEG;

    if(digit_count == 1)
        select = SECONDSEG;

    if(digit_count == 2)
        select = THIRDSEG;

    if(digit_count == 3)
        select = FOURTHSEG;

    /* Digit selection */
    LPC_GPIO1->FIOPIN = select;

    /* Segment data */
    seg = binaryseg[value[digit_count]];

    LPC_GPIO0->FIOPIN = seg << 4;
}

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    /* P0.4 - P0.11 GPIO */
    LPC_PINCON->PINSEL0 &= 0x0000FFFF;

    /* P1.23 - P1.26 GPIO */
    LPC_PINCON->PINSEL3 &= 0xC03FFFFF;

    /* P0.4 - P0.11 OUTPUT */
    LPC_GPIO0->FIODIR |= 0x00000FF0;

    /* P1.23 - P1.26 OUTPUT */
    LPC_GPIO1->FIODIR |= 0x07800000;

    while(1)
    {
        digit_count = 0;

        while(digit_count < 4)
        {
            display();

            delay();

            digit_count++;
        }

        count++;

        if(count == 500)
        {
            count = 0;
            increment();
        }
    }
}

#include <LPC17xx.h>

#define SEG_MASK 0x00000FF0
#define DIG_MASK 0x07800000

unsigned char seg_code[10] =
{
    0x3F,   // 0
    0x06,   // 1
    0x5B,   // 2
    0x4F,   // 3
    0x66,   // 4
    0x6D,   // 5
    0x7D,   // 6
    0x07,   // 7
    0x7F,   // 8
    0x6F    // 9
};

unsigned int count = 0;
unsigned int i;

void delay_1ms(void)
{
    for(i = 0; i < 12000; i++);
}

void display_digit(unsigned char digit, unsigned char position)
{
    unsigned int seg;
    
    LPC_GPIO1->FIOCLR = DIG_MASK;

    LPC_GPIO0->FIOCLR = SEG_MASK;
    seg = ((unsigned int)seg_code[digit]) << 4;
    LPC_GPIO0->FIOSET = seg;
    if(position == 0)
        LPC_GPIO1->FIOSET = (1 << 23);

    else if(position == 1)
        LPC_GPIO1->FIOSET = (1 << 24);

    else if(position == 2)
        LPC_GPIO1->FIOSET = (1 << 25);

    else if(position == 3)
        LPC_GPIO1->FIOSET = (1 << 26);

    delay_1ms();

    LPC_GPIO1->FIOCLR = DIG_MASK;
}

void display_number(unsigned int num)
{
    unsigned char d0, d1, d2, d3;
    unsigned int j;

    d0 = num / 1000;
    d1 = (num / 100) % 10;
    d2 = (num / 10) % 10;
    d3 = num % 10;

    for(j = 0; j < 50; j++)
    {
        display_digit(d0, 0);
        display_digit(d1, 1);
        display_digit(d2, 2);
        display_digit(d3, 3);
    }
}

int main(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL0 &= 0xFF0000FF;

    LPC_PINCON->PINSEL1 &= ~(3 << 10);

    /* P1.23-P1.26 as GPIO */
    LPC_PINCON->PINSEL3 &= ~(0xFF << 14);

    /* Segment pins as output */
    LPC_GPIO0->FIODIR |= SEG_MASK;

    /* Switch P0.21 as input */
    LPC_GPIO0->FIODIR &= ~(1 << 21);

    /* Digit select pins as output */
    LPC_GPIO1->FIODIR |= DIG_MASK;

    /* Initially turn everything OFF */
    LPC_GPIO0->FIOCLR = SEG_MASK;
    LPC_GPIO1->FIOCLR = DIG_MASK;

    while(1)
    {
        /* Display current count for approximately 1 second */
        display_number(count);

        /* Check switch */
        if(LPC_GPIO0->FIOPIN & (1 << 21))
        {
            /* UP counter */
            if(count >= 9999)
                count = 0;
            else
                count++;
        }
        else
        {
            /* DOWN counter */
            if(count == 0)
                count = 9999;
            else
                count--;
        }
    }
}
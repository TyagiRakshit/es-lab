#include <LPC17xx.h>

unsigned char seg[10] =
{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

unsigned int mask[4] =
{0xF87FFFFF,0xF8FFFFFF,0xF97FFFFF,0xF9FFFFFF};

unsigned int num=0, n, i, j, k;

int main()
{
    SystemInit();
    SystemCoreClockUpdate();

    LPC_PINCON->PINSEL0 &= 0xFF0000FF;
    LPC_PINCON->PINSEL3 &= 0xFFC03FFF;
    LPC_PINCON->PINSEL4 &= ~(3<<24);

    LPC_GPIO0->FIODIR |= 0xFF0;
    LPC_GPIO1->FIODIR |= 0x07800000;
    LPC_GPIO2->FIODIR &= ~(1<<12);

    while(1)
    {
        for(k=0;k<250;k++)
        {
            n=num;

            for(i=0;i<4;i++)
            {
                LPC_GPIO1->FIOPIN = mask[i];
                LPC_GPIO0->FIOPIN = seg[n%10]<<4;

                for(j=0;j<1000;j++);

                LPC_GPIO0->FIOCLR = 0xFF0;
                n=n/10;
            }
        }

        if(LPC_GPIO2->FIOPIN & (1<<12))
            num=(num+1)%10000;
        else
            num=(num+9999)%10000;
    }
}

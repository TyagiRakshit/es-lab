#include <LPC17xx.h>

// Global variables
unsigned long int temp1 = 0, temp2 = 0, i;
// flag1 = 0: Command mode (RS = 0)
// flag1 = 1: Data mode    (RS = 1)
unsigned char flag1 = 0, flag2 = 0;

unsigned long int init_command[] = {0x30,0x30,0x30,0x20,0x28,0x0C,0x06,0x01,0x80};

// Function declarations
void port_write(void);
void lcd_write(void);
void delay(volatile unsigned int);

int main(void)
{
    char msg[] = "debrato";      // string to display

    SystemInit();
    SystemCoreClockUpdate();

    // P0.16 - P0.31 as GPIO (covers P0.23-P0.28)
    LPC_PINCON->PINSEL1 = 0;

    // P0.23-P0.26: LCD D4-D7, P0.27: RS, P0.28: EN
    LPC_GPIO0->FIODIR = (1 << 27) | (1 << 28) | (0xF << 23);

    delay(300000);               // power-up wait

    flag1 = 0;                   // command mode
    for (i = 0; i < 9; i++)
    {
        temp1 = init_command[i];
        lcd_write();
    }

    flag1 = 1;                   // data mode (RS = 1)
    i = 0;
    while (msg[i] != '\0')
    {
        temp1 = msg[i];
        lcd_write();
        i++;
    }

    while (1);                   // stop here
}

// Write a 4-bit value (in temp2) to LCD D4-D7
void port_write(void)
{
    LPC_GPIO0->FIOPIN = temp2 << 23;     // put nibble on P0.23-P0.26

    if (flag1 == 0)
        LPC_GPIO0->FIOCLR = 1 << 27;     // RS = 0: command
    else
        LPC_GPIO0->FIOSET = 1 << 27;     // RS = 1: data

    LPC_GPIO0->FIOSET = 1 << 28;         // EN = 1
    delay(50);                           // keep EN high briefly
    LPC_GPIO0->FIOCLR = 1 << 28;         // EN = 0
    delay(30000);                        // let the LCD process
}

// Send a byte (command or character) from temp1
void lcd_write(void)
{
    // Only the upper nibble is sent for the 0x30 / 0x20 init commands
    flag2 = (flag1 == 1) ? 0 : ((temp1 == 0x30) || (temp1 == 0x20)) ? 1 : 0;

    temp2 = (temp1 >> 4) & 0x0F;         // upper nibble
    port_write();

    if (flag2 == 0)
    {
        temp2 = temp1 & 0x0F;            // lower nibble
        port_write();
    }
}

// Software delay: volatile stops the compiler from optimizing the loop away
void delay(volatile unsigned int r1)
{
    volatile unsigned int r;
    for (r = 0; r < r1; r++);
}
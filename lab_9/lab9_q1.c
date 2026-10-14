#include <LPC17xx.h>
#include <stdio.h>
#include "AN_LCD.h"

char keymap[4][4] =
{
    {'1','2','3','+'},
    {'4','5','6','-'},
    {'7','8','9','='},
    {'C','0','D','E'}
};

/* Read one key from the 4x4 keyboard */
char getkey(void)
{
    unsigned int row, col;
    char key;

    while(1)
    {
        for(row = 0; row < 4; row++)
        {
            LPC_GPIO2->FIOCLR = (0xF << 10);
            LPC_GPIO2->FIOSET = (1 << (10 + row));

            for(col = 0; col < 4; col++)
            {
                if(LPC_GPIO1->FIOPIN & (1 << (23 + col)))
                {
                    key = keymap[row][col];

                    // Wait until key is released
                    while(LPC_GPIO1->FIOPIN &
                          (1 << (23 + col)));

                    return key;
                }
            }
        }
    }
}

int main(void)
{
    char key, op;
    int A, B, result;
    char output[17];

    SystemInit();
    SystemCoreClockUpdate();

    // Keyboard GPIO configuration
    LPC_PINCON->PINSEL3 &= 0xFFC03FFF;
    LPC_PINCON->PINSEL4 &= 0xF00FFFFF;

    // Rows: output
    LPC_GPIO2->FIODIR |= (0xF << 10);

    // Columns: input
    LPC_GPIO1->FIODIR &= ~(0xF << 23);

    lcd_init();

    while(1)
    {
        // Read first digit
        do {
            key = getkey();
        } while(key < '0' || key > '9');

        A = key - '0';

        // Read operator
        do {
            op = getkey();
        } while(op != '+' && op != '-');

        // Read second digit
        do {
            key = getkey();
        } while(key < '0' || key > '9');

        B = key - '0';

        // Wait for '='
        do {
            key = getkey();
        } while(key != '=');

        // Calculate result
        if(op == '+')
            result = A + B;
        else
            result = A - B;

        // Display expression and result on LCD
        sprintf(output, "%d%c%d=%d", A, op, B, result);

        temp1 = 0x01;       // Clear LCD
        lcd_com();
        delay_lcd(800);

        lcd_puts((unsigned char *)output);
    }
}

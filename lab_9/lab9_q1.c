#include <LPC17xx.h>

#define LCD_DATA 0x07800000
#define RS       0x08000000
#define EN       0x10000000

unsigned int i;

void delay(unsigned int x)
{
    unsigned int j;
    for(j = 0; j < x; j++);
}

void lcd_pulse(void)
{
    LPC_GPIO0->FIOSET = EN;
    delay(1000);
    LPC_GPIO0->FIOCLR = EN;
    delay(1000);
}

void lcd_cmd(unsigned char cmd)
{
    LPC_GPIO0->FIOCLR = LCD_DATA;
    LPC_GPIO0->FIOSET = ((unsigned int)cmd << 23);

    LPC_GPIO0->FIOCLR = RS;
    lcd_pulse();
    delay(5000);
}

void lcd_data(unsigned char data)
{
    LPC_GPIO0->FIOCLR = LCD_DATA;
    LPC_GPIO0->FIOSET = ((unsigned int)data << 23);

    LPC_GPIO0->FIOSET = RS;
    lcd_pulse();
    delay(5000);
}

void lcd_init(void)
{
    LPC_GPIO0->FIODIR |= LCD_DATA | RS | EN;

    delay(20000);

    lcd_cmd(0x30);
    lcd_cmd(0x30);
    lcd_cmd(0x30);
    lcd_cmd(0x20);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    lcd_cmd(0x01);
    lcd_cmd(0x80);
}

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}

/* 4x4 keypad */
unsigned char keypad(void)
{
    unsigned char row, col;

    unsigned char key[4][4] =
    {
        {'1','2','3','+'},
        {'4','5','6','-'},
        {'7','8','9','='},
        {'C','0','E','D'}
    };

    while(1)
    {
        for(row = 0; row < 4; row++)
        {
            /* Set all rows high */
            LPC_GPIO2->FIOSET = 0x000000F0;

            /* Make one row LOW */
            LPC_GPIO2->FIOCLR = (1 << (4 + row));

            delay(100);

            /* Check columns */
            if(!(LPC_GPIO2->FIOPIN & (1 << 0)))
                col = 0;
            else if(!(LPC_GPIO2->FIOPIN & (1 << 1)))
                col = 1;
            else if(!(LPC_GPIO2->FIOPIN & (1 << 2)))
                col = 2;
            else if(!(LPC_GPIO2->FIOPIN & (1 << 3)))
                col = 3;
            else
                continue;

            delay(20000);

            while(!(LPC_GPIO2->FIOPIN & 0x0000000F));

            return key[row][col];
        }
    }
}

int main(void)
{
    unsigned char A, B, op, eq;
    int result;
    char buffer[16];
    int n, temp;

    SystemInit();
    SystemCoreClockUpdate();

    /* LCD pins */
    LPC_PINCON->PINSEL1 &= ~(0xFFFFFFFF);

    /* Keypad pins P2.0-P2.7 as GPIO */
    LPC_PINCON->PINSEL4 &= ~(0x0000FFFF);

    /* P2.4-P2.7 = rows OUTPUT */
    LPC_GPIO2->FIODIR |= 0x000000F0;

    /* P2.0-P2.3 = columns INPUT */
    LPC_GPIO2->FIODIR &= ~(0x0000000F);

    lcd_init();

    lcd_string("Enter:");

    /* Read A */
    A = keypad();
    lcd_data(A);

    /* Read operator */
    op = keypad();
    lcd_data(op);

    /* Read B */
    B = keypad();
    lcd_data(B);

    /* Read '=' */
    eq = keypad();
    lcd_data(eq);

    /* Convert ASCII to number */
    A = A - '0';
    B = B - '0';

    /* Perform operation */
    if(op == '+')
        result = A + B;
    else
        result = A - B;

    /* Move LCD cursor to second line */
    lcd_cmd(0xC0);

    lcd_string("Result = ");

    /* Display result */
    if(result < 0)
    {
        lcd_data('-');
        result = -result;
    }

    if(result >= 10)
    {
        temp = result / 10;
        lcd_data(temp + '0');

        result = result % 10;
    }

    lcd_data(result + '0');

    while(1);
}

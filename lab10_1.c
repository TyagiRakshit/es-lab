#include <LPC17xx.h>
#include <stdio.h>
#include "AN_LCD.h"

// Function to read an ADC channel
unsigned int ADC_Read(unsigned int channel)
{
    unsigned long value;

    // Select channel, enable ADC, start conversion
    LPC_ADC->ADCR = (1 << channel) | (1 << 21) | (1 << 24);

    // Wait until conversion is complete (DONE = 1)
    do
    {
        value = LPC_ADC->ADGDR;
    } while(!(value & (1UL << 31)));

    // Extract 12-bit digital value
    return (value >> 4) & 0xFFF;
}

int main(void)
{
    unsigned int adc4, adc5;
    int difference;
    char msg[17];

    SystemInit();
    SystemCoreClockUpdate();

    // Power ON ADC
    LPC_SC->PCONP |= (1 << 12);

    // Configure P1.30 and P1.31 as AD0.4 and AD0.5
    LPC_PINCON->PINSEL3 |= 0xF0000000;

    // Initialize LCD
    lcd_init();

    while(1)
    {
        // Read ADC channel 4
        adc4 = ADC_Read(4);

        // Read ADC channel 5
        adc5 = ADC_Read(5);

        // Calculate signed digital difference
        difference = (int)adc4 - (int)adc5;

        // Convert result to string
        sprintf(msg, "Diff: %d       ", difference);

        // Display on first line of LCD
        temp1 = 0x80;
        lcd_com();
        delay_lcd(800);
        lcd_puts((unsigned char *)msg);
    }
}

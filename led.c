#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sfr/regtc1797.sfr>
#if 0
void led_init(void)
{
    P3_IOCR0.U = 0x80808080;
    P3_IOCR4.U = 0x80808080;
}

void led_on_all(void)
{
    P3_OUT.U &= ~(0xFF);
}

void led_off_all(void)
{
    P3_OUT.U |= (0xFF);
}

void led_on(int led_no)
{
    P3_OUT.U &= ~(1 << led_no);
}

void led_off(int led_no)
{
    P3_OUT.U |= (1 << led_no);
}

void led_toggle(int led_no)
{
    P3_OUT.U ^= (1 << led_no);
}
#endif

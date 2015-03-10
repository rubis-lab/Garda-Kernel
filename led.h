#ifndef __LED_H__
#define __LED_H__
#include <sfr/regtc1797.sfr>
#if 0
void led_init(void);
void led_on_all(void);
void led_off_all(void);
void led_on(int led_no);
void led_off(int led_no);
void led_toggle(int led_no);
#endif
inline void led_init(void)
{
    P3_IOCR0.U = 0x80808080;
    P3_IOCR4.U = 0x80808080;
}

inline void led_on_all(void)
{
    P3_OUT.U &= ~(0xFF);
}

inline void led_off_all(void)
{
    P3_OUT.U |= (0xFF);
}

inline void led_on(int led_no)
{
    P3_OUT.U &= ~(1 << led_no);
}

inline void led_off(int led_no)
{
    P3_OUT.U |= (1 << led_no);
}

inline void led_toggle(int led_no)
{
    P3_OUT.U ^= (1 << led_no);
}

#endif

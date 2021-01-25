#include <msp430.h> 

/**
 * 练习104 红色LED灯闪烁的实验
 *
 */
void main(void)
{
    unsigned int u16_deley;

    //停用看门狗
	WDTCTL = WDTPW | WDTHOLD;
    //设置P1.0的方向为输出
    P1DIR = 0X01;

    while(1)
    {
        //设置P1.0输出高电平,点亮LED
        P1OUT = 0x01;
        //软件延时
        for(u16_deley=0;u16_deley<50000;u16_deley++);
        //设置P1.0输出低电平,熄灭LED
        P1OUT = 0x00;
        //软件延时
        for(u16_deley=0;u16_deley<50000;u16_deley++);
    }
}

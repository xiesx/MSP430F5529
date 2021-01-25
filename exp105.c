#include <msp430.h> 

/**
 * 练习105 绿色LED灯闪烁的实验
 *
 * 引脚P4.7接有绿色LED
 *
 */
void main(void)
{
    unsigned int u16_deley;

    //停用看门狗
	WDTCTL = WDTPW | WDTHOLD;
    //设置P4.7的方向为输出
    P4DIR = 0x80;

    while(1)
    {
        //设置P4.7输出高电平,点亮LED
        P4OUT = 0x80;
        //软件延时
        for(u16_deley=0;u16_deley<50000;u16_deley++);
        //设置P4.7输出低电平,熄灭LED
        P4OUT = 0x00;
        //软件延时
        for(u16_deley=0;u16_deley<50000;u16_deley++);
    }
}

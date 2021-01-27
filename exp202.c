#include <msp430.h> 

/**
 * 练习202 演示按键的输入操作
 *
 * MSP-EXP430F5529LP：
 * 两个用户按键:P2.1->S1;P1.1->S2
 * 两个用户LED:P1.0->LED1;P4.7->LED2
 *
 * S2控制LED1；
 */
void main(void)
{
    //停用看门狗
	WDTCTL = WDTPW | WDTHOLD;

	//设置P1.1的方向为输入
	//xxxx xx0x -> 1111 1101   ~
    P1DIR &= 0xFD;
    //启用P1.1的内部上下拉电阻
    P1REN |= 0x02;
    //设置为上拉电阻
    //xxxx xx1x  0000 0010
    P1OUT |= 0x02;

    //设置P1.0的方向为输出，控制红色LED
    // xxxx xxx1  0000 0001
    P1DIR |= 0x01;

    while(1)
    {
        //读取输入值,如果是低电平,则点亮LED
        if((P1IN&0x02)==0x00)
        {
            //设置P1.0输出高电平,点亮LED
            // xxxx xxx1  0000 0001
            P1OUT |= 0x01;
        }
        else
        {
            //设置P1.0输出低电平,熄灭LED
            // xxxx xxx1  ~(0000 0001)
            P1OUT = P1OUT & ~(0x01);
        }
    }
}

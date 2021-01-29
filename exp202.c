#include <msp430.h> 

/**
 * 练习202 演示按键的输入操作
 *
 * MSP-EXP430F5529LP：
 * 两个用户按键:P2.1->S1;P1.1->S2
 * 两个用户LED:P1.0->LED1;P4.7->LED2
 *
 * S2控制LED1；(用到了同一个IO口，不能简单的用=来操作控制)
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


//改进版本:
#if 0
void main(void)
{
    //停用看门狗
    WDTCTL = WDTPW | WDTHOLD;

    //设置P1.1为输入
    //P1DIR = P1DIR & ~BIT1;
    //P1DIR & ~BIT1 -->屏蔽无关位,指定位清零  p1有8个引脚，即8个比特位，
    //   P1. 7654 3210
    // P1DIR xxxx xxxx
    // BIT1  0000 0010
    //~BIT1  1111 1101
    //   &   xxxx xx0x   --》只是把特定的比特位清零
    P1DIR &= ~BIT1;

    //启用P1.1的内部上下拉电阻,且设置为上拉
    //P1REN = P1REN | BIT1;
    //P1REN | BIT1 -->屏蔽无关位,指定位置1； p1有8个引脚，即8个比特位，
    //   P1. 7654 3210
    // P1REN xxxx xxxx
    // BIT1  0000 0010
    //   |   xxxx xx1x   --》只是把特定的比特位置1
    P1REN |= BIT1;
    P1OUT |= BIT1;

    //设置P1.0为输出，控制红色LED
    P1DIR |= BIT0;
    //初始化灯的状态，熄灭
    P1OUT &= ~BIT0;

    while(1)
    {
        //读取引脚P1.1,如果是低电平,则点亮LED
        // P1IN & BIT1 -->屏蔽无关位,  p1有8个引脚，即8个比特位，
        //   P1. 7654 3210
        // P1IN  xxxx xxxx
        // BIT1  0000 0010
        //   &   0000 00x0  --》只保留P1.1的输入值
        //此时，
        //P1.1为高电平(按键未动), 0000 0010 = BIT1
        //P1.1为低电平(按键按下), 0000 0000 = 0x00
        if((P1IN&BIT1)==0x00)
        {
            //设置P1.0输出高电平,点亮LED
            P1OUT |= BIT0;
        }
        else
        {
            //设置P1.0输出低电平,熄灭LED
            P1OUT &= ~(BIT0);
        }
    }
}


#endif

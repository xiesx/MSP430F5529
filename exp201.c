#include <msp430.h> 

/**
 * 练习201 演示按键的输入操作
 *
 * MSP-EXP430F5529LP上有两个用户按键:P2.1->S1;P1.1->S2
 */
void main(void)
{
    //停用看门狗
	WDTCTL = WDTPW | WDTHOLD;
    //设置P1.1的方向为输入
    P1DIR = 0x00;
    P1REN = 0x02;
    P1OUT = 0x02;

    //设置P4.7的方向为输出，控制绿色LED
    P4DIR = 0x80;

    while(1)
    {
        //读取输入值,如果是低电平,则点亮LED
        if((P1IN&0x02)==0x00)
        {
            //设置P4.7输出高电平,点亮LED
            P4OUT = 0x80;
        }
        else
        {
            //设置P4.7输出低电平,熄灭LED
              P4OUT = 0x00;
        }
    }
}

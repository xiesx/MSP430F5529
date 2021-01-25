#include <msp430.h> 

/**
 * 练习102- 红色LED的点亮和熄灭
 *
 */

int main(void)
{
  //关闭看门狗
  WDTCTL = WDTPW | WDTHOLD;

  //设置P1.0为输出
  P1DIR = 0X01;
  //设置P1.0输出高电平,点亮LED
  P1OUT = 0x01;
  //设置P1.0输出低电平, 熄灭LED
  P1OUT = 0x00;
  //设置P1.0输出高电平,点亮LED
  P1OUT = 0x01;

 return 0;
}


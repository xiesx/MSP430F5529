#include <msp430.h> 

/**
 * 练习103- 绿色LED的点亮和熄灭
 *
 */

int main(void)
{
  //关闭看门狗
  WDTCTL = WDTPW | WDTHOLD;

  //设置P4.7为输出
  P4DIR = 0X80;
  //设置P4.7输出高电平,点亮LED
  P4OUT = 0x80;
  //设置P4.7输出低电平, 熄灭LED
  P4OUT = 0x00;
  //设置P4.7输出高电平,点亮LED
  P4OUT = 0x80;

 return 0;
}


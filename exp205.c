#include <msp430.h> 

/**
 * 练习205 按键控制LED灯闪烁的速度
 *
 * MSP-EXP430F5529LP：
 * 两个用户按键:P2.1->S1;P1.1->S2
 * 两个用户LED:P1.0->LED1;P4.7->LED2
 *
 * 上电后LED1闪烁；通过按键S1，S2调整闪烁的频率；（8种闪烁的频率）
 * 按键S1,闪烁的速度加快，到最快时，回到最慢；
 * 按键S2,闪烁的速度变慢，到最慢时，回到最快；
 *
 * 思考:
 * 有哪些操作可以提取成函数的？
 */

unsigned int const u16DelayTable[]={3000,5000,8000,10000,15000,30000,50000,60000};

void main(void)
{
    unsigned int u16_deley_temp;
    unsigned int u16_deley_config;
    unsigned char u8_config_index;

    //停用看门狗
    WDTCTL = WDTPW | WDTHOLD;

    //设置P1.1为输入
    P1DIR &= ~BIT1;

    //启用P1.1的内部上下拉电阻,且设置为上拉
    P1REN |= BIT1;
    P1OUT |= BIT1;

    //设置P2.1为输入
    P2DIR &= ~BIT1;

    //启用P2.1的内部上下拉电阻,且设置为上拉
    P2REN |= BIT1;
    P2OUT |= BIT1;

    //设置P1.0为输出
    P1DIR |= BIT0;
    //初始化灯的状态，熄灭
    P1OUT &= ~BIT0;


    u8_config_index = 4;
    u16_deley_config = u16DelayTable[u8_config_index];

    while(1)
    {
        //读取按键S2(P1.1)
        if((P1IN&BIT1)==0x00)
        {
            __delay_cycles(20000);  //20ms延时
            if((P1IN&BIT1)==0x00)
            {
                //一共8给档,下标对应0-7;
                //如果已经是7,则从0开始；不是话，加1档
                if(u8_config_index == 7)
                {
                    u8_config_index=0;
                }
                else
                {
                    u8_config_index++;
                }

                u16_deley_config = u16DelayTable[u8_config_index];

                //等待按键释放
                while((P1IN&BIT1)==0x00);
            }
        }

        //读取按键S1(P2.1)
        if((P2IN&BIT1)==0x00)
        {
            __delay_cycles(20000);  //20ms延时
            if((P2IN&BIT1)==0x00)
            {
                //一共8给档,下标对应0-7;
                //如果已经是0,则回到7开始；不是话，减1档
                if(u8_config_index == 0)
                {
                    u8_config_index=7;
                }
                else
                {
                    u8_config_index--;
                }

                u16_deley_config = u16DelayTable[u8_config_index];

                //等待按键释放
                while((P2IN&BIT1)==0x00);
            }
        }

        //LED以特定的参数进行闪烁控制
        P1OUT ^= BIT0;
        for(u16_deley_temp=0;u16_deley_temp<u16_deley_config;u16_deley_temp++);

    }
}

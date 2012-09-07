#include <stm32f10x_cl.h>

volatile uint32_t flag ;

void SysTick_Handler(void) {
   flag = !flag;
   ITM_SendChar('0'+flag);
}

int main(void)
{
   SysTick_Config(SystemFrequency/100);
   while(1);
}

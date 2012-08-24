#include "leds.h"
#include "LPC17xx_gpio.h"
#include "timer.h"
#include "serial.h"

/************************** PRIVATE VARIABLES *************************/
//static const char* menu1 = "Hello from Feabhas  \n\r";
//static const char* menu2 = "Goodbye from Feabhas  \n\r";

static void delay(void);

int main(void)
{
  // char ch;
  // Init onboard LEDs direction to output
  FIO3DIRr |= LED_D5_MASK | LED_D6_MASK;
  FIO4DIRr |= LED_D7_MASK | LED_D8_MASK;

  // Init off-board LEDs direction to output
  FIO1DIRr |= LED_D11_MASK | LED_D21_MASK | LED_D31_MASK | LED_D41_MASK;
  
//  init_serial0();
//  putstring0(menu1);

//  Timer0Init();

  while(1)
  {
      // Toggle D5-D8   
      FIO3PINr ^= LED_D5_MASK;
      delay();
      FIO3PINr ^= LED_D6_MASK;
      delay();
      FIO4PINr ^= LED_D7_MASK;
      delay();
      FIO4PINr ^= LED_D8_MASK;
      delay();
      // Toggle D11, D21, D31, D41
      FIO1PINr ^= LED_D11_MASK;
      delay();
      FIO1PINr ^= LED_D21_MASK;
      delay();
      FIO1PINr ^= LED_D31_MASK;
      delay();
      FIO1PINr ^= LED_D41_MASK;
      delay();

    
       // alternative
//      // turn all 4 onboard leds on
//      FIO3SETr = LED_D5_MASK;
//      delay();
//      FIO3SETr = LED_D6_MASK;
//      delay();
//      FIO4SETr = LED_D7_MASK;
//      delay();
//      FIO4SETr = LED_D8_MASK;
//      delay();
//      // turn all 4 baseboard leds on
//      FIO1SETr = LED_D11_MASK;
//      delay();
//      FIO1SETr = LED_D21_MASK;
//      delay();
//      FIO1SETr = LED_D31_MASK;
//      delay();
//      FIO1SETr = LED_D41_MASK;
//      delay();
//      
//      // turn all 4 onboard leds off
//      FIO3CLRr = LED_D5_MASK;
//      delay();
//      FIO3CLRr = LED_D6_MASK;
//      delay();
//      FIO4CLRr = LED_D7_MASK;
//      delay();
//      FIO4CLRr = LED_D8_MASK;
//      delay();
//      // turn all 4 baseboard leds off
//      FIO1CLRr = LED_D11_MASK;
//      delay();
//      FIO1CLRr = LED_D21_MASK;
//      delay();
//      FIO1CLRr = LED_D31_MASK;
//      delay();
//      FIO1CLRr = LED_D41_MASK;
//      delay();      

//       ch = getchar0();
//       putchar0(ch);
//       if(ch == '#') break;  
  }
//  putstring0(menu2);
}


/*************************************************************************
 * Function Name: delay
 * Parameters: none
 *
 * Return: none
 *
 * Description: busy-wait loop
 *
 *************************************************************************/
void delay(void)
{
	volatile int i;
  for(i = 0; i < 750000; i++)
  {
    // do nothing
  }
}

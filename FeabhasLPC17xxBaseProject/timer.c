#include <intrinsics.h>
#include <stdio.h>
#include <nxp/iolpc1764.h>
#include <assert.h>
#include <stdint.h>

#include "timer.h"
#include "leds.h"
#include "nvic.h"
#include "LPC17xx_gpio.h"

#define TIMER0_TICK_PER_SEC   10
//#define TIMER0_TICK_PER_SEC   1
#define TIMER0_IN_FREQ        25000000


/*************************************************************************
 * Function Name: TMR0_IRQHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 0 interrupt handler
 *
 *************************************************************************/
void TMR0_IRQHandler (void)
{
  /* Toggle LED1 */
  FIO3PINr ^= LED_D5_MASK;

  /*clear interrupt */
  T0IR_bit.MR0INT = 1;
  /**/
  NVIC_ClrPend(NVIC_TIMER0);
}

void Timer0Init(void)
{
  
  // Enable TIM0 clocks
  PCONP_bit.PCTIM0 = 1; // enable clock

  // Init Time0
  T0TCR_bit.CE = 0;     // counting  disable
  T0TCR_bit.CR = 1;     // set reset
  T0TCR_bit.CR = 0;     // release reset
  T0CTCR_bit.CTM = 0;   // Timer Mode: every rising PCLK edge
  T0MCR_bit.MR0I = 1;   // Enable Interrupt on MR0
  T0MCR_bit.MR0R = 1;   // Enable reset on MR0
  T0MCR_bit.MR0S = 0;   // Disable stop on MR0
  // set timer 0 period
  T0PR = 18-1;
  T0MR0 = (TIMER0_IN_FREQ)/(18 * TIMER0_TICK_PER_SEC);
  // init timer 0 interrupt
  T0IR_bit.MR0INT = 1;  // clear pending interrupt
  T0TCR_bit.CE = 1;     // counting Enable
  /*Enable NVIC TMR0 Interrupt*/
  NVIC_IntEnable(NVIC_TIMER0);
  __enable_interrupt();
}

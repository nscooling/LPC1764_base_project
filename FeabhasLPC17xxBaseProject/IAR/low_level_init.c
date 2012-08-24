/**************************************************
 *
 * This module contains the function `__low_level_init', a function
 * that is called before the `main' function of the program.  Normally
 * low-level initializations - such as setting the prefered interrupt
 * level or setting the watchdog - can be performed here.
 *
 * Note that this function is called before the data segments are
 * initialized, this means that this function cannot rely on the
 * values of global or static variables.
 *
 * When this function returns zero, the startup code will inhibit the
 * initialization of the data segments. The result is faster startup,
 * the drawback is that neither global nor static data will be
 * initialized.
 *
 * Copyright 1999-2004 IAR Systems. All rights reserved.
 *
 * $Revision: 21623 $
 *
 **************************************************/
/**************************************************
 * file: low_level_init.c
 * version 1.0(Cortex-M3)
 *
 * Copyright 1995-2012 Feabhas Limited. All rights reserved
 *
 * This file is designed to work with the Feabhas Cortex-M3 board
 * using the NXP LPC1764 microprocessor
 *
 * This file configures:
 * 1) The Flash accelerator
 * 2) The clock source (external crystal @ 12MHz
 * 3) The Phase-Lock Loop (PLL) to clock the Cortex-M3 core @ 100MHz
 * 4) The Peripherial Clock at 25MHz
 * 5) The external pins to GPIO and all inputs
 *
 **************************************************/

#ifdef __cplusplus
extern "C" {
#endif
  
  
#include <nxp/iolpc1764.h>
#include <stdint.h>

#define FLASHCFGr              (*(volatile uint32_t*)0x400FC000)

#pragma language=extended
  
static void Initialise_Clock_Source_and_PLL(void);
static void Initialise_GPIO(void);

__interwork int __low_level_init(void);

__interwork int __low_level_init(void)
{
  /*==================================*/
  /*  Initialize hardware.            */
  /*==================================*/
    // Flash accelerator init
  FLASHCFGr = (0x5UL<<12) | 0x3AUL;
  // Init clock
  Initialise_Clock_Source_and_PLL();

  // Init GPIO
  Initialise_GPIO();

  /*==================================*/
  /* Choose if segment initialization */
  /* should be done or not.           */
  /* Return: 0 to omit seg_init       */
  /*         1 to run seg_init        */
  /*==================================*/
  return 1;
}

#define FCCLK_FREQ 100000000
/*************************************************************************
 * Function Name: Initialise_Clock_Source_and_PLL
 * Parameters: void
 * Return: void
 *
  * Description: Initialize PLL and clocks' dividers. pllclk - 400MHz,
 *              Fcckl = 100MHz
 *
 *************************************************************************/
void Initialise_Clock_Source_and_PLL(void)
{
  // 1. Init OSC
  SCS_bit.OSCRANGE = 0;
  SCS_bit.OSCEN = 1;

  while(!SCS_bit.OSCSTAT)
  {
      // 2.  Wait for OSC ready
  }
  
  // 3. Disconnect PLL
  PLL0CON_bit.PLLC = 0;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  
  // 4. Disable PLL
  PLL0CON_bit.PLLE = 0;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  
  // 5. Select source clock for PLL
  CLKSRCSEL_bit.CLKSRC = 1;   // Selects the main oscillator as a PLL clock source.
  PCLKSEL0 = PCLKSEL1  = 0;   // other peripherals 100/4 = 25MHz
  
//  // 6. Set PLL settings 300 MHz
//  PLL0CFG_bit.MSEL = 25-1;
//  PLL0CFG_bit.NSEL = 2-1;
//  PLL0FEED = 0xAA;
//  PLL0FEED = 0x55;
    // 6. Set PLL settings (pllclk) 400 MHz based on Fin of 12MHz
  PLL0CFG_bit.MSEL = 100-1;
  PLL0CFG_bit.NSEL = 6-1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  // 7. Enable PLL
  PLL0CON_bit.PLLE = 1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
  
  while(!PLL0STAT_bit.PLOCK)
  {
      // 8. Wait for the PLL to achieve lock
  }
  
  // 9. Set clk divider settings
//  CCLKCFG   = 3-1;            // 1/3 Fpll
  // 9. Set clk divider settings
  CCLKCFG   = 4-1;            // 1/4 pllclk
  
  // 10. Connect the PLL
  PLL0CON_bit.PLLC = 1;
  PLL0FEED = 0xAA;
  PLL0FEED = 0x55;
}

void Initialise_GPIO(void)
{
  // Set to inputs
  FIO0DIR = 0;
  FIO1DIR = 0;
  FIO2DIR = 0;
  FIO3DIR = 0;
  FIO4DIR = 0;

  // clear mask registers
  FIO0MASK = 0;
  FIO1MASK = 0;
  FIO2MASK = 0;
  FIO3MASK = 0;
  FIO4MASK = 0;

  // Reset all GPIO pins to default primary function
  PINSEL0 = 0; 
  PINSEL1 = 0;
  PINSEL2 = 0;
  PINSEL3 = 0;
  PINSEL4 = 0;
  PINSEL7 = 0;
  PINSEL8 = 0;
  PINSEL9 = 0;
}

#pragma language=default

#ifdef __cplusplus
}
#endif

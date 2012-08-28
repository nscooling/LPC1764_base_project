#include "serial.h"
#include <stdint.h>

/* UART Fractional Divider Register */
typedef struct{
  uint32_t DIVADDVAL  : 4;
  uint32_t MULVAL     : 4;
  uint32_t            :24;
} UARTfdr_bits;

/* Define access to UART0 registers using pointers */
volatile uint8_t * const pU0RBR = (uint8_t *) 0x4000C000;
volatile uint8_t * const pU0THR = (uint8_t *) 0x4000C000;
volatile uint8_t * const pU0LCR = (uint8_t *) 0x4000C00C;
volatile uint8_t * const pU0LSR = (uint8_t *) 0x4000C014;
volatile uint8_t * const pU0DLL = (uint8_t *) 0x4000C000;
volatile uint8_t * const pU0DLM = (uint8_t *) 0x4000C004;
volatile uint8_t * const pU0TER = (uint8_t *) 0x4000C030;
volatile uint8_t * const pU0FDR = (uint8_t *) 0x4000C028;
volatile UARTfdr_bits * const pU0FDR_bit = (UARTfdr_bits *) 0x4000C028;

volatile uint32_t * const pPINSEL0 = (uint32_t *)0x4002C000;


void init_serial0 (void)
{
  *pU0TER = 0;
  /* 1. Pin Function Select Register 0 already set 
  (in low_level_init.c) */
  *pPINSEL0 = 0x50; // UART0 Rx Tx
  
  /* 2. LCR: 8 bits, no parity, 1 stop bit */
  *pU0LCR = 0x03;
  
  /* 3. DLL: Get access using DLAB bit in LCR */
  *pU0LCR |= 0x80;
  
  /* 4. Set baud rate to 9600 baud */
  *pU0DLL = 0x5D;
  *pU0DLM = 0;
  //*pU0FDR = (4 << 4) | 3;
  pU0FDR_bit->DIVADDVAL = 3;
  pU0FDR_bit->MULVAL = 4;
  
  /* 5. Clear DLAB bit */
  *pU0LCR &= ~0x80;
  /* 6. Enable Transmit on Uart */
  *pU0TER = (1<<7);
}

/* Output a single character */
void putchar0 (char c)
{
   /* Wait until Tx ready flag set */
  while ((*pU0LSR & 0x20) == 0){
      /* Do nothing */ ;
  }
   /* Write character */
   *pU0THR = c; 

}

/* Output a character string */
void putstring0 (const char *str)
{
  while (*str) {
      putchar0 (*str++);
  }
}

/* Input a single character */
char getchar0 (void)
{ 
   /* Wait until Rx ready flag set */
   while ((*pU0LSR & 0x01) == 0){
      /* Do nothing */ ; 
   }
   /* Read character */
   return *pU0RBR;
}


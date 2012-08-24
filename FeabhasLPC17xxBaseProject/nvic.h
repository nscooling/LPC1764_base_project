#ifndef _NVIC_H_
#define _NVIC_H_

#include <stdint.h>

/*************************************************************************
 * Function Name: NVIC_IntEnable
 * Parameters: IntNumber - Interrupt number
 * Return: void
 *
 * Description: Enable interrupt at NVIC
 *
 *************************************************************************/
void NVIC_IntEnable(uint32_t IntNumber);

/*************************************************************************
 * Function Name: NVIC_IntDisable
 * Parameters: IntNumber - Interrupt number
 * Return: void
 *
 * Description: Disables interrupt at NVIC
 *
 *************************************************************************/
void NVIC_IntDisable(uint32_t IntNumber);

/*************************************************************************
 * Function Name: NVIC_ClrPend
 * Parameters: IntNumber - Interrupt number
 * Return: void
 *
 * Description:Clear pending interrupt at NVIC
 *
 *************************************************************************/
void NVIC_ClrPend(uint32_t IntNumber);

/*************************************************************************
 * Function Name: NVIC_IntPri
 * Parameters: IntNumber - Interrupt number, Interrupt Priority
 * Return: void
 *
 * Description:Sets Interrupt priority
 *
 *************************************************************************/
void NVIC_IntPri(uint32_t IntNumber, uint8_t Priority);

#endif

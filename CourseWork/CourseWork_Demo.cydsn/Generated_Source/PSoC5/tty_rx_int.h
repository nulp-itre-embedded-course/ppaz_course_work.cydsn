/*******************************************************************************
* File Name: tty_rx_int.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_tty_rx_int_H)
#define CY_ISR_tty_rx_int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void tty_rx_int_Start(void);
void tty_rx_int_StartEx(cyisraddress address);
void tty_rx_int_Stop(void);

CY_ISR_PROTO(tty_rx_int_Interrupt);

void tty_rx_int_SetVector(cyisraddress address);
cyisraddress tty_rx_int_GetVector(void);

void tty_rx_int_SetPriority(uint8 priority);
uint8 tty_rx_int_GetPriority(void);

void tty_rx_int_Enable(void);
uint8 tty_rx_int_GetState(void);
void tty_rx_int_Disable(void);

void tty_rx_int_SetPending(void);
void tty_rx_int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the tty_rx_int ISR. */
#define tty_rx_int_INTC_VECTOR            ((reg32 *) tty_rx_int__INTC_VECT)

/* Address of the tty_rx_int ISR priority. */
#define tty_rx_int_INTC_PRIOR             ((reg8 *) tty_rx_int__INTC_PRIOR_REG)

/* Priority of the tty_rx_int interrupt. */
#define tty_rx_int_INTC_PRIOR_NUMBER      tty_rx_int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable tty_rx_int interrupt. */
#define tty_rx_int_INTC_SET_EN            ((reg32 *) tty_rx_int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the tty_rx_int interrupt. */
#define tty_rx_int_INTC_CLR_EN            ((reg32 *) tty_rx_int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the tty_rx_int interrupt state to pending. */
#define tty_rx_int_INTC_SET_PD            ((reg32 *) tty_rx_int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the tty_rx_int interrupt. */
#define tty_rx_int_INTC_CLR_PD            ((reg32 *) tty_rx_int__INTC_CLR_PD_REG)


#endif /* CY_ISR_tty_rx_int_H */


/* [] END OF FILE */

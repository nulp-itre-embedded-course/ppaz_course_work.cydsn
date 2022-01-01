/*******************************************************************************
* File Name: isrSampleTimer.h
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
#if !defined(CY_ISR_isrSampleTimer_H)
#define CY_ISR_isrSampleTimer_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isrSampleTimer_Start(void);
void isrSampleTimer_StartEx(cyisraddress address);
void isrSampleTimer_Stop(void);

CY_ISR_PROTO(isrSampleTimer_Interrupt);

void isrSampleTimer_SetVector(cyisraddress address);
cyisraddress isrSampleTimer_GetVector(void);

void isrSampleTimer_SetPriority(uint8 priority);
uint8 isrSampleTimer_GetPriority(void);

void isrSampleTimer_Enable(void);
uint8 isrSampleTimer_GetState(void);
void isrSampleTimer_Disable(void);

void isrSampleTimer_SetPending(void);
void isrSampleTimer_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isrSampleTimer ISR. */
#define isrSampleTimer_INTC_VECTOR            ((reg32 *) isrSampleTimer__INTC_VECT)

/* Address of the isrSampleTimer ISR priority. */
#define isrSampleTimer_INTC_PRIOR             ((reg8 *) isrSampleTimer__INTC_PRIOR_REG)

/* Priority of the isrSampleTimer interrupt. */
#define isrSampleTimer_INTC_PRIOR_NUMBER      isrSampleTimer__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isrSampleTimer interrupt. */
#define isrSampleTimer_INTC_SET_EN            ((reg32 *) isrSampleTimer__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isrSampleTimer interrupt. */
#define isrSampleTimer_INTC_CLR_EN            ((reg32 *) isrSampleTimer__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isrSampleTimer interrupt state to pending. */
#define isrSampleTimer_INTC_SET_PD            ((reg32 *) isrSampleTimer__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isrSampleTimer interrupt. */
#define isrSampleTimer_INTC_CLR_PD            ((reg32 *) isrSampleTimer__INTC_CLR_PD_REG)


#endif /* CY_ISR_isrSampleTimer_H */


/* [] END OF FILE */

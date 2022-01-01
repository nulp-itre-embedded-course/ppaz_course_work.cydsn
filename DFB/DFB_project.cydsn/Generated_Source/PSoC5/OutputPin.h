/*******************************************************************************
* File Name: OutputPin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_OutputPin_H) /* Pins OutputPin_H */
#define CY_PINS_OutputPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "OutputPin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 OutputPin__PORT == 15 && ((OutputPin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    OutputPin_Write(uint8 value);
void    OutputPin_SetDriveMode(uint8 mode);
uint8   OutputPin_ReadDataReg(void);
uint8   OutputPin_Read(void);
void    OutputPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   OutputPin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the OutputPin_SetDriveMode() function.
     *  @{
     */
        #define OutputPin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define OutputPin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define OutputPin_DM_RES_UP          PIN_DM_RES_UP
        #define OutputPin_DM_RES_DWN         PIN_DM_RES_DWN
        #define OutputPin_DM_OD_LO           PIN_DM_OD_LO
        #define OutputPin_DM_OD_HI           PIN_DM_OD_HI
        #define OutputPin_DM_STRONG          PIN_DM_STRONG
        #define OutputPin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define OutputPin_MASK               OutputPin__MASK
#define OutputPin_SHIFT              OutputPin__SHIFT
#define OutputPin_WIDTH              1u

/* Interrupt constants */
#if defined(OutputPin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OutputPin_SetInterruptMode() function.
     *  @{
     */
        #define OutputPin_INTR_NONE      (uint16)(0x0000u)
        #define OutputPin_INTR_RISING    (uint16)(0x0001u)
        #define OutputPin_INTR_FALLING   (uint16)(0x0002u)
        #define OutputPin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define OutputPin_INTR_MASK      (0x01u) 
#endif /* (OutputPin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OutputPin_PS                     (* (reg8 *) OutputPin__PS)
/* Data Register */
#define OutputPin_DR                     (* (reg8 *) OutputPin__DR)
/* Port Number */
#define OutputPin_PRT_NUM                (* (reg8 *) OutputPin__PRT) 
/* Connect to Analog Globals */                                                  
#define OutputPin_AG                     (* (reg8 *) OutputPin__AG)                       
/* Analog MUX bux enable */
#define OutputPin_AMUX                   (* (reg8 *) OutputPin__AMUX) 
/* Bidirectional Enable */                                                        
#define OutputPin_BIE                    (* (reg8 *) OutputPin__BIE)
/* Bit-mask for Aliased Register Access */
#define OutputPin_BIT_MASK               (* (reg8 *) OutputPin__BIT_MASK)
/* Bypass Enable */
#define OutputPin_BYP                    (* (reg8 *) OutputPin__BYP)
/* Port wide control signals */                                                   
#define OutputPin_CTL                    (* (reg8 *) OutputPin__CTL)
/* Drive Modes */
#define OutputPin_DM0                    (* (reg8 *) OutputPin__DM0) 
#define OutputPin_DM1                    (* (reg8 *) OutputPin__DM1)
#define OutputPin_DM2                    (* (reg8 *) OutputPin__DM2) 
/* Input Buffer Disable Override */
#define OutputPin_INP_DIS                (* (reg8 *) OutputPin__INP_DIS)
/* LCD Common or Segment Drive */
#define OutputPin_LCD_COM_SEG            (* (reg8 *) OutputPin__LCD_COM_SEG)
/* Enable Segment LCD */
#define OutputPin_LCD_EN                 (* (reg8 *) OutputPin__LCD_EN)
/* Slew Rate Control */
#define OutputPin_SLW                    (* (reg8 *) OutputPin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define OutputPin_PRTDSI__CAPS_SEL       (* (reg8 *) OutputPin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define OutputPin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) OutputPin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define OutputPin_PRTDSI__OE_SEL0        (* (reg8 *) OutputPin__PRTDSI__OE_SEL0) 
#define OutputPin_PRTDSI__OE_SEL1        (* (reg8 *) OutputPin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define OutputPin_PRTDSI__OUT_SEL0       (* (reg8 *) OutputPin__PRTDSI__OUT_SEL0) 
#define OutputPin_PRTDSI__OUT_SEL1       (* (reg8 *) OutputPin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define OutputPin_PRTDSI__SYNC_OUT       (* (reg8 *) OutputPin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(OutputPin__SIO_CFG)
    #define OutputPin_SIO_HYST_EN        (* (reg8 *) OutputPin__SIO_HYST_EN)
    #define OutputPin_SIO_REG_HIFREQ     (* (reg8 *) OutputPin__SIO_REG_HIFREQ)
    #define OutputPin_SIO_CFG            (* (reg8 *) OutputPin__SIO_CFG)
    #define OutputPin_SIO_DIFF           (* (reg8 *) OutputPin__SIO_DIFF)
#endif /* (OutputPin__SIO_CFG) */

/* Interrupt Registers */
#if defined(OutputPin__INTSTAT)
    #define OutputPin_INTSTAT            (* (reg8 *) OutputPin__INTSTAT)
    #define OutputPin_SNAP               (* (reg8 *) OutputPin__SNAP)
    
	#define OutputPin_0_INTTYPE_REG 		(* (reg8 *) OutputPin__0__INTTYPE)
#endif /* (OutputPin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_OutputPin_H */


/* [] END OF FILE */

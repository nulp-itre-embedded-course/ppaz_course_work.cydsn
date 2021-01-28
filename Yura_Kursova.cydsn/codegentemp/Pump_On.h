/*******************************************************************************
* File Name: Pump_On.h  
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

#if !defined(CY_PINS_Pump_On_H) /* Pins Pump_On_H */
#define CY_PINS_Pump_On_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pump_On_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pump_On__PORT == 15 && ((Pump_On__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pump_On_Write(uint8 value);
void    Pump_On_SetDriveMode(uint8 mode);
uint8   Pump_On_ReadDataReg(void);
uint8   Pump_On_Read(void);
void    Pump_On_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pump_On_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pump_On_SetDriveMode() function.
     *  @{
     */
        #define Pump_On_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pump_On_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pump_On_DM_RES_UP          PIN_DM_RES_UP
        #define Pump_On_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pump_On_DM_OD_LO           PIN_DM_OD_LO
        #define Pump_On_DM_OD_HI           PIN_DM_OD_HI
        #define Pump_On_DM_STRONG          PIN_DM_STRONG
        #define Pump_On_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pump_On_MASK               Pump_On__MASK
#define Pump_On_SHIFT              Pump_On__SHIFT
#define Pump_On_WIDTH              1u

/* Interrupt constants */
#if defined(Pump_On__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pump_On_SetInterruptMode() function.
     *  @{
     */
        #define Pump_On_INTR_NONE      (uint16)(0x0000u)
        #define Pump_On_INTR_RISING    (uint16)(0x0001u)
        #define Pump_On_INTR_FALLING   (uint16)(0x0002u)
        #define Pump_On_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pump_On_INTR_MASK      (0x01u) 
#endif /* (Pump_On__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pump_On_PS                     (* (reg8 *) Pump_On__PS)
/* Data Register */
#define Pump_On_DR                     (* (reg8 *) Pump_On__DR)
/* Port Number */
#define Pump_On_PRT_NUM                (* (reg8 *) Pump_On__PRT) 
/* Connect to Analog Globals */                                                  
#define Pump_On_AG                     (* (reg8 *) Pump_On__AG)                       
/* Analog MUX bux enable */
#define Pump_On_AMUX                   (* (reg8 *) Pump_On__AMUX) 
/* Bidirectional Enable */                                                        
#define Pump_On_BIE                    (* (reg8 *) Pump_On__BIE)
/* Bit-mask for Aliased Register Access */
#define Pump_On_BIT_MASK               (* (reg8 *) Pump_On__BIT_MASK)
/* Bypass Enable */
#define Pump_On_BYP                    (* (reg8 *) Pump_On__BYP)
/* Port wide control signals */                                                   
#define Pump_On_CTL                    (* (reg8 *) Pump_On__CTL)
/* Drive Modes */
#define Pump_On_DM0                    (* (reg8 *) Pump_On__DM0) 
#define Pump_On_DM1                    (* (reg8 *) Pump_On__DM1)
#define Pump_On_DM2                    (* (reg8 *) Pump_On__DM2) 
/* Input Buffer Disable Override */
#define Pump_On_INP_DIS                (* (reg8 *) Pump_On__INP_DIS)
/* LCD Common or Segment Drive */
#define Pump_On_LCD_COM_SEG            (* (reg8 *) Pump_On__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pump_On_LCD_EN                 (* (reg8 *) Pump_On__LCD_EN)
/* Slew Rate Control */
#define Pump_On_SLW                    (* (reg8 *) Pump_On__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pump_On_PRTDSI__CAPS_SEL       (* (reg8 *) Pump_On__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pump_On_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pump_On__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pump_On_PRTDSI__OE_SEL0        (* (reg8 *) Pump_On__PRTDSI__OE_SEL0) 
#define Pump_On_PRTDSI__OE_SEL1        (* (reg8 *) Pump_On__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pump_On_PRTDSI__OUT_SEL0       (* (reg8 *) Pump_On__PRTDSI__OUT_SEL0) 
#define Pump_On_PRTDSI__OUT_SEL1       (* (reg8 *) Pump_On__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pump_On_PRTDSI__SYNC_OUT       (* (reg8 *) Pump_On__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pump_On__SIO_CFG)
    #define Pump_On_SIO_HYST_EN        (* (reg8 *) Pump_On__SIO_HYST_EN)
    #define Pump_On_SIO_REG_HIFREQ     (* (reg8 *) Pump_On__SIO_REG_HIFREQ)
    #define Pump_On_SIO_CFG            (* (reg8 *) Pump_On__SIO_CFG)
    #define Pump_On_SIO_DIFF           (* (reg8 *) Pump_On__SIO_DIFF)
#endif /* (Pump_On__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pump_On__INTSTAT)
    #define Pump_On_INTSTAT            (* (reg8 *) Pump_On__INTSTAT)
    #define Pump_On_SNAP               (* (reg8 *) Pump_On__SNAP)
    
	#define Pump_On_0_INTTYPE_REG 		(* (reg8 *) Pump_On__0__INTTYPE)
#endif /* (Pump_On__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pump_On_H */


/* [] END OF FILE */

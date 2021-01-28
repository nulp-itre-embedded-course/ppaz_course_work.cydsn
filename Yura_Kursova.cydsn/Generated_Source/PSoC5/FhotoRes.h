/*******************************************************************************
* File Name: FhotoRes.h  
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

#if !defined(CY_PINS_FhotoRes_H) /* Pins FhotoRes_H */
#define CY_PINS_FhotoRes_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FhotoRes_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FhotoRes__PORT == 15 && ((FhotoRes__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FhotoRes_Write(uint8 value);
void    FhotoRes_SetDriveMode(uint8 mode);
uint8   FhotoRes_ReadDataReg(void);
uint8   FhotoRes_Read(void);
void    FhotoRes_SetInterruptMode(uint16 position, uint16 mode);
uint8   FhotoRes_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FhotoRes_SetDriveMode() function.
     *  @{
     */
        #define FhotoRes_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FhotoRes_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FhotoRes_DM_RES_UP          PIN_DM_RES_UP
        #define FhotoRes_DM_RES_DWN         PIN_DM_RES_DWN
        #define FhotoRes_DM_OD_LO           PIN_DM_OD_LO
        #define FhotoRes_DM_OD_HI           PIN_DM_OD_HI
        #define FhotoRes_DM_STRONG          PIN_DM_STRONG
        #define FhotoRes_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FhotoRes_MASK               FhotoRes__MASK
#define FhotoRes_SHIFT              FhotoRes__SHIFT
#define FhotoRes_WIDTH              1u

/* Interrupt constants */
#if defined(FhotoRes__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FhotoRes_SetInterruptMode() function.
     *  @{
     */
        #define FhotoRes_INTR_NONE      (uint16)(0x0000u)
        #define FhotoRes_INTR_RISING    (uint16)(0x0001u)
        #define FhotoRes_INTR_FALLING   (uint16)(0x0002u)
        #define FhotoRes_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FhotoRes_INTR_MASK      (0x01u) 
#endif /* (FhotoRes__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FhotoRes_PS                     (* (reg8 *) FhotoRes__PS)
/* Data Register */
#define FhotoRes_DR                     (* (reg8 *) FhotoRes__DR)
/* Port Number */
#define FhotoRes_PRT_NUM                (* (reg8 *) FhotoRes__PRT) 
/* Connect to Analog Globals */                                                  
#define FhotoRes_AG                     (* (reg8 *) FhotoRes__AG)                       
/* Analog MUX bux enable */
#define FhotoRes_AMUX                   (* (reg8 *) FhotoRes__AMUX) 
/* Bidirectional Enable */                                                        
#define FhotoRes_BIE                    (* (reg8 *) FhotoRes__BIE)
/* Bit-mask for Aliased Register Access */
#define FhotoRes_BIT_MASK               (* (reg8 *) FhotoRes__BIT_MASK)
/* Bypass Enable */
#define FhotoRes_BYP                    (* (reg8 *) FhotoRes__BYP)
/* Port wide control signals */                                                   
#define FhotoRes_CTL                    (* (reg8 *) FhotoRes__CTL)
/* Drive Modes */
#define FhotoRes_DM0                    (* (reg8 *) FhotoRes__DM0) 
#define FhotoRes_DM1                    (* (reg8 *) FhotoRes__DM1)
#define FhotoRes_DM2                    (* (reg8 *) FhotoRes__DM2) 
/* Input Buffer Disable Override */
#define FhotoRes_INP_DIS                (* (reg8 *) FhotoRes__INP_DIS)
/* LCD Common or Segment Drive */
#define FhotoRes_LCD_COM_SEG            (* (reg8 *) FhotoRes__LCD_COM_SEG)
/* Enable Segment LCD */
#define FhotoRes_LCD_EN                 (* (reg8 *) FhotoRes__LCD_EN)
/* Slew Rate Control */
#define FhotoRes_SLW                    (* (reg8 *) FhotoRes__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FhotoRes_PRTDSI__CAPS_SEL       (* (reg8 *) FhotoRes__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FhotoRes_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FhotoRes__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FhotoRes_PRTDSI__OE_SEL0        (* (reg8 *) FhotoRes__PRTDSI__OE_SEL0) 
#define FhotoRes_PRTDSI__OE_SEL1        (* (reg8 *) FhotoRes__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FhotoRes_PRTDSI__OUT_SEL0       (* (reg8 *) FhotoRes__PRTDSI__OUT_SEL0) 
#define FhotoRes_PRTDSI__OUT_SEL1       (* (reg8 *) FhotoRes__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FhotoRes_PRTDSI__SYNC_OUT       (* (reg8 *) FhotoRes__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FhotoRes__SIO_CFG)
    #define FhotoRes_SIO_HYST_EN        (* (reg8 *) FhotoRes__SIO_HYST_EN)
    #define FhotoRes_SIO_REG_HIFREQ     (* (reg8 *) FhotoRes__SIO_REG_HIFREQ)
    #define FhotoRes_SIO_CFG            (* (reg8 *) FhotoRes__SIO_CFG)
    #define FhotoRes_SIO_DIFF           (* (reg8 *) FhotoRes__SIO_DIFF)
#endif /* (FhotoRes__SIO_CFG) */

/* Interrupt Registers */
#if defined(FhotoRes__INTSTAT)
    #define FhotoRes_INTSTAT            (* (reg8 *) FhotoRes__INTSTAT)
    #define FhotoRes_SNAP               (* (reg8 *) FhotoRes__SNAP)
    
	#define FhotoRes_0_INTTYPE_REG 		(* (reg8 *) FhotoRes__0__INTTYPE)
#endif /* (FhotoRes__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FhotoRes_H */


/* [] END OF FILE */

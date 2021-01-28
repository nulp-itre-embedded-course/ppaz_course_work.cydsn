/*******************************************************************************
* File Name: HidroSns.h  
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

#if !defined(CY_PINS_HidroSns_H) /* Pins HidroSns_H */
#define CY_PINS_HidroSns_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "HidroSns_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 HidroSns__PORT == 15 && ((HidroSns__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    HidroSns_Write(uint8 value);
void    HidroSns_SetDriveMode(uint8 mode);
uint8   HidroSns_ReadDataReg(void);
uint8   HidroSns_Read(void);
void    HidroSns_SetInterruptMode(uint16 position, uint16 mode);
uint8   HidroSns_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the HidroSns_SetDriveMode() function.
     *  @{
     */
        #define HidroSns_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define HidroSns_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define HidroSns_DM_RES_UP          PIN_DM_RES_UP
        #define HidroSns_DM_RES_DWN         PIN_DM_RES_DWN
        #define HidroSns_DM_OD_LO           PIN_DM_OD_LO
        #define HidroSns_DM_OD_HI           PIN_DM_OD_HI
        #define HidroSns_DM_STRONG          PIN_DM_STRONG
        #define HidroSns_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define HidroSns_MASK               HidroSns__MASK
#define HidroSns_SHIFT              HidroSns__SHIFT
#define HidroSns_WIDTH              1u

/* Interrupt constants */
#if defined(HidroSns__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HidroSns_SetInterruptMode() function.
     *  @{
     */
        #define HidroSns_INTR_NONE      (uint16)(0x0000u)
        #define HidroSns_INTR_RISING    (uint16)(0x0001u)
        #define HidroSns_INTR_FALLING   (uint16)(0x0002u)
        #define HidroSns_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define HidroSns_INTR_MASK      (0x01u) 
#endif /* (HidroSns__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define HidroSns_PS                     (* (reg8 *) HidroSns__PS)
/* Data Register */
#define HidroSns_DR                     (* (reg8 *) HidroSns__DR)
/* Port Number */
#define HidroSns_PRT_NUM                (* (reg8 *) HidroSns__PRT) 
/* Connect to Analog Globals */                                                  
#define HidroSns_AG                     (* (reg8 *) HidroSns__AG)                       
/* Analog MUX bux enable */
#define HidroSns_AMUX                   (* (reg8 *) HidroSns__AMUX) 
/* Bidirectional Enable */                                                        
#define HidroSns_BIE                    (* (reg8 *) HidroSns__BIE)
/* Bit-mask for Aliased Register Access */
#define HidroSns_BIT_MASK               (* (reg8 *) HidroSns__BIT_MASK)
/* Bypass Enable */
#define HidroSns_BYP                    (* (reg8 *) HidroSns__BYP)
/* Port wide control signals */                                                   
#define HidroSns_CTL                    (* (reg8 *) HidroSns__CTL)
/* Drive Modes */
#define HidroSns_DM0                    (* (reg8 *) HidroSns__DM0) 
#define HidroSns_DM1                    (* (reg8 *) HidroSns__DM1)
#define HidroSns_DM2                    (* (reg8 *) HidroSns__DM2) 
/* Input Buffer Disable Override */
#define HidroSns_INP_DIS                (* (reg8 *) HidroSns__INP_DIS)
/* LCD Common or Segment Drive */
#define HidroSns_LCD_COM_SEG            (* (reg8 *) HidroSns__LCD_COM_SEG)
/* Enable Segment LCD */
#define HidroSns_LCD_EN                 (* (reg8 *) HidroSns__LCD_EN)
/* Slew Rate Control */
#define HidroSns_SLW                    (* (reg8 *) HidroSns__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define HidroSns_PRTDSI__CAPS_SEL       (* (reg8 *) HidroSns__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define HidroSns_PRTDSI__DBL_SYNC_IN    (* (reg8 *) HidroSns__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define HidroSns_PRTDSI__OE_SEL0        (* (reg8 *) HidroSns__PRTDSI__OE_SEL0) 
#define HidroSns_PRTDSI__OE_SEL1        (* (reg8 *) HidroSns__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define HidroSns_PRTDSI__OUT_SEL0       (* (reg8 *) HidroSns__PRTDSI__OUT_SEL0) 
#define HidroSns_PRTDSI__OUT_SEL1       (* (reg8 *) HidroSns__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define HidroSns_PRTDSI__SYNC_OUT       (* (reg8 *) HidroSns__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(HidroSns__SIO_CFG)
    #define HidroSns_SIO_HYST_EN        (* (reg8 *) HidroSns__SIO_HYST_EN)
    #define HidroSns_SIO_REG_HIFREQ     (* (reg8 *) HidroSns__SIO_REG_HIFREQ)
    #define HidroSns_SIO_CFG            (* (reg8 *) HidroSns__SIO_CFG)
    #define HidroSns_SIO_DIFF           (* (reg8 *) HidroSns__SIO_DIFF)
#endif /* (HidroSns__SIO_CFG) */

/* Interrupt Registers */
#if defined(HidroSns__INTSTAT)
    #define HidroSns_INTSTAT            (* (reg8 *) HidroSns__INTSTAT)
    #define HidroSns_SNAP               (* (reg8 *) HidroSns__SNAP)
    
	#define HidroSns_0_INTTYPE_REG 		(* (reg8 *) HidroSns__0__INTTYPE)
#endif /* (HidroSns__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_HidroSns_H */


/* [] END OF FILE */

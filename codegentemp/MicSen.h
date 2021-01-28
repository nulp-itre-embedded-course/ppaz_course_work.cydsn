/*******************************************************************************
* File Name: MicSen.h  
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

#if !defined(CY_PINS_MicSen_H) /* Pins MicSen_H */
#define CY_PINS_MicSen_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MicSen_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MicSen__PORT == 15 && ((MicSen__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MicSen_Write(uint8 value);
void    MicSen_SetDriveMode(uint8 mode);
uint8   MicSen_ReadDataReg(void);
uint8   MicSen_Read(void);
void    MicSen_SetInterruptMode(uint16 position, uint16 mode);
uint8   MicSen_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MicSen_SetDriveMode() function.
     *  @{
     */
        #define MicSen_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define MicSen_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define MicSen_DM_RES_UP          PIN_DM_RES_UP
        #define MicSen_DM_RES_DWN         PIN_DM_RES_DWN
        #define MicSen_DM_OD_LO           PIN_DM_OD_LO
        #define MicSen_DM_OD_HI           PIN_DM_OD_HI
        #define MicSen_DM_STRONG          PIN_DM_STRONG
        #define MicSen_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MicSen_MASK               MicSen__MASK
#define MicSen_SHIFT              MicSen__SHIFT
#define MicSen_WIDTH              1u

/* Interrupt constants */
#if defined(MicSen__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MicSen_SetInterruptMode() function.
     *  @{
     */
        #define MicSen_INTR_NONE      (uint16)(0x0000u)
        #define MicSen_INTR_RISING    (uint16)(0x0001u)
        #define MicSen_INTR_FALLING   (uint16)(0x0002u)
        #define MicSen_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define MicSen_INTR_MASK      (0x01u) 
#endif /* (MicSen__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MicSen_PS                     (* (reg8 *) MicSen__PS)
/* Data Register */
#define MicSen_DR                     (* (reg8 *) MicSen__DR)
/* Port Number */
#define MicSen_PRT_NUM                (* (reg8 *) MicSen__PRT) 
/* Connect to Analog Globals */                                                  
#define MicSen_AG                     (* (reg8 *) MicSen__AG)                       
/* Analog MUX bux enable */
#define MicSen_AMUX                   (* (reg8 *) MicSen__AMUX) 
/* Bidirectional Enable */                                                        
#define MicSen_BIE                    (* (reg8 *) MicSen__BIE)
/* Bit-mask for Aliased Register Access */
#define MicSen_BIT_MASK               (* (reg8 *) MicSen__BIT_MASK)
/* Bypass Enable */
#define MicSen_BYP                    (* (reg8 *) MicSen__BYP)
/* Port wide control signals */                                                   
#define MicSen_CTL                    (* (reg8 *) MicSen__CTL)
/* Drive Modes */
#define MicSen_DM0                    (* (reg8 *) MicSen__DM0) 
#define MicSen_DM1                    (* (reg8 *) MicSen__DM1)
#define MicSen_DM2                    (* (reg8 *) MicSen__DM2) 
/* Input Buffer Disable Override */
#define MicSen_INP_DIS                (* (reg8 *) MicSen__INP_DIS)
/* LCD Common or Segment Drive */
#define MicSen_LCD_COM_SEG            (* (reg8 *) MicSen__LCD_COM_SEG)
/* Enable Segment LCD */
#define MicSen_LCD_EN                 (* (reg8 *) MicSen__LCD_EN)
/* Slew Rate Control */
#define MicSen_SLW                    (* (reg8 *) MicSen__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MicSen_PRTDSI__CAPS_SEL       (* (reg8 *) MicSen__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MicSen_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MicSen__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MicSen_PRTDSI__OE_SEL0        (* (reg8 *) MicSen__PRTDSI__OE_SEL0) 
#define MicSen_PRTDSI__OE_SEL1        (* (reg8 *) MicSen__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MicSen_PRTDSI__OUT_SEL0       (* (reg8 *) MicSen__PRTDSI__OUT_SEL0) 
#define MicSen_PRTDSI__OUT_SEL1       (* (reg8 *) MicSen__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MicSen_PRTDSI__SYNC_OUT       (* (reg8 *) MicSen__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MicSen__SIO_CFG)
    #define MicSen_SIO_HYST_EN        (* (reg8 *) MicSen__SIO_HYST_EN)
    #define MicSen_SIO_REG_HIFREQ     (* (reg8 *) MicSen__SIO_REG_HIFREQ)
    #define MicSen_SIO_CFG            (* (reg8 *) MicSen__SIO_CFG)
    #define MicSen_SIO_DIFF           (* (reg8 *) MicSen__SIO_DIFF)
#endif /* (MicSen__SIO_CFG) */

/* Interrupt Registers */
#if defined(MicSen__INTSTAT)
    #define MicSen_INTSTAT            (* (reg8 *) MicSen__INTSTAT)
    #define MicSen_SNAP               (* (reg8 *) MicSen__SNAP)
    
	#define MicSen_0_INTTYPE_REG 		(* (reg8 *) MicSen__0__INTTYPE)
#endif /* (MicSen__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MicSen_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: PhotoSen.h  
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

#if !defined(CY_PINS_PhotoSen_H) /* Pins PhotoSen_H */
#define CY_PINS_PhotoSen_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PhotoSen_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PhotoSen__PORT == 15 && ((PhotoSen__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PhotoSen_Write(uint8 value);
void    PhotoSen_SetDriveMode(uint8 mode);
uint8   PhotoSen_ReadDataReg(void);
uint8   PhotoSen_Read(void);
void    PhotoSen_SetInterruptMode(uint16 position, uint16 mode);
uint8   PhotoSen_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PhotoSen_SetDriveMode() function.
     *  @{
     */
        #define PhotoSen_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PhotoSen_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PhotoSen_DM_RES_UP          PIN_DM_RES_UP
        #define PhotoSen_DM_RES_DWN         PIN_DM_RES_DWN
        #define PhotoSen_DM_OD_LO           PIN_DM_OD_LO
        #define PhotoSen_DM_OD_HI           PIN_DM_OD_HI
        #define PhotoSen_DM_STRONG          PIN_DM_STRONG
        #define PhotoSen_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PhotoSen_MASK               PhotoSen__MASK
#define PhotoSen_SHIFT              PhotoSen__SHIFT
#define PhotoSen_WIDTH              1u

/* Interrupt constants */
#if defined(PhotoSen__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PhotoSen_SetInterruptMode() function.
     *  @{
     */
        #define PhotoSen_INTR_NONE      (uint16)(0x0000u)
        #define PhotoSen_INTR_RISING    (uint16)(0x0001u)
        #define PhotoSen_INTR_FALLING   (uint16)(0x0002u)
        #define PhotoSen_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PhotoSen_INTR_MASK      (0x01u) 
#endif /* (PhotoSen__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PhotoSen_PS                     (* (reg8 *) PhotoSen__PS)
/* Data Register */
#define PhotoSen_DR                     (* (reg8 *) PhotoSen__DR)
/* Port Number */
#define PhotoSen_PRT_NUM                (* (reg8 *) PhotoSen__PRT) 
/* Connect to Analog Globals */                                                  
#define PhotoSen_AG                     (* (reg8 *) PhotoSen__AG)                       
/* Analog MUX bux enable */
#define PhotoSen_AMUX                   (* (reg8 *) PhotoSen__AMUX) 
/* Bidirectional Enable */                                                        
#define PhotoSen_BIE                    (* (reg8 *) PhotoSen__BIE)
/* Bit-mask for Aliased Register Access */
#define PhotoSen_BIT_MASK               (* (reg8 *) PhotoSen__BIT_MASK)
/* Bypass Enable */
#define PhotoSen_BYP                    (* (reg8 *) PhotoSen__BYP)
/* Port wide control signals */                                                   
#define PhotoSen_CTL                    (* (reg8 *) PhotoSen__CTL)
/* Drive Modes */
#define PhotoSen_DM0                    (* (reg8 *) PhotoSen__DM0) 
#define PhotoSen_DM1                    (* (reg8 *) PhotoSen__DM1)
#define PhotoSen_DM2                    (* (reg8 *) PhotoSen__DM2) 
/* Input Buffer Disable Override */
#define PhotoSen_INP_DIS                (* (reg8 *) PhotoSen__INP_DIS)
/* LCD Common or Segment Drive */
#define PhotoSen_LCD_COM_SEG            (* (reg8 *) PhotoSen__LCD_COM_SEG)
/* Enable Segment LCD */
#define PhotoSen_LCD_EN                 (* (reg8 *) PhotoSen__LCD_EN)
/* Slew Rate Control */
#define PhotoSen_SLW                    (* (reg8 *) PhotoSen__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PhotoSen_PRTDSI__CAPS_SEL       (* (reg8 *) PhotoSen__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PhotoSen_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PhotoSen__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PhotoSen_PRTDSI__OE_SEL0        (* (reg8 *) PhotoSen__PRTDSI__OE_SEL0) 
#define PhotoSen_PRTDSI__OE_SEL1        (* (reg8 *) PhotoSen__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PhotoSen_PRTDSI__OUT_SEL0       (* (reg8 *) PhotoSen__PRTDSI__OUT_SEL0) 
#define PhotoSen_PRTDSI__OUT_SEL1       (* (reg8 *) PhotoSen__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PhotoSen_PRTDSI__SYNC_OUT       (* (reg8 *) PhotoSen__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PhotoSen__SIO_CFG)
    #define PhotoSen_SIO_HYST_EN        (* (reg8 *) PhotoSen__SIO_HYST_EN)
    #define PhotoSen_SIO_REG_HIFREQ     (* (reg8 *) PhotoSen__SIO_REG_HIFREQ)
    #define PhotoSen_SIO_CFG            (* (reg8 *) PhotoSen__SIO_CFG)
    #define PhotoSen_SIO_DIFF           (* (reg8 *) PhotoSen__SIO_DIFF)
#endif /* (PhotoSen__SIO_CFG) */

/* Interrupt Registers */
#if defined(PhotoSen__INTSTAT)
    #define PhotoSen_INTSTAT            (* (reg8 *) PhotoSen__INTSTAT)
    #define PhotoSen_SNAP               (* (reg8 *) PhotoSen__SNAP)
    
	#define PhotoSen_0_INTTYPE_REG 		(* (reg8 *) PhotoSen__0__INTTYPE)
#endif /* (PhotoSen__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PhotoSen_H */


/* [] END OF FILE */

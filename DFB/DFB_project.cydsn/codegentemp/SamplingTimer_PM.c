/*******************************************************************************
* File Name: SamplingTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "SamplingTimer.h"

static SamplingTimer_backupStruct SamplingTimer_backup;


/*******************************************************************************
* Function Name: SamplingTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SamplingTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void SamplingTimer_SaveConfig(void) 
{
    #if (!SamplingTimer_UsingFixedFunction)
        SamplingTimer_backup.TimerUdb = SamplingTimer_ReadCounter();
        SamplingTimer_backup.InterruptMaskValue = SamplingTimer_STATUS_MASK;
        #if (SamplingTimer_UsingHWCaptureCounter)
            SamplingTimer_backup.TimerCaptureCounter = SamplingTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!SamplingTimer_UDB_CONTROL_REG_REMOVED)
            SamplingTimer_backup.TimerControlRegister = SamplingTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: SamplingTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SamplingTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void SamplingTimer_RestoreConfig(void) 
{   
    #if (!SamplingTimer_UsingFixedFunction)

        SamplingTimer_WriteCounter(SamplingTimer_backup.TimerUdb);
        SamplingTimer_STATUS_MASK =SamplingTimer_backup.InterruptMaskValue;
        #if (SamplingTimer_UsingHWCaptureCounter)
            SamplingTimer_SetCaptureCount(SamplingTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!SamplingTimer_UDB_CONTROL_REG_REMOVED)
            SamplingTimer_WriteControlRegister(SamplingTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: SamplingTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SamplingTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void SamplingTimer_Sleep(void) 
{
    #if(!SamplingTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(SamplingTimer_CTRL_ENABLE == (SamplingTimer_CONTROL & SamplingTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            SamplingTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            SamplingTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    SamplingTimer_Stop();
    SamplingTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SamplingTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SamplingTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void SamplingTimer_Wakeup(void) 
{
    SamplingTimer_RestoreConfig();
    #if(!SamplingTimer_UDB_CONTROL_REG_REMOVED)
        if(SamplingTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                SamplingTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

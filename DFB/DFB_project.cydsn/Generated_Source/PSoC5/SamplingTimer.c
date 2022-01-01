/*******************************************************************************
* File Name: SamplingTimer.c
* Version 2.80
*
* Description:
*  The Timer component consists of a 8, 16, 24 or 32-bit timer with
*  a selectable period between 2 and 2^Width - 1.  The timer may free run
*  or be used as a capture timer as well.  The capture can be initiated
*  by a positive or negative edge signal as well as via software.
*  A trigger input can be programmed to enable the timer on rising edge
*  falling edge, either edge or continous run.
*  Interrupts may be generated due to a terminal count condition
*  or a capture event.
*
* Note:
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "SamplingTimer.h"

uint8 SamplingTimer_initVar = 0u;


/*******************************************************************************
* Function Name: SamplingTimer_Init
********************************************************************************
*
* Summary:
*  Initialize to the schematic state
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_Init(void) 
{
    #if(!SamplingTimer_UsingFixedFunction)
            /* Interrupt State Backup for Critical Region*/
            uint8 SamplingTimer_interruptState;
    #endif /* Interrupt state back up for Fixed Function only */

    #if (SamplingTimer_UsingFixedFunction)
        /* Clear all bits but the enable bit (if it's already set) for Timer operation */
        SamplingTimer_CONTROL &= SamplingTimer_CTRL_ENABLE;

        /* Clear the mode bits for continuous run mode */
        #if (CY_PSOC5A)
            SamplingTimer_CONTROL2 &= ((uint8)(~SamplingTimer_CTRL_MODE_MASK));
        #endif /* Clear bits in CONTROL2 only in PSOC5A */

        #if (CY_PSOC3 || CY_PSOC5LP)
            SamplingTimer_CONTROL3 &= ((uint8)(~SamplingTimer_CTRL_MODE_MASK));
        #endif /* CONTROL3 register exists only in PSoC3 OR PSoC5LP */

        /* Check if One Shot mode is enabled i.e. RunMode !=0*/
        #if (SamplingTimer_RunModeUsed != 0x0u)
            /* Set 3rd bit of Control register to enable one shot mode */
            SamplingTimer_CONTROL |= 0x04u;
        #endif /* One Shot enabled only when RunModeUsed is not Continuous*/

        #if (SamplingTimer_RunModeUsed == 2)
            #if (CY_PSOC5A)
                /* Set last 2 bits of control2 register if one shot(halt on
                interrupt) is enabled*/
                SamplingTimer_CONTROL2 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Set last 2 bits of control3 register if one shot(halt on
                interrupt) is enabled*/
                SamplingTimer_CONTROL3 |= 0x03u;
            #endif /* Set One-Shot Halt on Interrupt bit in CONTROL3 for PSoC3 or PSoC5LP */

        #endif /* Remove section if One Shot Halt on Interrupt is not enabled */

        #if (SamplingTimer_UsingHWEnable != 0)
            #if (CY_PSOC5A)
                /* Set the default Run Mode of the Timer to Continuous */
                SamplingTimer_CONTROL2 |= SamplingTimer_CTRL_MODE_PULSEWIDTH;
            #endif /* Set Continuous Run Mode in CONTROL2 for PSoC5A */

            #if (CY_PSOC3 || CY_PSOC5LP)
                /* Clear and Set ROD and COD bits of CFG2 register */
                SamplingTimer_CONTROL3 &= ((uint8)(~SamplingTimer_CTRL_RCOD_MASK));
                SamplingTimer_CONTROL3 |= SamplingTimer_CTRL_RCOD;

                /* Clear and Enable the HW enable bit in CFG2 register */
                SamplingTimer_CONTROL3 &= ((uint8)(~SamplingTimer_CTRL_ENBL_MASK));
                SamplingTimer_CONTROL3 |= SamplingTimer_CTRL_ENBL;

                /* Set the default Run Mode of the Timer to Continuous */
                SamplingTimer_CONTROL3 |= SamplingTimer_CTRL_MODE_CONTINUOUS;
            #endif /* Set Continuous Run Mode in CONTROL3 for PSoC3ES3 or PSoC5A */

        #endif /* Configure Run Mode with hardware enable */

        /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        SamplingTimer_RT1 &= ((uint8)(~SamplingTimer_RT1_MASK));
        SamplingTimer_RT1 |= SamplingTimer_SYNC;

        /*Enable DSI Sync all all inputs of the Timer*/
        SamplingTimer_RT1 &= ((uint8)(~SamplingTimer_SYNCDSI_MASK));
        SamplingTimer_RT1 |= SamplingTimer_SYNCDSI_EN;

        /* Set the IRQ to use the status register interrupts */
        SamplingTimer_CONTROL2 |= SamplingTimer_CTRL2_IRQ_SEL;
    #endif /* Configuring registers of fixed function implementation */

    /* Set Initial values from Configuration */
    SamplingTimer_WritePeriod(SamplingTimer_INIT_PERIOD);
    SamplingTimer_WriteCounter(SamplingTimer_INIT_PERIOD);

    #if (SamplingTimer_UsingHWCaptureCounter)/* Capture counter is enabled */
        SamplingTimer_CAPTURE_COUNT_CTRL |= SamplingTimer_CNTR_ENABLE;
        SamplingTimer_SetCaptureCount(SamplingTimer_INIT_CAPTURE_COUNT);
    #endif /* Configure capture counter value */

    #if (!SamplingTimer_UsingFixedFunction)
        #if (SamplingTimer_SoftwareCaptureMode)
            SamplingTimer_SetCaptureMode(SamplingTimer_INIT_CAPTURE_MODE);
        #endif /* Set Capture Mode for UDB implementation if capture mode is software controlled */

        #if (SamplingTimer_SoftwareTriggerMode)
            #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED)
                if (0u == (SamplingTimer_CONTROL & SamplingTimer__B_TIMER__TM_SOFTWARE))
                {
                    SamplingTimer_SetTriggerMode(SamplingTimer_INIT_TRIGGER_MODE);
                }
            #endif /* (!SamplingTimer_UDB_CONTROL_REG_REMOVED) */
        #endif /* Set trigger mode for UDB Implementation if trigger mode is software controlled */

        /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
        /* Enter Critical Region*/
        SamplingTimer_interruptState = CyEnterCriticalSection();

        /* Use the interrupt output of the status register for IRQ output */
        SamplingTimer_STATUS_AUX_CTRL |= SamplingTimer_STATUS_ACTL_INT_EN_MASK;

        /* Exit Critical Region*/
        CyExitCriticalSection(SamplingTimer_interruptState);

        #if (SamplingTimer_EnableTriggerMode)
            SamplingTimer_EnableTrigger();
        #endif /* Set Trigger enable bit for UDB implementation in the control register*/
		
		
        #if (SamplingTimer_InterruptOnCaptureCount && !SamplingTimer_UDB_CONTROL_REG_REMOVED)
            SamplingTimer_SetInterruptCount(SamplingTimer_INIT_INT_CAPTURE_COUNT);
        #endif /* Set interrupt count in UDB implementation if interrupt count feature is checked.*/

        SamplingTimer_ClearFIFO();
    #endif /* Configure additional features of UDB implementation */

    SamplingTimer_SetInterruptMode(SamplingTimer_INIT_INTERRUPT_MODE);
}


/*******************************************************************************
* Function Name: SamplingTimer_Enable
********************************************************************************
*
* Summary:
*  Enable the Timer
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (SamplingTimer_UsingFixedFunction)
        SamplingTimer_GLOBAL_ENABLE |= SamplingTimer_BLOCK_EN_MASK;
        SamplingTimer_GLOBAL_STBY_ENABLE |= SamplingTimer_BLOCK_STBY_EN_MASK;
    #endif /* Set Enable bit for enabling Fixed function timer*/

    /* Remove assignment if control register is removed */
    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED || SamplingTimer_UsingFixedFunction)
        SamplingTimer_CONTROL |= SamplingTimer_CTRL_ENABLE;
    #endif /* Remove assignment if control register is removed */
}


/*******************************************************************************
* Function Name: SamplingTimer_Start
********************************************************************************
*
* Summary:
*  The start function initializes the timer with the default values, the
*  enables the timerto begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  SamplingTimer_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void SamplingTimer_Start(void) 
{
    if(SamplingTimer_initVar == 0u)
    {
        SamplingTimer_Init();

        SamplingTimer_initVar = 1u;   /* Clear this bit for Initialization */
    }

    /* Enable the Timer */
    SamplingTimer_Enable();
}


/*******************************************************************************
* Function Name: SamplingTimer_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the timer, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the timer.
*
*******************************************************************************/
void SamplingTimer_Stop(void) 
{
    /* Disable Timer */
    #if(!SamplingTimer_UDB_CONTROL_REG_REMOVED || SamplingTimer_UsingFixedFunction)
        SamplingTimer_CONTROL &= ((uint8)(~SamplingTimer_CTRL_ENABLE));
    #endif /* Remove assignment if control register is removed */

    /* Globally disable the Fixed Function Block chosen */
    #if (SamplingTimer_UsingFixedFunction)
        SamplingTimer_GLOBAL_ENABLE &= ((uint8)(~SamplingTimer_BLOCK_EN_MASK));
        SamplingTimer_GLOBAL_STBY_ENABLE &= ((uint8)(~SamplingTimer_BLOCK_STBY_EN_MASK));
    #endif /* Disable global enable for the Timer Fixed function block to stop the Timer*/
}


/*******************************************************************************
* Function Name: SamplingTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function selects which of the interrupt inputs may cause an interrupt.
*  The twosources are caputure and terminal.  One, both or neither may
*  be selected.
*
* Parameters:
*  interruptMode:   This parameter is used to enable interrups on either/or
*                   terminal count or capture.
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_SetInterruptMode(uint8 interruptMode) 
{
    SamplingTimer_STATUS_MASK = interruptMode;
}


/*******************************************************************************
* Function Name: SamplingTimer_SoftwareCapture
********************************************************************************
*
* Summary:
*  This function forces a capture independent of the capture signal.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Side Effects:
*  An existing hardware capture could be overwritten.
*
*******************************************************************************/
void SamplingTimer_SoftwareCapture(void) 
{
    /* Generate a software capture by reading the counter register */
    #if(SamplingTimer_UsingFixedFunction)
        (void)CY_GET_REG16(SamplingTimer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(SamplingTimer_COUNTER_LSB_PTR_8BIT);
    #endif/* (SamplingTimer_UsingFixedFunction) */
    /* Capture Data is now in the FIFO */
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadStatusRegister
********************************************************************************
*
* Summary:
*  Reads the status register and returns it's state. This function should use
*  defined types for the bit-field information as the bits in this register may
*  be permuteable.
*
* Parameters:
*  void
*
* Return:
*  The contents of the status register
*
* Side Effects:
*  Status register bits may be clear on read.
*
*******************************************************************************/
uint8   SamplingTimer_ReadStatusRegister(void) 
{
    return (SamplingTimer_STATUS);
}


#if (!SamplingTimer_UDB_CONTROL_REG_REMOVED) /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: SamplingTimer_ReadControlRegister
********************************************************************************
*
* Summary:
*  Reads the control register and returns it's value.
*
* Parameters:
*  void
*
* Return:
*  The contents of the control register
*
*******************************************************************************/
uint8 SamplingTimer_ReadControlRegister(void) 
{
    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED) 
        return ((uint8)SamplingTimer_CONTROL);
    #else
        return (0);
    #endif /* (!SamplingTimer_UDB_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: SamplingTimer_WriteControlRegister
********************************************************************************
*
* Summary:
*  Sets the bit-field of the control register.
*
* Parameters:
*  control: The contents of the control register
*
* Return:
*
*******************************************************************************/
void SamplingTimer_WriteControlRegister(uint8 control) 
{
    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED) 
        SamplingTimer_CONTROL = control;
    #else
        control = 0u;
    #endif /* (!SamplingTimer_UDB_CONTROL_REG_REMOVED) */
}

#endif /* Remove API if control register is unused */


/*******************************************************************************
* Function Name: SamplingTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  This function returns the current value of the Period.
*
* Parameters:
*  void
*
* Return:
*  The present value of the counter.
*
*******************************************************************************/
uint16 SamplingTimer_ReadPeriod(void) 
{
   #if(SamplingTimer_UsingFixedFunction)
       return ((uint16)CY_GET_REG16(SamplingTimer_PERIOD_LSB_PTR));
   #else
       return (CY_GET_REG16(SamplingTimer_PERIOD_LSB_PTR));
   #endif /* (SamplingTimer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SamplingTimer_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period: This value may be between 1 and (2^Resolution)-1.  A value of 0 will
*          result in the counter remaining at zero.
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_WritePeriod(uint16 period) 
{
    #if(SamplingTimer_UsingFixedFunction)
        uint16 period_temp = (uint16)period;
        CY_SET_REG16(SamplingTimer_PERIOD_LSB_PTR, period_temp);
    #else
        CY_SET_REG16(SamplingTimer_PERIOD_LSB_PTR, period);
    #endif /*Write Period value with appropriate resolution suffix depending on UDB or fixed function implementation */
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCapture
********************************************************************************
*
* Summary:
*  This function returns the last value captured.
*
* Parameters:
*  void
*
* Return:
*  Present Capture value.
*
*******************************************************************************/
uint16 SamplingTimer_ReadCapture(void) 
{
   #if(SamplingTimer_UsingFixedFunction)
       return ((uint16)CY_GET_REG16(SamplingTimer_CAPTURE_LSB_PTR));
   #else
       return (CY_GET_REG16(SamplingTimer_CAPTURE_LSB_PTR));
   #endif /* (SamplingTimer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: SamplingTimer_WriteCounter
********************************************************************************
*
* Summary:
*  This funtion is used to set the counter to a specific value
*
* Parameters:
*  counter:  New counter value.
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_WriteCounter(uint16 counter) 
{
   #if(SamplingTimer_UsingFixedFunction)
        /* This functionality is removed until a FixedFunction HW update to
         * allow this register to be written
         */
        CY_SET_REG16(SamplingTimer_COUNTER_LSB_PTR, (uint16)counter);
        
    #else
        CY_SET_REG16(SamplingTimer_COUNTER_LSB_PTR, counter);
    #endif /* Set Write Counter only for the UDB implementation (Write Counter not available in fixed function Timer */
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCounter
********************************************************************************
*
* Summary:
*  This function returns the current counter value.
*
* Parameters:
*  void
*
* Return:
*  Present compare value.
*
*******************************************************************************/
uint16 SamplingTimer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(SamplingTimer_UsingFixedFunction)
        (void)CY_GET_REG16(SamplingTimer_COUNTER_LSB_PTR);
    #else
        (void)CY_GET_REG8(SamplingTimer_COUNTER_LSB_PTR_8BIT);
    #endif/* (SamplingTimer_UsingFixedFunction) */

    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(SamplingTimer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(SamplingTimer_CAPTURE_LSB_PTR));
    #else
        return (CY_GET_REG16(SamplingTimer_CAPTURE_LSB_PTR));
    #endif /* (SamplingTimer_UsingFixedFunction) */
}


#if(!SamplingTimer_UsingFixedFunction) /* UDB Specific Functions */

    
/*******************************************************************************
 * The functions below this point are only available using the UDB
 * implementation.  If a feature is selected, then the API is enabled.
 ******************************************************************************/


#if (SamplingTimer_SoftwareCaptureMode)


/*******************************************************************************
* Function Name: SamplingTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  This function sets the capture mode to either rising or falling edge.
*
* Parameters:
*  captureMode: This parameter sets the capture mode of the UDB capture feature
*  The parameter values are defined using the
*  #define SamplingTimer__B_TIMER__CM_NONE 0
#define SamplingTimer__B_TIMER__CM_RISINGEDGE 1
#define SamplingTimer__B_TIMER__CM_FALLINGEDGE 2
#define SamplingTimer__B_TIMER__CM_EITHEREDGE 3
#define SamplingTimer__B_TIMER__CM_SOFTWARE 4
 identifiers
*  The following are the possible values of the parameter
*  SamplingTimer__B_TIMER__CM_NONE        - Set Capture mode to None
*  SamplingTimer__B_TIMER__CM_RISINGEDGE  - Rising edge of Capture input
*  SamplingTimer__B_TIMER__CM_FALLINGEDGE - Falling edge of Capture input
*  SamplingTimer__B_TIMER__CM_EITHEREDGE  - Either edge of Capture input
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_SetCaptureMode(uint8 captureMode) 
{
    /* This must only set to two bits of the control register associated */
    captureMode = ((uint8)((uint8)captureMode << SamplingTimer_CTRL_CAP_MODE_SHIFT));
    captureMode &= (SamplingTimer_CTRL_CAP_MODE_MASK);

    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        SamplingTimer_CONTROL &= ((uint8)(~SamplingTimer_CTRL_CAP_MODE_MASK));

        /* Write The New Setting */
        SamplingTimer_CONTROL |= captureMode;
    #endif /* (!SamplingTimer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* Remove API if Capture Mode is not Software Controlled */


#if (SamplingTimer_SoftwareTriggerMode)


/*******************************************************************************
* Function Name: SamplingTimer_SetTriggerMode
********************************************************************************
*
* Summary:
*  This function sets the trigger input mode
*
* Parameters:
*  triggerMode: Pass one of the pre-defined Trigger Modes (except Software)
    #define SamplingTimer__B_TIMER__TM_NONE 0x00u
    #define SamplingTimer__B_TIMER__TM_RISINGEDGE 0x04u
    #define SamplingTimer__B_TIMER__TM_FALLINGEDGE 0x08u
    #define SamplingTimer__B_TIMER__TM_EITHEREDGE 0x0Cu
    #define SamplingTimer__B_TIMER__TM_SOFTWARE 0x10u
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_SetTriggerMode(uint8 triggerMode) 
{
    /* This must only set to two bits of the control register associated */
    triggerMode &= SamplingTimer_CTRL_TRIG_MODE_MASK;

    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
    
        /* Clear the Current Setting */
        SamplingTimer_CONTROL &= ((uint8)(~SamplingTimer_CTRL_TRIG_MODE_MASK));

        /* Write The New Setting */
        SamplingTimer_CONTROL |= (triggerMode | SamplingTimer__B_TIMER__TM_SOFTWARE);
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API if Trigger Mode is not Software Controlled */

#if (SamplingTimer_EnableTriggerMode)


/*******************************************************************************
* Function Name: SamplingTimer_EnableTrigger
********************************************************************************
*
* Summary:
*  Sets the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_EnableTrigger(void) 
{
    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED)   /* Remove assignment if control register is removed */
        SamplingTimer_CONTROL |= SamplingTimer_CTRL_TRIG_EN;
    #endif /* Remove code section if control register is not used */
}


/*******************************************************************************
* Function Name: SamplingTimer_DisableTrigger
********************************************************************************
*
* Summary:
*  Clears the control bit enabling Hardware Trigger mode
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_DisableTrigger(void) 
{
    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED )   /* Remove assignment if control register is removed */
        SamplingTimer_CONTROL &= ((uint8)(~SamplingTimer_CTRL_TRIG_EN));
    #endif /* Remove code section if control register is not used */
}
#endif /* Remove API is Trigger Mode is set to None */

#if(SamplingTimer_InterruptOnCaptureCount)


/*******************************************************************************
* Function Name: SamplingTimer_SetInterruptCount
********************************************************************************
*
* Summary:
*  This function sets the capture count before an interrupt is triggered.
*
* Parameters:
*  interruptCount:  A value between 0 and 3 is valid.  If the value is 0, then
*                   an interrupt will occur each time a capture occurs.
*                   A value of 1 to 3 will cause the interrupt
*                   to delay by the same number of captures.
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_SetInterruptCount(uint8 interruptCount) 
{
    /* This must only set to two bits of the control register associated */
    interruptCount &= SamplingTimer_CTRL_INTCNT_MASK;

    #if (!SamplingTimer_UDB_CONTROL_REG_REMOVED)
        /* Clear the Current Setting */
        SamplingTimer_CONTROL &= ((uint8)(~SamplingTimer_CTRL_INTCNT_MASK));
        /* Write The New Setting */
        SamplingTimer_CONTROL |= interruptCount;
    #endif /* (!SamplingTimer_UDB_CONTROL_REG_REMOVED) */
}
#endif /* SamplingTimer_InterruptOnCaptureCount */


#if (SamplingTimer_UsingHWCaptureCounter)


/*******************************************************************************
* Function Name: SamplingTimer_SetCaptureCount
********************************************************************************
*
* Summary:
*  This function sets the capture count
*
* Parameters:
*  captureCount: A value between 2 and 127 inclusive is valid.  A value of 1
*                to 127 will cause the interrupt to delay by the same number of
*                captures.
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_SetCaptureCount(uint8 captureCount) 
{
    SamplingTimer_CAP_COUNT = captureCount;
}


/*******************************************************************************
* Function Name: SamplingTimer_ReadCaptureCount
********************************************************************************
*
* Summary:
*  This function reads the capture count setting
*
* Parameters:
*  void
*
* Return:
*  Returns the Capture Count Setting
*
*******************************************************************************/
uint8 SamplingTimer_ReadCaptureCount(void) 
{
    return ((uint8)SamplingTimer_CAP_COUNT);
}
#endif /* SamplingTimer_UsingHWCaptureCounter */


/*******************************************************************************
* Function Name: SamplingTimer_ClearFIFO
********************************************************************************
*
* Summary:
*  This function clears all capture data from the capture FIFO
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void SamplingTimer_ClearFIFO(void) 
{
    while(0u != (SamplingTimer_ReadStatusRegister() & SamplingTimer_STATUS_FIFONEMP))
    {
        (void)SamplingTimer_ReadCapture();
    }
}

#endif /* UDB Specific Functions */


/* [] END OF FILE */

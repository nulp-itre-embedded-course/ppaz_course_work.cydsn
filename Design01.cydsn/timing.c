/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "timing.h"

extern uint8 sample_flag;
extern uint16 Fs;

static CY_ISR(SampleTimerIsr)
{
    //(void)SamplingTimer_STATUS;       // the same as SamplingTimer_ReadStatusRegister();
    Timer_ReadStatusRegister();
    sample_flag = 1;
}

void InitTiming(uint16 sample_period)
{
    Timer_Start();
    Timer_WritePeriod(sample_period);
    
    isr_Start();
	isr_SetVector(SampleTimerIsr);
}
/* [] END OF FILE */

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
    SamplingTimer_ReadStatusRegister();
    sample_flag = 1;
}

void InitTiming(uint16 sample_period)
{
    SamplingTimer_Start();
    SamplingTimer_WritePeriod(sample_period);
    
    isrSampleTimer_Start();
	isrSampleTimer_SetVector(SampleTimerIsr);
}
/* [] END OF FILE */

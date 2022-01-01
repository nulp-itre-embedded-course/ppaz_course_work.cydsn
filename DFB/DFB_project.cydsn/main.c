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
#include "project.h"
#include "sin_tab.h"

const uint32 Fcl = 24000000;     // частота тактування таймера
uint32 F0 = 2000; 
uint32 Fs = 10000;        // частота дискретизації, Гц

char number[10];
uint16 count = 0;

void InitTiming(uint16 sample_period);
void sendUART(uint32 value);

CY_ISR_PROTO(Filter_Isr)
{
    uint16 dac_out = Filter_Read16(Filter_CHANNEL_A) + 2040u;
    if (dac_out > 4080)
    {
        dac_out = 4080;
    }
    else if (dac_out < 0)
    {
        dac_out = 0;
    }
   
    
    sendUART(dac_out);
     DVDAC_SetValue(dac_out);
    
    
    
}

static CY_ISR(SampleTimerIsr)
{
    static uint8 i = 0;
    //(void)SamplingTimer_STATUS;       // the same as SamplingTimer_ReadStatusRegister();
    SamplingTimer_ReadStatusRegister();
    Filter_Write16(Filter_CHANNEL_A, input_signal[i & 0x0F] - 2040);
    

    
        sendUART(input_signal[i & 0x0F] - 2040);
     i++;
}

void InitTiming(uint16 sample_period)
{
    SamplingTimer_Start();
    SamplingTimer_WritePeriod(sample_period);
    
    isrSampleTimer_Start();
	isrSampleTimer_SetVector(SampleTimerIsr);
}

void sendUART(uint32 value){
    if(count < 200){
        sprintf(number, "%d", value);               
        UART_PutString(number);                       
        UART_PutString("\r\n");
        count++;
       }
     
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Fs = 15 * F0;

    uint16 sample_period_in_clocks = Fcl/Fs; 
    UART_Start();
    InitTiming(sample_period_in_clocks); 
    isr_Filter_StartEx(Filter_Isr);
    DVDAC_Start();
    Filter_Start();
    

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */

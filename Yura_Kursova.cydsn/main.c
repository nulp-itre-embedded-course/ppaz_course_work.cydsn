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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    UART_Start();

    for(;;)
    {
        if(FhotoRes_Read() == 1)
        {
            UART_PutString("Lamp ON");
            LED_On_Write(1);
        }
        if(FhotoRes_Read() == 0)
        {
            UART_PutString("Lamp OFF");
            LED_On_Write(0);
        }
        if(HidroSns_Read() == 1)
        {
            UART_PutString("Pump ON");
            /*подаэмо сигнал на реле для включення насоса*/
            Pump_On_Write(1);
        }
        if(HidroSns_Read() == 0)
        {
            UART_PutString("Pump OFF");
            /*подаэмо сигнал на реле для включення насоса*/
            Pump_On_Write(0);
        }
        
        CyDelay(200);
    }
}

/* [] END OF FILE */

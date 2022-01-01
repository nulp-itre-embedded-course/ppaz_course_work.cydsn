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
#include "timing.h"
#include "myDAC.h"
#include "sin_tab.h"
#include "tty_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const float PI = 3.1415926;
uint16 F0 = 1000;               // частота вхідного сигналу
const uint16 Fo = 500;          // частота зрізу фільтра, Гц
uint32 Fs = 2500;        // частота дискретизації, Гц
const uint32 Fcl = 24000000;     // частота тактування таймера
const float M = 0.25;       // коефіцієнт пропорційності
const float Q = 0.5;        // добротність

/* масиви відліків вхідного та вихідного сигналів */
float x[4] = {0,0,0,0};
float y[4] = {0,0,0,0};
float a0,a1,a2,b1,b2;  // коефіцієнти фільтра

/* sample_flag встановлюється в 1 кожний інтервал дискретизації перериванням від таймера
і обнуляється 0 вкінці обробки кожного відліку*/
uint8 sample_flag = 0;

void CalculateFilterCoefficients(uint8 f_type);

int main(void)
{
    Fs = F0 * 16;
    int j = 0;                // лічильник   
   
    
    /* розрахувати коефіцієнти фільтра */
    float dT = 1/((float)Fs);       // інтервал дискретизації, с
    float D = 1/Q;                  // коефіцієнт затухання
    
    a0 = (PI*PI*Fo*Fo*dT*dT) / (1 + PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT);
    a1 = 2*a0;
    a2 = a0;
    b1 = 2 * (1 - PI*PI*Fo*Fo*dT*dT) / (1 + PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT);
    b2 = -(1 - PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT) / (1 + PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT);

    char number[10];            // число як "стрічка"
    uint16 dac_out;
    uint16 sample_period_in_clocks = Fcl/Fs;  
    InitTiming(sample_period_in_clocks); 
    InitDac();
    UART_Start();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    for(;;)
    {
        if (sample_flag == 1)           // Момент виводу нового відліку на ЦАП?
        {
            /* Читати значення відліку вхідного сигналу */
            x[j & 0x03] = (float)input_signal[j & (INPUT_SIGNAL_SIZE-1)] - 2040;     

            /* Aлгоритм обробки для фільтра 2-го порядку */
            y[j&0x03] = a0*x[j&0x03]+a1*x[(j-1)&0x03]+a2*x[(j-2)&0x03]+b1*y[(j-1)&0x03]+b2*y[(j-2)&0x03];
            
            /*Вивести значення вихідного відліку ЦФ на ЦАП */
            dac_out = (int16)y[j & 0x03] + 2040;
            UpdateDac(dac_out);
            
            /*Передати значення вхідного та вихідного відліків по UART */
            if(j < 300){
                sprintf(number, "%d", (int16)x[j & 0x03]); 
                UART_PutString(number);                       
                UART_PutString("\r\n");
                sprintf(number, "%d", (int16)y[j & 0x03]); 
                UART_PutString(number);                       
                UART_PutString("\r\n");
                j++;
            }
            
            /* Oчистити прапорець */
            sample_flag = 0;                                
        }
    }
}

//----------------------------------------------------------


/* [] END OF FILE */

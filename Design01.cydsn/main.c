
#include "project.h"
#include "timing.h"
#include "myDAC.h"
#include "sin_tab.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const uint16 SIN_TAB_SIZE = 32;

const float PI = 3.1415926;
uint16 F0 = 8;               // частота вхідного сигналу
const uint16 Fo = 200;          // центраьна частота для фільтрів 2-го порядку, Гц
const uint32 Fs = 2500;        // частота дискретизації, Гц
const uint32 Fcl = 24000000;     // частота тактування таймера
const float Q = 5;        // добротність

/* масиви відліків вхідного та вихідного сигналів */
float x[4] = {0,0,0,0};
float y[4] = {0,0,0,0};
float a0,a1,a2,b1,b2;  // коефіцієнти фільтра

float deg_phase = 0;            // фаза сигналу в градусах
uint16 int_phase = 0;           // фаза перетворена в індекс 
uint16 ratio = 12;             // відношення Fs/F0

/* sample_flag встановлюється в 1 кожний інтервал дискретизації перериванням від таймера
і обнуляється 0 вкінці обробки кожного відліку*/
uint8 sample_flag = 0;

void CalculateFilterCoefficients();

int main(void)
{
    
    uint8 j = 0;                // лічильник   
    CalculateFilterCoefficients();      // розрахувати коефіцієнти фільтра

    char number[10];            // число як "стрічка"
    uint16 dac_out;
    uint16 sample_period_in_clocks = Fcl/Fs;  
    ratio = Fs/F0;
    InitTiming(sample_period_in_clocks); 
    InitDac();
    UART_Start();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    j = 0;
    
    for(;;)
    {
        if (sample_flag == 1)           // Момент виводу нового відліку на ЦАП?
        {
            LED_Write(1);
             deg_phase += 360.0/ratio;   // зміна фази за 1 інтервал дискретизації
             int_phase = (uint16)(deg_phase*SIN_TAB_SIZE/360); // фаза сигналу перерахована в індекс
             dac_out = sin_tab[int_phase & (SIN_TAB_SIZE-1)];
             
            x[j & 0x03] = (float)sin_tab[j & (SIN_TAB_SIZE-1)] - 2040;     // читати значення відліку вхідного сигналу
            y[j&0x03] = a0*x[j&0x03]+a1*x[(j-1)&0x03]+a2*x[(j-2)&0x03]+b1*y[(j-1)&0x03]+b2*y[(j-2)&0x03];
           
            dac_out = (int16)y[j & 0x03] + 2390;
            UpdateDac(dac_out);
            
            sprintf(number, "%d", dac_out);                 // перетворення числа в стрічку
            UART_PutString(number);                       // передати значення відліку по UART
            UART_PutString("\r\n");
            j++;
            sample_flag = 0;                                // очистити прапорець 
            LED_Write(0);
        }
    }
}

//----------------------------------------------------------
/* функція CalculateFilterCoefficients() розраховує коефіцієнти цифрового фільтра */
void CalculateFilterCoefficients()
{
    float dT = 1/((float)Fs);       // інтервал дискретизації, с
    float D = 1/Q;                  // коефіцієнт затухання
         // ФНЧ 2-го порядку
            a0 = (PI*PI*Fo*Fo*dT*dT) / (1 + PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT);
            a1 = 2*a0;
            a2 = a0;
            b1 = 2 * (1 - PI*PI*Fo*Fo*dT*dT) / (1 + PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT);
            b2 = -(1 - PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT) / (1 + PI*Fo*D*dT + PI*PI*Fo*Fo*dT*dT);   
}

/* [] END OF FILE */

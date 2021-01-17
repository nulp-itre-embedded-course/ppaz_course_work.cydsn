#include "common.h"
#include "stdio.h"

#define V_TO_C                                  (0.792)

int main(void)
{
    __enable_irq();

    uint32_t freq;
    uint32_t value;
    uint32_t chan = 0UL;
    char str[50U];

    printf("start\n\r");

    sys_errorLedEnable();
    sys_systemPwmStart();

    clk_systemClkStart(&freq);

    deb_startDebugUart(CLK_HFCLK_0_FREQ_EXP);


    DEB_PRINT("System Init complete\n\r");

    for (;;)
    {
        Cy_SysLib_Delay(500U);
        value = Cy_SAR_CountsTo_Volts(IP_SAR, chan, Cy_SAR_GetResult16(SAR, chan));
        sprintf(str, "Temperature = %f C\n\r", (value / V_TO_C));
        DEB_PRINT(str);
    }
}

/* [] END OF FILE */
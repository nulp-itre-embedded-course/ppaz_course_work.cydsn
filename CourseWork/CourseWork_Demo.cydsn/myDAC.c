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
#include "myDAC.h"

void InitDac(void)
{
    DVDAC_Start();
}

void UpdateDac(uint16 dac_out)
{
    if (dac_out > 4080)
    {
        dac_out = 4080;
    }
    else if (dac_out < 0)
    {
        dac_out = 0;
    }
    DVDAC_SetValue(dac_out);
}
/* [] END OF FILE */

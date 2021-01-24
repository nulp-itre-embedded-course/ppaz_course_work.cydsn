/*******************************************************************************
* File Name: main.c
*
* Version: 3.30
*
* Description:
*  This is source code for the datasheet example of the Real Time Clock (RTC)
*  component.
*
*  The PrintDecNumber() function is implemented in the utils.c file. It displays
*  decimal numbers (first parameter) on a specific row (second parameter) and
*  column (the third parameter) on the Character LCD component, named LCD. If
*  the Character LCD component's name is changed it also should be updated in
*  this function.
*
*  There are interrupt stubs in the RTC ISR. The every second interrupt for this
*  example project is listed below. The active alarm, DST, AM/PM and leap year
*  statuses renew code is removed from the listing below, as it is the same as
*  in the main() function and are described above. The only second value update
*  code is shown below.
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include <project.h>
#include <stdlib.h>
#include "string.h"
#include "stdio.h"
#include "utils.h"
#include "cyapicallbacks.h"





/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Main function performs following functions:
*   1. Declares date and time structure and fill it with the initial values
*   2. Enables global interrupts
*   3. Sets initial time and date values
*   4. Sets alarm date, time and mask
*   5. Sets interval mask
*   6. Sets DST start and stop configuration
*   7. Prints current date and time values.
*   8. Afterwards, device is continuosly switched to the Sleep low power mode.
*      When the 1PPS event occurs device wakes up, ISR is executed and device
*      is switched to the Sleep mode again till the next 1PPS event.
*      For more information refer to the device TRM and System
*      Reference Guide.
*
*   The information on the display is updated in the ISR.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{
    uint8 tmpVar = 0u;

    RTC_TIME_DATE Start;

    /* Fill struct with date and time */
    Start.Sec = 0u;
    Start.Min = 55u;
    Start.Hour = 12u;
    Start.DayOfMonth = 17u;
    Start.Month = 1u;
    Start.Year = 2021u;

    /* Enable all interrupts */
    CyGlobalIntEnable;

    /* Set date and time */
    RTC_WriteTime(&Start);

    /* Set alarm date and time */
    RTC_WriteAlarmSecond(10u);
    RTC_WriteAlarmMinute(57u);
    RTC_WriteAlarmHour(12u);
    RTC_WriteAlarmDayOfMonth(17u);
    RTC_WriteAlarmMonth(1u);
    RTC_WriteAlarmYear(2021u);

    /* Set alarm mask */
    RTC_WriteAlarmMask(RTC_ALARM_MIN_MASK | RTC_ALARM_HOUR_MASK);

    /* Set interval mask - handling of interrupt stubs of the RTC component */
    RTC_WriteIntervalMask(RTC_INTERVAL_SEC_MASK  | RTC_INTERVAL_MIN_MASK   |
                          RTC_INTERVAL_HOUR_MASK | RTC_INTERVAL_DAY_MASK   |
                          RTC_INTERVAL_WEEK_MASK | RTC_INTERVAL_MONTH_MASK |
                          RTC_INTERVAL_YEAR_MASK);

    /* Start RTC */
    RTC_Start();

    /* Start LCD */
    LCD_Start();
    
    /* Start UART */
    UART_Start();

    /* Prepare 0th column */
    LCD_Position(0u, 0u);
    LCD_PrintString("RTC    :  :  ");

    /* Print current time */
    tmpVar = RTC_ReadSecond();
    PrintDecNumber(tmpVar, 0u, 11u);
    tmpVar = RTC_ReadMinute();
    PrintDecNumber(tmpVar, 0u, 8u);
    tmpVar = RTC_ReadHour();
    PrintDecNumber(tmpVar, 0u, 5u);



    /* Get status */
    tmpVar = RTC_ReadStatus();

    /* Get and print daytime AM/PM */
    if(RTC_STATUS_AM_PM & tmpVar)
    {
        LCD_Position(0u, 14u);
        LCD_PrintString("PM");
    }
    else
    {
        LCD_Position(0u, 14u);
        LCD_PrintString("AM");
    }


    /* Get and print alarm status */
    if (RTC_STATUS_AA & tmpVar)
    {
        LCD_Position(1u, 15u);
        LCD_PutChar('A');
    }
    else
    {
        LCD_Position(1u, 15u);
        LCD_PutChar(' ');
    }
    char buf;
    char string[10] = {0};   // Занулити строку при сворені
    char sep[] = "-";
    char* duration;
    uint8_t i = 0;
    unsigned int b;
    char testArey[32];

    while(1u)
    {
        do
        {
            buf = UART_GetChar();
            if(buf != 0u)
            {
                string[i] = buf;
                i++;
            }
        }while('A'!= buf);
        if(string[0] == 's')
        {
            if(string[1] == 'h')
            {
                UART_PutString("Set hour");
                duration = strtok(string, sep);
                while(duration != NULL)
                {
                    UART_PutString(duration);
                    b = atoi(duration);
                    if (b > 0u)
                    {
                       // sprintf(testArey,"Our var = %d; \n", b);
                        RTC_WriteHour((uint8_t)b);
                       // UART_PutString(testArey);
                    }
                    duration = strtok(NULL, sep);
                }
            }
            if(string[1] == 'm')
            {
                UART_PutString("Set minute");
                duration = strtok(string, sep);
                while(duration != NULL)
                {
                    UART_PutString(duration);
                    b = atoi(duration);
                    if (b > 0u)
                    {
                       // sprintf(testArey,"Our var = %d; \n", b);
                        RTC_WriteMinute((uint8_t)b);
                       // UART_PutString(testArey);
                    }
                    duration = strtok(NULL, sep);
                }
            }
        }
        if(string[0] == 'r')
        {
            if(string[1] == 'h')
            {
                
                tmpVar = RTC_ReadAlarmHour();
                sprintf(testArey, "Alarm hour is %d", tmpVar);
                UART_PutString(testArey);
            }
            if(string[1] == 'm')
            {
                
                tmpVar = RTC_ReadAlarmMinute();
                sprintf(testArey, "Alarm minute is %d", tmpVar);
                UART_PutString(testArey);
            }
        }
        if(string[0] == 'a')
        {
            if(string[1] == 'h')
            {
                duration = strtok(string, sep);
                while(duration != NULL)
                {
                    UART_PutString(duration);
                    b = atoi(duration);
                    if (b > 0u)
                    {
                       // sprintf(testArey,"Our var = %d; \n", b);
                        RTC_WriteAlarmHour((uint8_t)b);
                       // UART_PutString(testArey);
                    }
                    duration = strtok(NULL, sep);
                }
            }
            if(string[1] == 'm')
            {
                duration = strtok(string, sep);
                while(duration != NULL)
                {
                    UART_PutString(duration);
                    b = atoi(duration);
                    if (b > 0u)
                    {
                       // sprintf(testArey,"Our var = %d; \n", b);
                        RTC_WriteAlarmMinute((uint8_t)b);
                       // UART_PutString(testArey);
                    }
                    duration = strtok(NULL, sep);
                }
            }
        }
        i = 0;
        memset(string, 0, 9);
       
    }
}



/* [] END OF FILE */

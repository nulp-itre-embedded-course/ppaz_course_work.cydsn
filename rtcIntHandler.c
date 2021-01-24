/*******************************************************************************
* File Name: rtcIntHandler.c
*
* Version: 3.30
*
* Description:
*  This is source code library for the datasheet example project of the
*  Real Time Clock (RTC) component.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/

#include "cyapicallbacks.h"

void RTC_EverySecondHandler_Callback(void)
{
    /* Get and print current seconds */
    temp = RTC_ReadSecond();        
    PrintDecNumber(temp, 0u, 11u);
    
    /* Get and print current hours */
    temp = RTC_ReadHour();
    PrintDecNumber(temp, 0u, 5u); 
    
    /* Get and print current minutes */
    temp = RTC_ReadMinute();
    PrintDecNumber(temp, 0u, 8u);
    
    /* Get status */
    temp = RTC_ReadStatus();
    
    /* Get and print active alarm status */
    if (RTC_STATUS_AA & temp) 
    {
        LCD_Position(1u, 15u);
        LCD_PutChar('A');
    }
    else
    {
        LCD_Position(1u, 15u);
        LCD_PutChar(' ');
    }

  
    /* Get and print AM/PM status */
    if (RTC_STATUS_AM_PM & temp) 
    {
        LCD_Position(0u, 14u);
        LCD_PrintString("PM");
    }
    else
    {
        LCD_Position(0u, 14u);
        LCD_PrintString("AM");
    }    
 
}    
    
void RTC_EveryMinuteHandler_Callback(void)
{
    /* Get and print current minutes */
    temp = RTC_ReadMinute();
    PrintDecNumber(temp, 0u, 8u);
}    
    
void RTC_EveryHourHandler_Callback(void)
{
    /* Get and print current hours */
    temp = RTC_ReadHour();
    PrintDecNumber(temp, 0u, 5u); 
}
    
void RTC_EveryDayHandler_Callback(void)
{
    /* Get and print current day of month */
    temp = RTC_ReadDayOfMonth();    
   // PrintDecNumber(temp, 1u, 0u);
    
    /* Get and print current day of week */
   // temp = RTC_currentTimeDate.DayOfWeek;
    //LCD_Position(1u, 9u);
   // LCD_PutChar(temp + 0x30u);
}    
    
void RTC_EveryMonthHandler_Callback(void)
{
    /* Get and print current month */
    temp = RTC_ReadMonth();
   // PrintDecNumber(temp, 1u, 3u);
}

void RTC_EveryYearHandler_Callback(void)
{
    /* Get and print current year */
    temp = (uint8)(RTC_ReadYear() % 100u);
   // PrintDecNumber(temp, 1u, 6u);     
}


/* [] END OF FILE */

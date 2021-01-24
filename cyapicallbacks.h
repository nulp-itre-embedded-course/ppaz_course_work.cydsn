/*******************************************************************************
* File Name: cyapicallbacks.h
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

#ifndef CYAPICALLBACKS_H
#define CYAPICALLBACKS_H
    
    #include "utils.h"
    #include "RTC.h"
    #include "LCD.h"
    #include "UART.h"
    
    static volatile uint8 temp = 0u;

    /* Callback function prototypes */
    void RTC_EverySecondHandler_Callback(void);
    void RTC_EveryMinuteHandler_Callback(void);
    void RTC_EveryHourHandler_Callback(void);
    void RTC_EveryDayHandler_Callback(void);
    void RTC_EveryMonthHandler_Callback(void);
    void RTC_EveryYearHandler_Callback(void);

    /* Callback defines */
    #define RTC_EVERY_SECOND_HANDLER_CALLBACK
    #define RTC_EVERY_MINUTE_HANDLER_CALLBACK
    #define RTC_EVERY_HOUR_HANDLER_CALLBACK
    #define RTC_EVERY_DAY_HANDLER_CALLBACK
    #define RTC_EVERY_MONTH_HANDLER_CALLBACK
    #define RTC_EVERY_YEAR_HANDLER_CALLBACK
    
#endif /* CYAPICALLBACKS_H */   
/* [] */

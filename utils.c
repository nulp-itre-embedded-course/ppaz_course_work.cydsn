/*******************************************************************************
* File Name: utils.c
*
* Version: 3.30
*
* Description:
*  This is source code library for the datasheet example project of the
*  Real Time Clock (RTC) component.
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

#include "utils.h"
#include <project.h>


/*******************************************************************************
* Function Name: PrintDecNumber
********************************************************************************
*
* Summary:
*  Prints decimal value of the number at a specified row and column of
*  LCD character display named LCD.
*
* Parameters:
*  uint8 num - Number to be printed.
*  uint8 row - Display row where to print.
*  uint8 col - Display column where to print.
*
* Return:
*  None.
*
*******************************************************************************/
void PrintDecNumber(uint8 num, uint8 row, uint8 col) CYREENTRANT
{
    uint8 tmp1 = 0u;
    uint8 tmp10 = 0u;
    LCD_Position(row, col + 1u);

    tmp1 = num % 10u;
    LCD_PutChar(tmp1 + 0x30u);

    tmp10 = num / 10u;

    LCD_Position(row, col);
    LCD_PutChar(tmp10 + 0x30u);
}


/* [] END OF FILE */

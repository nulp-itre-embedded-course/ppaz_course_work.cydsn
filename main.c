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
/*Підключені бібліотеки*/
#include "project.h"
#include "I2C.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

/*об'явлені дефайни*/
#define ADXL345_ADR    (0x53u)
#define ADR_POWER_CTL  (0x2Du)
#define ADR_DATA_X     (0x32u)
#define ADR_DATA_Y     (0x34u)
#define ADR_DATA_Z     (0x36u)

/*Глобальні змінні і масиви*/
uint8 ReBuf[1];
uint8 TrBuf[1];
uint8 dataXYZ[6];
uint8 err;
uint16 delay;
char bufer[32];
/*Прототипи функцій*/
uint8 ADXL345_Read(const uint8 adrRegistr);
void ADXL345_Write(const uint8 adrRegistr, uint8 data);
void ADXL345_ReadDataXYZ (uint8* dataXYZ);
uint16 DistanceFunction(void);


int main(void)
{


    CyGlobalIntEnable; /* Enable global interrupts. */
    /*Функції старту*/
    I2C_Start();
    UART_Start();
    Timer_Start();
    uint16 a;
    ADXL345_Write(ADR_POWER_CTL, 0x08);
    for(;;)
    {
        ADXL345_ReadDataXYZ(dataXYZ);
        a = DistanceFunction();
        sprintf(bufer, "Distance = %d \r\n", a);
        UART_PutString(bufer);
        CyDelay(100);

    }
}

/**********Функція читання регістрів датчика****************/
uint8 ADXL345_Read(const uint8 adrRegistr)
{
    TrBuf[0] = adrRegistr; // adr register DEVID
    err = I2C_MasterSendStart(ADXL345_ADR, 0u);
    if(err == I2C_MSTR_NO_ERROR)
    {
        err = I2C_MasterWriteByte(TrBuf[0]); 
        err = I2C_MasterSendRestart(ADXL345_ADR, 1u);    
        ReBuf[0] = I2C_MasterReadByte(I2C_NAK_DATA);
        I2C_MasterSendStop();
    }
    return ReBuf[0];
}
/************Функція запису в регістр датчика****************/
void ADXL345_Write(const uint8 adrRegistr, uint8 data)
{
    TrBuf[0] = adrRegistr; // adr register DEVID
    err = I2C_MasterSendStart(ADXL345_ADR, 0u);
    if(err == I2C_MSTR_NO_ERROR)
    {
        err = I2C_MasterWriteByte(TrBuf[0]);
        TrBuf[0] = data;
        err = I2C_MasterWriteByte(TrBuf[0]);                
        I2C_MasterSendStop();                       
    }
}
/***************Читання даних по прискорення по трьох осях***************/
void ADXL345_ReadDataXYZ (uint8* dataXYZ)
{
    //ADXL345_Write(ADR_POWER_CTL, 0x08); // Перехід в режим вимірювання
    dataXYZ[0] = ADXL345_Read(ADR_DATA_X);
    dataXYZ[1] = ADXL345_Read(ADR_DATA_X + 1);
    dataXYZ[2] = ADXL345_Read(ADR_DATA_Y);
    dataXYZ[3] = ADXL345_Read(ADR_DATA_Y + 1);
    dataXYZ[4] = ADXL345_Read(ADR_DATA_Z);
    dataXYZ[5] = ADXL345_Read(ADR_DATA_Z + 1);
    
    int16_t x = (int16_t)((dataXYZ[1] << 8) | dataXYZ[0]);
    int16_t y = (int16_t)((dataXYZ[3] << 8) | dataXYZ[2]);
    int16_t z = (int16_t)((dataXYZ[5] << 8) | dataXYZ[4]);
    sprintf(bufer, "X = %d;  Y = %d;  Z = %d; \r\n", x, y,z);
    UART_PutString(bufer);
   // ADXL345_Write(ADR_POWER_CTL, 0x00); // Перехід в режим очікування
}
/***************Вимірювання відстані***************/
uint16 DistanceFunction(void)
{
        Control_Write(0);
        CyDelayUs(2);
        Control_Write(1);
        CyDelayUs(10);
        Control_Write(0);
        CyDelayUs(500);
        
        while(ECHO_Read() == 1){}
        
        return delay = (65535 - Timer_ReadCounter())/58;
}



/* [] END OF FILE */

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
/**/
#include "project.h"
#include "I2C.h"

/**/
#define ADXL345_ADR    (0x53u)
#define ADR_POWER_CTL  (0x2Du)
#define ADR_DATA_X     (0x32u)
#define ADR_DATA_Y     (0x34u)
#define ADR_DATA_Z     (0x36u)

/**/
uint8 ReBuf[1];
uint8 TrBuf[1];
uint16 dataXYZ[3];
uint8 err;

/**/
uint8 ADXL345_Read(const uint8 adrRegistr);
void ADXL345_Write(const uint8 adrRegistr, uint8 data);
void ADXL345_ReadDataXYZ (uint16* dataXYZ);


int main(void)
{


    CyGlobalIntEnable; /* Enable global interrupts. */
    /**/
    I2C_Start();
    UART_Start();
    

    for(;;)
    {

        /* Place your application code here. */
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
void ADXL345_ReadDataXYZ (uint16* dataXYZ)
{
    ADXL345_Write(ADR_POWER_CTL, 0x08); // Перехід в режим вимірювання
    dataXYZ[0] =(dataXYZ[0] & ADXL345_Read(ADR_DATA_X));
    dataXYZ[0] =(dataXYZ[0] & (ADXL345_Read(ADR_DATA_X + 1) << 8));
    dataXYZ[1] =(dataXYZ[1] & ADXL345_Read(ADR_DATA_Y));
    dataXYZ[1] =(dataXYZ[1] & (ADXL345_Read(ADR_DATA_Y + 1) << 8));
    dataXYZ[2] =(dataXYZ[2] & ADXL345_Read(ADR_DATA_Z));
    dataXYZ[2] =(dataXYZ[2] & (ADXL345_Read(ADR_DATA_Z + 1) << 8));
    ADXL345_Write(ADR_POWER_CTL, 0x00); // Перехід в режим очікування
}



/* [] END OF FILE */

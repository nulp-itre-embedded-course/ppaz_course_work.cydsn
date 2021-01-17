/******************************************************************************
 * File:
 * ***************************************************************************/

#include "debug.h"

/******************************************************************************
 * Internal macro
 * ***************************************************************************/
/* UART oversample = 12; BaudRate = 115200 */
#define DEBUG_UART_PERI_DIV_VAL_EXP             (71U) // Actual baudRate - 115740
#define DEBUG_UART_PERI_DIV_VAL_ERROR           (5U)  // Actual baudRate - 111111


/******************************************************************************
 * Internal variable
 * ***************************************************************************/
static const cy_stc_scb_uart_config_t uartConfig =
{
    .uartMode                   = CY_SCB_UART_STANDARD,
    .enableMutliProcessorMode   = false,
    .smartCardRetryOnNack       = false,
    .irdaInvertRx               = false,
    .irdaEnableLowPowerReceiver = false,
    .oversample                 = 12UL,
    .enableMsbFirst             = false,
    .dataWidth                  = 8UL,
    .parity                     = CY_SCB_UART_PARITY_NONE,
    .stopBits                   = CY_SCB_UART_STOP_BITS_1,
    .enableInputFilter          = false,
    .breakWidth                 = 11UL,
    .dropOnFrameError           = false,
    .dropOnParityError          = false,
    .receiverAddress            = 0UL,
    .receiverAddressMask        = 0UL,
    .acceptAddrInFifo           = false,
    .enableCts                  = false,
    .ctsPolarity                = CY_SCB_UART_ACTIVE_LOW,
    .rtsRxFifoLevel             = 0UL,
    .rtsPolarity                = CY_SCB_UART_ACTIVE_LOW,
    .rxFifoTriggerLevel  = 0UL,
    .rxFifoIntEnableMask = 0UL,
    .txFifoTriggerLevel  = 0UL,
    .txFifoIntEnableMask = 0UL,
};


const cy_stc_gpio_pin_config_t uartRxConfig = 
{
    .outVal = COM_PIN_OUTPUT_LOW,
    .driveMode = CY_GPIO_DM_HIGHZ,
    .hsiom = P5_0_SCB5_UART_RX,
    .intEdge = CY_GPIO_INTR_DISABLE,
    .intMask = 0UL,
    .vtrip = CY_GPIO_VTRIP_CMOS,
    .slewRate = CY_GPIO_SLEW_FAST,
    .driveSel = CY_GPIO_DRIVE_1_2,
    .vregEn = 0UL,
    .ibufMode = 0UL,
    .vtripSel = 0UL,
    .vrefSel = 0UL,
    .vohSel = 0UL,
};


const cy_stc_gpio_pin_config_t uartTxConfig = 
{
    .outVal = COM_PIN_OUTPUT_LOW,
    .driveMode = CY_GPIO_DM_STRONG_IN_OFF,
    .hsiom = P5_1_SCB5_UART_TX,
    .intEdge = CY_GPIO_INTR_DISABLE,
    .intMask = 0UL,
    .vtrip = CY_GPIO_VTRIP_CMOS,
    .slewRate = CY_GPIO_SLEW_FAST,
    .driveSel = CY_GPIO_DRIVE_1_2,
    .vregEn = 0UL,
    .ibufMode = 0UL,
    .vtripSel = 0UL,
    .vrefSel = 0UL,
    .vohSel = 0UL,
};


/******************************************************************************
 * Name: deb_startDebugUart
 * ****************************************************************************
 * Description: Init and enable SCB5 in UART mode for debug purpose.
 * ***************************************************************************/
void deb_startDebugUart(uint8_t periFreq)
{
    /* Init UART for debugging */
    (void) Cy_SCB_UART_Init(IP_DEBUG_UART_BLOCK, &uartConfig, NULL);

    /* Init RX and TX pins */
    Cy_GPIO_Pin_Init(IP_DEBUG_UART_RX_PORT, IP_DEBUG_UART_RX_PIN, &uartRxConfig);
    Cy_GPIO_Pin_Init(IP_DEBUG_UART_TX_PORT, IP_DEBUG_UART_TX_PIN, &uartTxConfig);

    /* Connect peripheral divider */
    Cy_SysClk_PeriphDisableDivider(IP_DEBUG_UART_DIV_TYPE, IP_DEBUG_UART_DIV_NUM);
    Cy_SysClk_PeriphAssignDivider(IP_DEBUG_UART_DIV_CONNECTION, IP_DEBUG_UART_DIV_TYPE, IP_DEBUG_UART_DIV_NUM);
    if(periFreq == CLK_HFCLK_0_FREQ_EXP)
    {
        Cy_SysClk_PeriphSetDivider(IP_DEBUG_UART_DIV_TYPE, IP_DEBUG_UART_DIV_NUM, DEBUG_UART_PERI_DIV_VAL_EXP);
    }
    else
    {
        Cy_SysClk_PeriphSetDivider(IP_DEBUG_UART_DIV_TYPE, IP_DEBUG_UART_DIV_NUM, DEBUG_UART_PERI_DIV_VAL_ERROR);
    }
    Cy_SysClk_PeriphEnableDivider(IP_DEBUG_UART_DIV_TYPE, IP_DEBUG_UART_DIV_NUM);

    /* Enable UART */
    Cy_SCB_UART_Enable(IP_DEBUG_UART_BLOCK);
}
/******************************************************************************
 * File:
 * 
 * ***************************************************************************/

#include "system.h"

/******************************************************************************
 * Internal macro
 * ***************************************************************************/
#define SYSTEM_PWM_MASK                         (1U << IP_SYSTEM_PWM_NUM)
#define SYSTEM_PWM_PERI_DIV_VAL                 (99U)
#define SYSTEM_PWM_DIV_VAL                      (CY_TCPWM_PWM_PRESCALER_DIVBY_1)


/******************************************************************************
 * Name: sys_errorLedEnable
 * ****************************************************************************
 * Description:
 * ***************************************************************************/
void sys_errorLedEnable(void)
{
    cy_stc_gpio_pin_config_t conf =
    {
        .outVal    = COM_PIN_OUTPUT_HIGH,
        .driveMode = CY_GPIO_DM_STRONG_IN_OFF,
        .hsiom     = P13_7_GPIO,
        .intEdge   = CY_GPIO_INTR_DISABLE,
        .intMask   = 0u,
        .vtrip     = CY_GPIO_VTRIP_CMOS,
        .slewRate  = CY_GPIO_SLEW_FAST,
        .driveSel  = CY_GPIO_DRIVE_1_2,
        .vregEn    = 0u,
        .ibufMode  = 0u,
        .vtripSel  = 0u,
        .vrefSel   = 0u,
        .vohSel    = 0u,
    };

    Cy_GPIO_Pin_Init(IP_ERROR_LED_PORT, IP_ERROR_LED_PIN, &conf);
}



/******************************************************************************
 * Name: sys_errorHandle
 * ****************************************************************************
 * Description:
 * ***************************************************************************/
void sys_errorHandle()
{
    Cy_GPIO_Set(IP_ERROR_LED_PORT, IP_ERROR_LED_PIN);

    for(;;)
    {
    }
}


/******************************************************************************
 * Name: systemPwmStart
 * ****************************************************************************
 * Description:
 * ***************************************************************************/
void sys_systemPwmStart()
{
    /* Init PWM output */
    cy_stc_gpio_pin_config_t pinConf =
    {
        .outVal    = COM_PIN_OUTPUT_LOW,
        .driveMode = CY_GPIO_DM_STRONG_IN_OFF,
        .hsiom     = P9_4_TCPWM1_LINE0,
        .intEdge   = CY_GPIO_INTR_DISABLE,
        .intMask   = 0U,
        .vtrip     = CY_GPIO_VTRIP_CMOS,
        .slewRate  = CY_GPIO_SLEW_FAST,
        .driveSel  = CY_GPIO_DRIVE_FULL,
        .vregEn    = 0U,
        .ibufMode  = 0U,
        .vtripSel  = 0U,
        .vrefSel   = 0U,
        .vohSel    = 0U,
    };

    Cy_GPIO_Pin_Init(IP_SYSTEM_PWM_OUTPUT_PORT, IP_SYSTEM_PWM_OUTPUT_PIN, &pinConf);

    /* Connect peripheral divider */
    Cy_SysClk_PeriphDisableDivider(IP_SYSTEM_PWM_DIV_TYPE, IP_SYSTEM_PWM_DIV_NUM);
    Cy_SysClk_PeriphAssignDivider(IP_SYSTEM_PWM_DIV_CONNECTION, IP_SYSTEM_PWM_DIV_TYPE, IP_SYSTEM_PWM_DIV_NUM);
    Cy_SysClk_PeriphSetDivider(IP_SYSTEM_PWM_DIV_TYPE, IP_SYSTEM_PWM_DIV_NUM, SYSTEM_PWM_PERI_DIV_VAL);
    Cy_SysClk_PeriphEnableDivider(IP_SYSTEM_PWM_DIV_TYPE, IP_SYSTEM_PWM_DIV_NUM);

    /* Init PWM */
    cy_stc_tcpwm_pwm_config_t pwmConf =
    {
        .pwmMode               = CY_TCPWM_PWM_MODE_PWM,
        .clockPrescaler        = SYSTEM_PWM_DIV_VAL,
        .pwmAlignment          = CY_TCPWM_PWM_RIGHT_ALIGN, /* PWM signal is left aligned, meaning it starts high */
        .deadTimeClocks        = 0u, /* dead time feature is disabled */
        .runMode               = CY_TCPWM_PWM_CONTINUOUS, /* Wrap around at terminal count. */
        .period0               = 999u, /* Period of 100 (0-99). Terminal count event when rolls over back to 0. */
        .period1               = 0u, /* Period of 200 (0-199). Terminal count event when rolls over back to 0. */ /* Not used is this mode */
        .enablePeriodSwap      = true, /* period swapping feature is enabled */
        .compare0              = 500u, /* duty cycle 33% (with period 100) */
        .compare1              = 0u, /* duty cycle 33% (with period 200) */ /* Not used is this mode */
        .enableCompareSwap     = true, /* compare swapping feature is enabled */
        .interruptSources      = CY_TCPWM_INT_NONE, /* interrupt will rise on terminal count */
        .invertPWMOut          = 0u, /* Not invert */
        .invertPWMOutN         = 0u, /* Not invert */
        .killMode              = CY_TCPWM_PWM_STOP_ON_KILL, /* PWM stops counting on kill */ /* Not used is this mode */
        .swapInputMode         = CY_TCPWM_INPUT_RISINGEDGE,
        .swapInput             = CY_TCPWM_INPUT_0,
        .reloadInputMode       = CY_TCPWM_INPUT_RISINGEDGE,
        .reloadInput           = CY_TCPWM_INPUT_0,
        .startInputMode        = CY_TCPWM_INPUT_RISINGEDGE,
        .startInput            = CY_TCPWM_INPUT_0,
        .killInputMode         = CY_TCPWM_INPUT_RISINGEDGE,
        .killInput             = CY_TCPWM_INPUT_0,
        .countInputMode        = CY_TCPWM_INPUT_LEVEL, /* Set this input to LEVEL and 1 (high logic level) */
        .countInput            = CY_TCPWM_INPUT_1, /* So the PWM will be enabled forever */
    };

    if(CY_TCPWM_SUCCESS != Cy_TCPWM_PWM_Init(IP_SYSTEM_PWM_BLOCK, IP_SYSTEM_PWM_NUM, &pwmConf))
    {

    }

    Cy_TCPWM_PWM_Enable(IP_SYSTEM_PWM_BLOCK, IP_SYSTEM_PWM_NUM);
    Cy_TCPWM_TriggerStart_Single(IP_SYSTEM_PWM_BLOCK, IP_SYSTEM_PWM_NUM);
}
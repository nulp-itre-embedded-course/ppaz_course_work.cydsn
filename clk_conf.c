# include "clk_conf.h"


/******************************************************************************
 * Function prototype
 * ***************************************************************************/
static bool pllStart(void);
static bool bleEcoStart(void);


/******************************************************************************
 * Internal macro
 * ***************************************************************************/
#define BLE_ECO_C_LOAD                          ()
#define BLE_ECO_XTAL_START_UP_TIME              ()


/******************************************************************************
 * Internal variable
 * ***************************************************************************/
static const cy_stc_pll_manual_config_t pllConfig =
{
    .feedbackDiv = 25U,
    .referenceDiv = 1U,
    .outputDiv = 2U,
    .lfMode = false,
    .outputMode = CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT,
};

/******************************************************************************
 * Group External Function
 * ***************************************************************************/


/******************************************************************************
 * Name: systemClkStart
 * ****************************************************************************
 * Description:
 * Config clock system tree:
 * - ECO and WCO as clock source
 * ***************************************************************************/
clk_stc_systemClkStartStatus_t clk_systemClkStart(uint8_t *hfClkOutputFreq)
{
    clk_stc_systemClkStartStatus_t status = 
    {
        .hfClockStatus = CLK_SYSTEM_HF_START_SUCCESS,
        .lfClockStatus = CLK_SYSTEM_LF_START_SUCCESS,
        .bleClockStatus = CLK_SYSTEM_BLE_START_SUCCESS,
    };

    /**********************************
     * Config High frecuancy clock
     * *******************************/

    /* Set wait states. Set max output freq of cores to prevent a cores freezes */
    Cy_SysLib_SetWaitStates(false, CLK_HFCLK_0_FREQ_EXP);

    /* Config temporary clk path - 2 (source clock for HfClk[0] - IMO) for
    enable BLE ECO and FLL through clk path - 0 */
    Cy_SysClk_ClkPathSetSource(CLK_TEMP_PATH_MUX, CY_SYSCLK_CLKPATH_IN_IMO);
    Cy_SysClk_ClkHfSetSource(CLK_HFCLK_0_NUM, CY_SYSCLK_CLKHF_IN_CLKPATH2);
    Cy_SysClk_ClkHfSetDivider(CLK_HFCLK_0_NUM, CY_SYSCLK_CLKHF_NO_DIVIDE);

    /* Set IMO as input clock source for path - 0. */
    Cy_SysClk_ClkPathSetSource(CLK_MAIN_PATH_MUX, CY_SYSCLK_CLKPATH_IN_IMO);

    /* Start PLL */
    if(!pllStart())
    {
        status.hfClockStatus = CLK_SYSTEM_HF_START_PLL_FAIL;
    }
    else
    {
        /* Config HfClk[0], PeriClock, Fast and Slow clock.*/
        Cy_SysClk_ClkFastSetDivider(CLK_FAST_CLK_DIV);
        Cy_SysClk_ClkPeriSetDivider(CLK_PERI_CLK_DIV);
        Cy_SysClk_ClkSlowSetDivider(CLK_SLOW_CLK_DIV);

        /* Reconfig clk path. PLL works and now is prepare to be as clock
        source for HfClk[0] */
        Cy_SysClk_ClkHfSetSource(CLK_HFCLK_0_NUM, CY_SYSCLK_CLKHF_IN_CLKPATH1);
    }

    SystemCoreClockUpdate();

    /**********************************
     * Config Low frecuancy clock
     * *******************************/

    /* Config WCO clock */

    /* Config LfClk */

    /* Config BLE clock */

    return status;
}


/******************************************************************************
 * Name:
 * ****************************************************************************
 * Description:
 *
 * Input:
 * 
 * Return: true - config success.
 *         false - some errors happen.
 * ***************************************************************************/
// bool bleEcoStart()
// {
//     bool status;

//     if (CY_BLE_ECO_SUCCESS != Cy_BLE_EcoConfigure(CY_BLE_BLESS_ECO_FREQ_32MHZ, CY_BLE_SYS_ECO_CLK_DIV_1,
//                         BLE_ECO_C_LOAD, BLE_ECO_XTAL_START_UP_TIME, CY_BLE_ECO_VOLTAGE_REG_AUTO))
//     {
//         status = false;
//     }

//     return false;
// }

/******************************************************************************
 * Name:
 * ****************************************************************************
 * Description:
 *
 * Input:
 * 
 * Return: true - config success.
 *         false - pll didn't start in expected time.
 * ***************************************************************************/
bool pllStart(void)
{
    bool status = true;

    /* Check if PLL enable */
    if(Cy_SysClk_PllIsEnabled(CLK_PLL_CLOCK_PATH_NUM))
    {
        Cy_SysClk_PllDisable(CLK_PLL_CLOCK_PATH_NUM);
    }

    /* Config PLL */
    Cy_SysClk_PllManualConfigure(CLK_PLL_CLOCK_PATH_NUM, &pllConfig);

    if(CY_SYSCLK_SUCCESS != Cy_SysClk_PllEnable(CLK_PLL_CLOCK_PATH_NUM, CLK_PLL_TIMEOUT))
    {
        status = false;
    }

    return status;
}
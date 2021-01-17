#include "sar.h"


/******************************************************************************
 * Internal macro
 * ***************************************************************************/
/* Pre definition macros */
/* Sample Time 
 * Tacr >= 9 * (Rsrc + Rmux + Racqsw) * Csh
 * */
#define ADC_CLOCK_CYCLES_FOR_SAMPLE             (135U)

/* The minimum sample time is 167ns */
#define ADC_CLOCK_CYCLES_FOR_SAMPLE_MIN         (4U)

/* Channel 0 Enable bit mask */
#define CHANNEL_0_ENABLE_BIT_MASK               (1U)


/* Macros for Config structure */
#define CTRL                                      (uint32_t)CY_SAR_VREF_PWR_100\
                                                | (uint32_t)CY_SAR_VREF_SEL_VDDA\
                                                | (uint32_t)CY_SAR_BYPASS_CAP_ENABLE\
                                                | (uint32_t)CY_SAR_NEG_SEL_VREF\
                                                | (uint32_t)CY_SAR_CTRL_NEGVREF_HW\
                                                | (uint32_t)CY_SAR_CTRL_COMP_DLY_2P5\
                                                | (uint32_t)CY_SAR_COMP_PWR_100\
                                                | (uint32_t)CY_SAR_DEEPSLEEP_SARMUX_OFF\
                                                | (uint32_t)CY_SAR_SARSEQ_SWITCH_ENABLE

#define SAMPLE_CTRL                               (uint32_t)CY_SAR_RIGHT_ALIGN\
                                                | (uint32_t)CY_SAR_SINGLE_ENDED_UNSIGNED\
                                                | (uint32_t)CY_SAR_DIFFERENTIAL_SIGNED\
                                                | (uint32_t)CY_SAR_AVG_MODE_SEQUENTIAL_FIXED\
                                                | (uint32_t)CY_SAR_AVG_CNT_2\
                                                | (uint32_t)CY_SAR_TRIGGER_MODE_FW_ONLY

/* Only sample times 1 is used */
#define SAMPLE_TIME_01                            (ADC_CLOCK_CYCLES_FOR_SAMPLE << CY_SAR_SAMPLE_TIME0_SHIFT)\
                                                | (ADC_CLOCK_CYCLES_FOR_SAMPLE_MIN << CY_SAR_SAMPLE_TIME1_SHIFT)

/* Only sample times 1 is used */
#define SAMPLE_TIME_23                            (ADC_CLOCK_CYCLES_FOR_SAMPLE_MIN << CY_SAR_SAMPLE_TIME2_SHIFT)\
                                                | (ADC_CLOCK_CYCLES_FOR_SAMPLE_MIN << CY_SAR_SAMPLE_TIME3_SHIFT)

#define RANGE_THRES                             (0x300uL  << CY_SAR_RANGE_LOW_SHIFT) | (0xC00uL  << CY_SAR_RANGE_HIGH_SHIFT)

#define CHANNEL_ENABLE                          CHANNEL_0_ENABLE_BIT_MASK

#define CHANNEL_0_CONFIG                          (uint32_t)CY_SAR_CHAN_SINGLE_ENDED\
                                                | (uint32_t)CY_SAR_CHAN_SAMPLE_TIME_0\
                                                | (uint32_t)CY_SAR_POS_PORT_ADDR_SARMUX\
                                                | (uint32_t)CY_SAR_CHAN_POS_PIN_ADDR_1\
                                                | CY_SAR_CHAN_AVG_DISABLE

#define CHANNEL_CONFIG                          {(uint32_t)CHANNEL_0_CONFIG,\
                                                0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U,0U}

#define MUX_SWITCH                              CY_SAR_MUX_FW_P1_VPLUS

#define MUX_SWITCH_SQ_CTRL                      CY_SAR_MUX_SQ_CTRL_P1

static const cy_stc_sar_config_t sarConfig =
{
    .ctrl = CTRL,
    .sampleCtrl = SAMPLE_CTRL,
    .sampleTime01 = SAMPLE_TIME_01,
    .sampleTime23 = SAMPLE_TIME_23,
    .rangeThres = RANGE_THRES,
    .rangeCond = CY_SAR_RANGE_COND_BELOW,
    .chanEn = CHANNEL_ENABLE,
    .chanConfig = CHANNEL_CONFIG,
    .intrMask = 0U,
    .satIntrMask = 0U,
    .rangeIntrMask = 0U,
    .muxSwitch = MUX_SWITCH,
    .muxSwitchSqCtrl = MUX_SWITCH_SQ_CTRL,
    .configRouting = true,
    .vrefMvValue = 3300u,


    .clock = CY_SAR_CLK_PERI,
    .fifoCfgPtr = NULL,
    .trTimer = false,
    .scanCnt = false,
    .scanCntIntr = false,
};

const cy_stc_gpio_pin_config_t SAR_PIN = 
{
	.outVal = 1,
	.driveMode = CY_GPIO_DM_ANALOG,
	.hsiom = HSIOM_SEL_GPIO,
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
void startSar(void)
{
    cy_en_sar_status_t status;
    status = Cy_SAR_Init(IP_SAR, &sarConfig);

    /* Connect peripheral divider */
    Cy_SysClk_PeriphDisableDivider(IP_SAR_DIV_TYPE, IP_SAR_DIV_NUM);
    Cy_SysClk_PeriphAssignDivider(IP_SAR_DIV_CONNECTION, IP_SAR_DIV_TYPE, IP_SAR_DIV_NUM);
    Cy_SysClk_PeriphSetDivider(IP_SAR_DIV_TYPE, IP_SAR_DIV_NUM, SAR_DIV_VAL);
    Cy_SysClk_PeriphEnableDivider(IP_SAR_DIV_TYPE, IP_SAR_DIV_NUM);

    Cy_GPIO_Pin_Init(GPIO_PRT10, 1U, &SAR_PIN);

    if (CY_SAR_SUCCESS == status)
    {
        /* Turn on the SAR hardware. */
        Cy_SAR_Enable(IP_SAR);
        /* Begin continuous conversions. */
        Cy_SAR_StartConvert(IP_SAR, CY_SAR_START_CONVERT_CONTINUOUS);
    }
}
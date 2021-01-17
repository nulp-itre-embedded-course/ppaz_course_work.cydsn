/******************************************************************************
 * File:
 * 
 * ***************************************************************************/


#if !defined(_CLK_CONFIG_H)
#define _CLK_CONFIG_H

#include "common.h"


/******************************************************************************
 * Enums
 * ***************************************************************************/
typedef enum
{
    CLK_SYSTEM_HF_START_SUCCESS = 0U,
    /* Timeout happen, PLL doesn't start */
    CLK_SYSTEM_HF_START_PLL_FAIL = 1U,
} clk_enum_HfClocks_Status_t;

typedef enum
{
    CLK_SYSTEM_LF_START_SUCCESS = 0U,
} clk_enum_LfClocks_Status_t;

typedef enum
{
    CLK_SYSTEM_BLE_START_SUCCESS = 0U,
} clk_enum_BleClocks_Status_t;


/******************************************************************************
 * Structures
 * ***************************************************************************/
typedef struct clk_enum_systemClkStartStatus
{
    clk_enum_HfClocks_Status_t  hfClockStatus;
    clk_enum_LfClocks_Status_t  lfClockStatus;
    clk_enum_BleClocks_Status_t bleClockStatus;
} clk_stc_systemClkStartStatus_t;


/******************************************************************************
 * Macro
 * ***************************************************************************/
#define CLK_IMO_FREQ                            (8U)

#define CLK_PLL_CLOCK_PATH_NUM                  (1U)
#define CLK_PLL_TIMEOUT                         (1000U) /* us */
#define CLK_PLL_INPUT_FREQ                      (CLK_IMO_FREQ)
#define CLK_PLL_OUTPUT_FREQ                     (100U)

#define CLK_HFCLK_0_NUM                         (0U)
#define CLK_HFCLK_0_FREQ_EXP                    (CLK_PLL_OUTPUT_FREQ) /* MHz */
#define CLK_HFCLK_0_FREQ_ERROR                  (CLK_IMO_FREQ)

#define CLK_FAST_CLK_DIV                        (0U)
#define CLK_SLOW_CLK_DIV                        (0U)
#define CLK_PERI_CLK_DIV                        (0U)

#define CLK_MAIN_PATH_MUX                       (0U)
#define CLK_TEMP_PATH_MUX                       (2U)


/******************************************************************************
 *       Function Prototypes
 * ***************************************************************************/
clk_stc_systemClkStartStatus_t clk_systemClkStart(uint8_t *hfClkOutputFreq);


#endif /* _CLK_CONFIG_H */
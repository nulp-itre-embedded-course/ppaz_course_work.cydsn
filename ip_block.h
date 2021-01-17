/******************************************************************************
 * File: ip_block
 * Provide list of IP block which are used.
 * ***************************************************************************/

#if !defined(_IP_BLOCK_H)
#define _IP_BLOCK_H

#include "common.h"


/******************************************************************************
 * Peripheral Clock Dividers
 * ***************************************************************************/
/* 8-bit dividers */
#define IP_SYSTEM_PWM_DIV_TYPE                  (CY_SYSCLK_DIV_8_BIT)
#define IP_SYSTEM_PWM_DIV_NUM                   (0U)

#define IP_DEBUG_UART_DIV_TYPE                  (CY_SYSCLK_DIV_8_BIT)
#define IP_DEBUG_UART_DIV_NUM                   (1U)

#define IP_SAR_DIV_TYPE                         (CY_SYSCLK_DIV_8_BIT)
#define IP_SAR_DIV_NUM                          (5U)


/* 16-bit dividers */


/* 16.5-bit dividers */


/* 24.5-bit dividers */


/* Divider clock connections */
#define IP_SYSTEM_PWM_DIV_CONNECTION            (PCLK_TCPWM1_CLOCKS0)
#define IP_DEBUG_UART_DIV_CONNECTION            (PCLK_SCB5_CLOCK)
#define IP_SAR_DIV_CONNECTION                   (PCLK_PASS_CLOCK_SAR)


/******************************************************************************
 * GPIO
 * ***************************************************************************/
/* Debug uart RX pin */
#define IP_DEBUG_UART_RX_PORT                   (GPIO_PRT5)
#define IP_DEBUG_UART_RX_PIN                    (0U)

/* Debug uart TX pin */
#define IP_DEBUG_UART_TX_PORT                   (GPIO_PRT5)
#define IP_DEBUG_UART_TX_PIN                    (1U)

/* System PWM output */
#define IP_SYSTEM_PWM_OUTPUT_PORT               (GPIO_PRT9)
#define IP_SYSTEM_PWM_OUTPUT_PIN                (4U)


/* Error led */
#define IP_ERROR_LED_PORT                       (GPIO_PRT13)
#define IP_ERROR_LED_PIN                        (7U)


/******************************************************************************
 * TCPWM 16-bit
 * ***************************************************************************/
/* System PWM */
#define IP_SYSTEM_PWM_BLOCK                     (TCPWM1)
#define IP_SYSTEM_PWM_NUM                       (0U)


/******************************************************************************
 * SCB
 * ***************************************************************************/
/* Debug UART */
#define IP_DEBUG_UART_BLOCK                     (SCB5)


/******************************************************************************
 * SAR
 * ***************************************************************************/
#define IP_SAR                                  (SAR)


#endif /* _IP_BLOCK_H */
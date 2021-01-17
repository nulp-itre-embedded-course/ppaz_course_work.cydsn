/******************************************************************************
 * File: common.h
 * All external units start from: COM_
 * Contain general macros.
 * ***************************************************************************/

#if !defined(_COMMON_H)
#define _COMMON_H

#include "cy_pdl.h"

#include "ip_block.h"

#include "clk_conf.h"
#include "debug.h"
#include "system.h"
#include "sar.h"


/******************************************************************************
 * Common macros
 * ***************************************************************************/
#define COM_PIN_OUTPUT_HIGH                     (1U)
#define COM_PIN_OUTPUT_LOW                      (0U)

#define COM_MHZ                                 (1000000U)

#endif /* _COMMON_H */
#include "Filter.h"
#include "Filter_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is: Biquad
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelABiquadCoefficients Filter_ChannelABiquadCoefficients

/* Number of Biquad sections are: 1 */

const uint8 CYCODE Filter_ChannelABiquadCoefficients[Filter_BIQUAD_A_SIZE] = 
{
 /* Coefficients of Section 0 */
 0x9Au, 0xDEu, 0x01u, 0x00u, /* Section(0)_A0, 0.0292115211486816 */

 0x34u, 0xBDu, 0x03u, 0x00u, /* Section(0)_A1, 0.0584230422973633 */

 0x9Au, 0xDEu, 0x01u, 0x00u, /* Section(0)_A2, 0.0292115211486816 */

 0xB1u, 0x60u, 0x58u, 0x00u, /* Section(0)_B1, -1.3809015750885 */

 0xF6u, 0x24u, 0xE0u, 0x00u, /* Section(0)_B2, 0.497744083404541 */
};


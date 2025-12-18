/*******************************************************************************
* File Name: CK.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CK_ALIASES_H) /* Pins CK_ALIASES_H */
#define CY_PINS_CK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CK_0			(CK__0__PC)
#define CK_0_PS		(CK__0__PS)
#define CK_0_PC		(CK__0__PC)
#define CK_0_DR		(CK__0__DR)
#define CK_0_SHIFT	(CK__0__SHIFT)
#define CK_0_INTR	((uint16)((uint16)0x0003u << (CK__0__SHIFT*2u)))

#define CK_INTR_ALL	 ((uint16)(CK_0_INTR))


#endif /* End Pins CK_ALIASES_H */


/* [] END OF FILE */

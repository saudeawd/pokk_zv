/*******************************************************************************
* File Name: CK.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "CK.h"

static CK_BACKUP_STRUCT  CK_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CK_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet CK_SUT.c usage_CK_Sleep_Wakeup
*******************************************************************************/
void CK_Sleep(void)
{
    #if defined(CK__PC)
        CK_backup.pcState = CK_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CK_backup.usbState = CK_CR1_REG;
            CK_USB_POWER_REG |= CK_USBIO_ENTER_SLEEP;
            CK_CR1_REG &= CK_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CK__SIO)
        CK_backup.sioState = CK_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CK_SIO_REG &= (uint32)(~CK_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CK_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to CK_Sleep() for an example usage.
*******************************************************************************/
void CK_Wakeup(void)
{
    #if defined(CK__PC)
        CK_PC = CK_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CK_USB_POWER_REG &= CK_USBIO_EXIT_SLEEP_PH1;
            CK_CR1_REG = CK_backup.usbState;
            CK_USB_POWER_REG &= CK_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CK__SIO)
        CK_SIO_REG = CK_backup.sioState;
    #endif
}


/* [] END OF FILE */

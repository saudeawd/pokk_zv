/*******************************************************************************
* File Name: CK.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CK_H) /* Pins CK_H */
#define CY_PINS_CK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CK_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} CK_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CK_Read(void);
void    CK_Write(uint8 value);
uint8   CK_ReadDataReg(void);
#if defined(CK__PC) || (CY_PSOC4_4200L) 
    void    CK_SetDriveMode(uint8 mode);
#endif
void    CK_SetInterruptMode(uint16 position, uint16 mode);
uint8   CK_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CK_Sleep(void); 
void CK_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CK__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CK_DRIVE_MODE_BITS        (3)
    #define CK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CK_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CK_SetDriveMode() function.
         *  @{
         */
        #define CK_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CK_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CK_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CK_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CK_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CK_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CK_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CK_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CK_MASK               CK__MASK
#define CK_SHIFT              CK__SHIFT
#define CK_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CK_SetInterruptMode() function.
     *  @{
     */
        #define CK_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CK_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CK_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CK_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CK__SIO)
    #define CK_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CK__PC) && (CY_PSOC4_4200L)
    #define CK_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CK_USBIO_DISABLE              ((uint32)(~CK_USBIO_ENABLE))
    #define CK_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CK_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CK_USBIO_ENTER_SLEEP          ((uint32)((1u << CK_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CK_USBIO_SUSPEND_DEL_SHIFT)))
    #define CK_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CK_USBIO_SUSPEND_SHIFT)))
    #define CK_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CK_USBIO_SUSPEND_DEL_SHIFT)))
    #define CK_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CK__PC)
    /* Port Configuration */
    #define CK_PC                 (* (reg32 *) CK__PC)
#endif
/* Pin State */
#define CK_PS                     (* (reg32 *) CK__PS)
/* Data Register */
#define CK_DR                     (* (reg32 *) CK__DR)
/* Input Buffer Disable Override */
#define CK_INP_DIS                (* (reg32 *) CK__PC2)

/* Interrupt configuration Registers */
#define CK_INTCFG                 (* (reg32 *) CK__INTCFG)
#define CK_INTSTAT                (* (reg32 *) CK__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CK_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CK__SIO)
    #define CK_SIO_REG            (* (reg32 *) CK__SIO)
#endif /* (CK__SIO_CFG) */

/* USBIO registers */
#if !defined(CK__PC) && (CY_PSOC4_4200L)
    #define CK_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CK_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CK_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CK_DRIVE_MODE_SHIFT       (0x00u)
#define CK_DRIVE_MODE_MASK        (0x07u << CK_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CK_H */


/* [] END OF FILE */

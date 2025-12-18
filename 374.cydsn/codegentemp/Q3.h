/*******************************************************************************
* File Name: Q3.h  
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

#if !defined(CY_PINS_Q3_H) /* Pins Q3_H */
#define CY_PINS_Q3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Q3_aliases.h"


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
} Q3_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Q3_Read(void);
void    Q3_Write(uint8 value);
uint8   Q3_ReadDataReg(void);
#if defined(Q3__PC) || (CY_PSOC4_4200L) 
    void    Q3_SetDriveMode(uint8 mode);
#endif
void    Q3_SetInterruptMode(uint16 position, uint16 mode);
uint8   Q3_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Q3_Sleep(void); 
void Q3_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Q3__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Q3_DRIVE_MODE_BITS        (3)
    #define Q3_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Q3_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Q3_SetDriveMode() function.
         *  @{
         */
        #define Q3_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Q3_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Q3_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Q3_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Q3_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Q3_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Q3_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Q3_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Q3_MASK               Q3__MASK
#define Q3_SHIFT              Q3__SHIFT
#define Q3_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Q3_SetInterruptMode() function.
     *  @{
     */
        #define Q3_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Q3_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Q3_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Q3_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Q3__SIO)
    #define Q3_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Q3__PC) && (CY_PSOC4_4200L)
    #define Q3_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Q3_USBIO_DISABLE              ((uint32)(~Q3_USBIO_ENABLE))
    #define Q3_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Q3_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Q3_USBIO_ENTER_SLEEP          ((uint32)((1u << Q3_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Q3_USBIO_SUSPEND_DEL_SHIFT)))
    #define Q3_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Q3_USBIO_SUSPEND_SHIFT)))
    #define Q3_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Q3_USBIO_SUSPEND_DEL_SHIFT)))
    #define Q3_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Q3__PC)
    /* Port Configuration */
    #define Q3_PC                 (* (reg32 *) Q3__PC)
#endif
/* Pin State */
#define Q3_PS                     (* (reg32 *) Q3__PS)
/* Data Register */
#define Q3_DR                     (* (reg32 *) Q3__DR)
/* Input Buffer Disable Override */
#define Q3_INP_DIS                (* (reg32 *) Q3__PC2)

/* Interrupt configuration Registers */
#define Q3_INTCFG                 (* (reg32 *) Q3__INTCFG)
#define Q3_INTSTAT                (* (reg32 *) Q3__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Q3_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Q3__SIO)
    #define Q3_SIO_REG            (* (reg32 *) Q3__SIO)
#endif /* (Q3__SIO_CFG) */

/* USBIO registers */
#if !defined(Q3__PC) && (CY_PSOC4_4200L)
    #define Q3_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Q3_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Q3_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Q3_DRIVE_MODE_SHIFT       (0x00u)
#define Q3_DRIVE_MODE_MASK        (0x07u << Q3_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Q3_H */


/* [] END OF FILE */

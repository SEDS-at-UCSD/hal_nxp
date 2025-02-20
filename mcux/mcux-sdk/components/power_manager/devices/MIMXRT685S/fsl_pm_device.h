/*
 * Copyright 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_PM_DEVICE_H_
#define _FSL_PM_DEVICE_H_

#include "fsl_common.h"

#include "fsl_pm_config.h"

/*!
 * @addtogroup PM Framework: Power Manager Framework
 * @brief This section includes Power Mode macros, System Constraints macros, and Wakeup source macros.
 * @{
 */

/*!
 * @name Power Mode Definition
 * @{
 */

/* Power Mode Index */
#define PM_LP_STATE_SLEEP                (0U)
#define PM_LP_STATE_DEEP_SLEEP           (1U)
#define PM_LP_STATE_DEEP_POWER_DOWN      (2U)
#define PM_LP_STATE_FULL_DEEP_POWER_DOWN (3U)
#define PM_LP_STATE_NO_CONSTRAINT        (0xFFU)

/* @} */

/* Helper macros */
#define PM_RESC_MASK(resc_masks, resc) (resc_masks->rescMask[resc / 32L] >> (resc % 32L)) & 1U
#define PM_RESC_GROUP(resc_groups, resc) (resc_groups->groupSlice[resc / 8] >> (4 * (resc % 8))) & 0xFU

/*!
 * @name System basic resource constraints definitions.
 * @{
 */

/*! @brief Available constraints for resources
 *
 *  The constraints below are grouped together in 3 groups
 */

typedef enum _resc_name
{
    /* Peripherals and RAMs that do not have separate retention bit */
    kResc_MAIN_CLK        = 0,   /*!< Main Clock */
    kResc_VDDCOREREG_HP      ,   /*!< VDDCORE Regulator */
    kResc_PMCREF_HP          ,   /*!< PMC Reference */
    kResc_HVD1V8             ,   /*!< 1.8V High-Voltage Detect */
    kResc_PORCORE_HP         ,   /*!< VDDCORE Power-On Reset monitor */
    kResc_LVDCORE_HP         ,   /*!< VDDCORE Low-Voltage Detect */
    kResc_HVDCORE            ,   /*!< VDDCORE High-Voltage Detect */
    kResc_SYSXTAL            ,   /*!< System crystal oscillator */
    kResc_LPOSC              ,   /*!< Low-Power Oscillator */
    kResc_SFRO               ,   /*!< SFRO 16 MHz internal oscillator */
    kResc_FFRO               ,   /*!< FFRO 48/60 MHz internal oscillator */
    kResc_SYSPLLLDO          ,   /*!< LDO for System PLL */
    kResc_SYSPLLANA          ,   /*!< Analog for System PLL */
    kResc_AUDIOPLLLDO        ,   /*!< LDO for Audio PLL */
    kResc_AUDIOPLLANA        ,   /*!< Analog for Audio PLL */
    kResc_ADC_ACTIVE         ,   /*!< ADC Powered */
    kResc_ADC_TEMP           ,   /*!< ADC Temperature sensor */
    kResc_ACMP               ,   /*!< Analog Comparator */
    kResc_ROM                ,   /*!< ROM */

     /* dedicated peripheral SRAMs that have 2 bits each in PDSLEEPCFG1 */
    kResc_SRAM_PQ            ,   /*!< PowerQuad SRAM */
    kResc_SRAM_FLEXSPI       ,   /*!< FlexSPI SRAM */
    kResc_SRAM_USB           ,   /*!< USB SRAM */
    kResc_SRAM_USDHC0        ,   /*!< uSDHC0 SRAM */
    kResc_SRAM_USDHC1        ,   /*!< uSDHC1 SRAM */
    kResc_SRAM_CASPER        ,   /*!< CASPER SRAM */
    kResc_SRAM_DSPCACHE      ,   /*!< DSP CACHE SRAM */
    kResc_SRAM_DSPTCM        ,   /*!< DSP TCM SRAM */

     /* System SRAMs that have bits in both PDSLEEPCFG2 & 3 */
    kResc_SRAM0_32KB         ,   /*!< SRAM partition0 */
    kResc_SRAM1_32KB         ,   /*!< SRAM partition1 */
    kResc_SRAM2_32KB         ,   /*!< SRAM partition2 */
    kResc_SRAM3_32KB         ,   /*!< SRAM partition3 */
    kResc_SRAM4_32KB         ,   /*!< SRAM partition4 */
    kResc_SRAM5_32KB         ,   /*!< SRAM partition5 */
    kResc_SRAM6_32KB         ,   /*!< SRAM partition6 */
    kResc_SRAM7_32KB         ,   /*!< SRAM partition7 */
    kResc_SRAM8_64KB         ,   /*!< SRAM partition8 */
    kResc_SRAM9_64KB         ,   /*!< SRAM partition9 */
    kResc_SRAM10_64KB        ,   /*!< SRAM partition10 */
    kResc_SRAM11_64KB        ,   /*!< SRAM partition11 */
    kResc_SRAM12_128KB       ,   /*!< SRAM partition12 */
    kResc_SRAM13_128KB       ,   /*!< SRAM partition13 */
    kResc_SRAM14_128KB       ,   /*!< SRAM partition14 */
    kResc_SRAM15_128KB       ,   /*!< SRAM partition15 */
    kResc_SRAM16_256KB       ,   /*!< SRAM partition16 */
    kResc_SRAM17_256KB       ,   /*!< SRAM partition17 */
    kResc_SRAM18_256KB       ,   /*!< SRAM partition18 */
    kResc_SRAM19_256KB       ,   /*!< SRAM partition19 */
    kResc_SRAM20_256KB       ,   /*!< SRAM partition20 */
    kResc_SRAM21_256KB       ,   /*!< SRAM partition21 */
    kResc_SRAM22_256KB       ,   /*!< SRAM partition22 */
    kResc_SRAM23_256KB       ,   /*!< SRAM partition23 */
    kResc_SRAM24_256KB       ,   /*!< SRAM partition24 */
    kResc_SRAM25_256KB       ,   /*!< SRAM partition25 */
    kResc_SRAM26_256KB       ,   /*!< SRAM partition26 */
    kResc_SRAM27_256KB       ,   /*!< SRAM partition27 */
    kResc_SRAM28_256KB       ,   /*!< SRAM partition28 */
    kResc_SRAM29_256KB       ,   /*!< SRAM partition29 */

    kResc_MaxNum             ,   /*!< Maximum number of supported constraints */
} resc_name_t;

/* Macros for Resource Constraint Group Types */
#define RESC_GROUP_PRAMS_START          kResc_SRAM_PQ
#define RESC_GROUP_PRAMS_END            kResc_SRAM_DSPTCM
#define RESC_GROUP_PRAMS_SIZE           RESC_GROUP_PRAMS_END - RESC_GROUP_PRAMS_START + 1

#define RESC_GROUP_SRAMS_START          kResc_SRAM0_32KB
#define RESC_GROUP_SRAMS_END            kResc_SRAM29_256KB
#define RESC_GROUP_SRAMS_SIZE           RESC_GROUP_SRAMS_END - RESC_GROUP_SRAMS_START + 1

#define RESC_GROUP_PERIPHERALS_START    kResc_MAIN_CLK
#define RESC_GROUP_PERIPHERALS_END      kResc_ROM
#define RESC_GROUP_PERIPHERALS_SIZE     RESC_GROUP_PERIPHERALS_END - RESC_GROUP_PERIPHERALS_START + 1

/*!
 * @brief Structure for peripheral SRAM resources, or bits in PDSLEEPCFG
 *
 */
typedef struct _enabled_resources_prams
{
    uint32_t apd_mask; /*!< PDSLEEPCFG1 mask for Array PD */
    uint32_t ppd_mask; /*!< PDSLEEPCFG1 mask for Periphery PD */
} enabled_resources_prams_t;

/*!
 * @brief Structure for other peripheral resources, or bit in PDSLEEPCFG
 *
 */
typedef struct _enabled_resources_peripherals
{
    uint8_t  group; /*!< Group for this enabled resource */
    uint32_t mask;  /*!< Mask in group for this enabled resource */
} enabled_resources_peripherals_t;

/* Constraints used by application. */
#define PM_RESC_MAIN_CLK_ON         PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_MAIN_CLK)
#define PM_RESC_VDDCOREREG_HP       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_VDDCOREREG_HP)
#define PM_RESC_PMCREF_HP           PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_PMCREF_HP)
#define PM_RESC_HVD1V8_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_HVD1V8)
#define PM_RESC_PORCORE_HP          PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_PORCORE_HP)
#define PM_RESC_LVDCORE_HP          PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LVDCORE_HP)
#define PM_RESC_HVDCORE_ACTIVE      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_HVDCORE)
#define PM_RESC_SYSXTAL_ON          PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYSXTAL)
#define PM_RESC_LPOSC_ON            PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_LPOSC)
#define PM_RESC_SFRO_ON             PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SFRO)
#define PM_RESC_FFRO_ON             PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_FFRO)
#define PM_RESC_SYSPLLLDO_ON        PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYSPLLLDO)
#define PM_RESC_SYSPLLANA_ON        PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_SYSPLLANA)
#define PM_RESC_AUDIOPLLLDO_ON      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_AUDIOPLLLDO)
#define PM_RESC_AUDIOPLLANA_ON      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_AUDIOPLLANA)
#define PM_RESC_ADC_ACTIVE          PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ADC)
#define PM_RESC_ADC_TEMP_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ADC_TEMP)
#define PM_RESC_ACMP_ACTIVE         PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ACMP)
#define PM_RESC_ROM_ACTIVE          PM_ENCODE_RESC(PM_RESOURCE_FULL_ON, kResc_ROM)

#define PM_RESC_PQ_SRAM_ACTIVE          PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_PQ)
#define PM_RESC_PQ_SRAM_RETENTION       PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_PQ)

#define PM_RESC_FLEXSPI_SRAM_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_FLEXSPI)
#define PM_RESC_FLEXSPI_SRAM_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_FLEXSPI)

#define PM_RESC_USB_SRAM_ACTIVE         PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_USB)
#define PM_RESC_USB_SRAM_RETENTION      PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_USB)

#define PM_RESC_USDHC0_SRAM_ACTIVE      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_USDHC0)
#define PM_RESC_USDHC0_SRAM_RETENTION   PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_USDHC0)

#define PM_RESC_USDHC1_SRAM_ACTIVE      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_USDHC1)
#define PM_RESC_USDHC1_SRAM_RETENTION   PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_USDHC1)

#define PM_RESC_CASPER_SRAM_ACTIVE      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_CASPER)
#define PM_RESC_CASPER_SRAM_RETENTION   PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_CASPER)

#define PM_RESC_DSP_CACHE_ACTIVE        PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_DSPCACHE)
#define PM_RESC_DSP_CACHE_RETENTION     PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_DSPCACHE)

#define PM_RESC_DSP_TCM_ACTIVE          PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM_DSPTCM)
#define PM_RESC_DSP_TCM_RETENTION       PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM_DSPTCM)

#define PM_RESC_SRAM0_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM0_32KB)
#define PM_RESC_SRAM0_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM0_32KB)

#define PM_RESC_SRAM1_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM1_32KB)
#define PM_RESC_SRAM1_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM1_32KB)

#define PM_RESC_SRAM2_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM2_32KB)
#define PM_RESC_SRAM2_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM2_32KB)

#define PM_RESC_SRAM3_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM3_32KB)
#define PM_RESC_SRAM3_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM3_32KB)

#define PM_RESC_SRAM4_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM4_32KB)
#define PM_RESC_SRAM4_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM4_32KB)

#define PM_RESC_SRAM5_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM5_32KB)
#define PM_RESC_SRAM5_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM5_32KB)

#define PM_RESC_SRAM6_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM6_32KB)
#define PM_RESC_SRAM6_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM6_32KB)

#define PM_RESC_SRAM7_32KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM7_32KB)
#define PM_RESC_SRAM7_32KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM7_32KB)

#define PM_RESC_SRAM8_64KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM8_64KB)
#define PM_RESC_SRAM8_64KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM8_64KB)

#define PM_RESC_SRAM9_64KB_ACTIVE       PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM9_64KB)
#define PM_RESC_SRAM9_64KB_RETENTION    PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM9_64KB)

#define PM_RESC_SRAM10_64KB_ACTIVE      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM10_64KB)
#define PM_RESC_SRAM10_64KB_RETENTION   PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM10_64KB)

#define PM_RESC_SRAM11_64KB_ACTIVE      PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM11_64KB)
#define PM_RESC_SRAM11_64KB_RETENTION   PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM11_64KB)

#define PM_RESC_SRAM12_128KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM12_128KB)
#define PM_RESC_SRAM12_128KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM12_128KB)

#define PM_RESC_SRAM13_128KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM13_128KB)
#define PM_RESC_SRAM13_128KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM13_128KB)

#define PM_RESC_SRAM14_128KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM14_128KB)
#define PM_RESC_SRAM14_128KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM14_128KB)

#define PM_RESC_SRAM15_128KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM15_128KB)
#define PM_RESC_SRAM15_128KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM15_128KB)

#define PM_RESC_SRAM16_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM16_256KB)
#define PM_RESC_SRAM16_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM16_256KB)

#define PM_RESC_SRAM17_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM17_256KB)
#define PM_RESC_SRAM17_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM17_256KB)

#define PM_RESC_SRAM18_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM18_256KB)
#define PM_RESC_SRAM18_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM18_256KB)

#define PM_RESC_SRAM19_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM19_256KB)
#define PM_RESC_SRAM19_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM19_256KB)

#define PM_RESC_SRAM20_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM20_256KB)
#define PM_RESC_SRAM20_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM20_256KB)

#define PM_RESC_SRAM21_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM21_256KB)
#define PM_RESC_SRAM21_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM21_256KB)

#define PM_RESC_SRAM22_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM22_256KB)
#define PM_RESC_SRAM22_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM22_256KB)

#define PM_RESC_SRAM23_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM23_256KB)
#define PM_RESC_SRAM23_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM23_256KB)

#define PM_RESC_SRAM24_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM24_256KB)
#define PM_RESC_SRAM24_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM24_256KB)

#define PM_RESC_SRAM25_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM25_256KB)
#define PM_RESC_SRAM25_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM25_256KB)

#define PM_RESC_SRAM26_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM26_256KB)
#define PM_RESC_SRAM26_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM26_256KB)

#define PM_RESC_SRAM27_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM27_256KB)
#define PM_RESC_SRAM27_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM27_256KB)

#define PM_RESC_SRAM28_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM28_256KB)
#define PM_RESC_SRAM28_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM28_256KB)

#define PM_RESC_SRAM29_256KB_ACTIVE     PM_ENCODE_RESC(PM_RESOURCE_FULL_ON,      kResc_SRAM29_256KB)
#define PM_RESC_SRAM29_256KB_RETENTION  PM_ENCODE_RESC(PM_RESOURCE_PARTABLE_ON1, kResc_SRAM29_256KB)

#if FSL_PM_SUPPORT_WAKEUP_SOURCE_MANAGER

#endif

#endif /* _FSL_PM_DEVICE_H_ */
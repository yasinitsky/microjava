/*
 * Microjava - Java for microcontrollers
 * Copyright (C) 2024 Yaroslav Yasynytskyi
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file    clocks.h
 * @brief   API to configure chip clocks. See RP2040 Datasheet, Chapter 2.15
 */

#ifndef MJ_HW_RP2040_CLOCKS_H
#define MJ_HW_RP2040_CLOCKS_H

#include <shared/types.h>

/* Main sources for CLK_REF */
#define CLOCKS_CLK_REF_SRC_ROSC         0x0u
#define CLOCKS_CLK_REF_SRC_AUXSRC       0x1u
#define CLOCKS_CLK_REF_SRC_XOSC         0x2u

/* Main sources for CLK_SYS */
#define CLOCKS_CLK_SYS_SRC_CLK_REF      0x0u
#define CLOCKS_CLK_SYS_SRC_AUXSRC       0x1u

/* Use this macro as source with clocks without main source */
#define CLOCKS_CLK_SRC_NONE             0x0u

/* Auxiliary sources for CLK_GPOUT* */
#define CLOCKS_CLK_GPOUT_AUXSRC_PLL_SYS 0x0u
#define CLOCKS_CLK_GPOUT_AUXSRC_GPIN0   0x1u
#define CLOCKS_CLK_GPOUT_AUXSRC_GPIN1   0x2u
#define CLOCKS_CLK_GPOUT_AUXSRC_PLL_USB 0x3u
#define CLOCKS_CLK_GPOUT_AUXSRC_ROSC    0x4u
#define CLOCKS_CLK_GPOUT_AUXSRC_XOSC    0x5u
#define CLOCKS_CLK_GPOUT_AUXSRC_CLK_SYS 0x6u
#define CLOCKS_CLK_GPOUT_AUXSRC_CLK_USB 0x7u
#define CLOCKS_CLK_GPOUT_AUXSRC_CLK_ADC 0x8u
#define CLOCKS_CLK_GPOUT_AUXSRC_CLK_RTC 0x9u
#define CLOCKS_CLK_GPOUT_AUXSRC_CLK_REF 0xau

/* Auxiliary sources for CLK_REF */
#define CLOCKS_CLK_REF_AUXSRC_PLL_USB   0x0u
#define CLOCKS_CLK_REF_AUXSRC_GPIN0     0x1u
#define CLOCKS_CLK_REF_AUXSRC_GPIN1     0x2u

/* Auxiliary sources for CLK_SYS */
#define CLOCKS_CLK_SYS_AUXSRC_PLL_SYS   0x0u
#define CLOCKS_CLK_SYS_AUXSRC_PLL_USB   0x1u
#define CLOCKS_CLK_SYS_AUXSRC_ROSC      0x2u
#define CLOCKS_CLK_SYS_AUXSRC_XOSC      0x3u
#define CLOCKS_CLK_SYS_AUXSRC_GPIN0     0x4u
#define CLOCKS_CLK_SYS_AUXSRC_GPIN1     0x5u

/* Auxiliary sources for CLK_PERI */
#define CLOCKS_CLK_PERI_AUXSRC_CLK_SYS  0x0u
#define CLOCKS_CLK_PERI_AUXSRC_PLL_SYS  0x1u
#define CLOCKS_CLK_PERI_AUXSRC_PLL_USB  0x2u
#define CLOCKS_CLK_PERI_AUXSRC_ROSC     0x3u
#define CLOCKS_CLK_PERI_AUXSRC_XOSC     0x4u
#define CLOCKS_CLK_PERI_AUXSRC_GPIN0    0x5u
#define CLOCKS_CLK_PERI_AUXSRC_GPIN1    0x6u

/* Auxiliary sources for CLK_USB */
#define CLOCKS_CLK_USB_AUXSRC_PLL_USB   0x0u
#define CLOCKS_CLK_USB_AUXSRC_PLL_SYS   0x1u
#define CLOCKS_CLK_USB_AUXSRC_ROSC      0x2u
#define CLOCKS_CLK_USB_AUXSRC_XOSC      0x3u
#define CLOCKS_CLK_USB_AUXSRC_GPIN0     0x4u
#define CLOCKS_CLK_USB_AUXSRC_GPIN1     0x5u

/* Auxiliary sources for CLK_ADC */
#define CLOCKS_CLK_ADC_AUXSRC_PLL_USB   0x0u
#define CLOCKS_CLK_ADC_AUXSRC_PLL_SYS   0x1u
#define CLOCKS_CLK_ADC_AUXSRC_ROSC      0x2u
#define CLOCKS_CLK_ADC_AUXSRC_XOSC      0x3u
#define CLOCKS_CLK_ADC_AUXSRC_GPIN0     0x4u
#define CLOCKS_CLK_ADC_AUXSRC_GPIN1     0x5u

/* Auxiliary sources for CLK_RTC */
#define CLOCKS_CLK_RTC_AUXSRC_PLL_USB   0x0u
#define CLOCKS_CLK_RTC_AUXSRC_PLL_SYS   0x1u
#define CLOCKS_CLK_RTC_AUXSRC_ROSC      0x2u
#define CLOCKS_CLK_RTC_AUXSRC_XOSC      0x3u
#define CLOCKS_CLK_RTC_AUXSRC_GPIN0     0x4u
#define CLOCKS_CLK_RTC_AUXSRC_GPIN1     0x5u

/* Use this value as auxiliary source when clock is using main source */
#define CLOCKS_CLK_AUXSRC_NONE          0x0u

typedef enum {
    CLOCKS_CLK_GPOUT0,
    CLOCKS_CLK_GPOUT1,
    CLOCKS_CLK_GPOUT2,
    CLOCKS_CLK_GPOUT3,
    CLOCKS_CLK_REF,
    CLOCKS_CLK_SYS,
    CLOCKS_CLK_PERI,
    CLOCKS_CLK_USB,
    CLOCKS_CLK_ADC,
    CLOCKS_CLK_RTC,
    CLOCKS_CLK_COUNT
} clocks_clk_t;

/**
 * @brief Initialize clocks with default properties
 */
void clocks_init();

/**
 * @brief                   Configure clock with given properties
 * 
 * @param clock             Clock to configure
 * @param source            Main clock source. Works only for CLK_REF and CLK_SYS. For other clocks value is ignored (use CLOCKS_CLK_SRC_NONE for readability)
 *                          Valid values are CLOCKS_CLK_*_SRC_* macros. Use only values that correspond to the specified clock
 * @param aux_source        Auxiliary clock source. Valid values are CLOCKS_CLK_*_AUXSRC_* macros. Use CLOCKS_CLK_AUX_NONE if main source is specified.
 *                          Use only values that correspond to the specified clock.
 *                          If clock is CLOCKS_CLK_REF or CLOCKS_CLK_SYS, use CLOCKS_CLK_REF_SRC_AUX or CLOCKS_CLK_SYS_SRC_AUX as main
 *                          source respectively to use auxiliary source specified here
 * @param source_frequency  Frequency of the clock source
 * @param frequency         Target clock frequency. Should be >= source_frequency
 */
void clocks_clk_configure(clocks_clk_t clock, mj_u32 source, mj_u32 aux_source, mj_u32 source_frequency, mj_u32 frequency);

/**
 * @brief Get clock frequency
 */
mj_u32 clocks_clk_get_frequency(clocks_clk_t clock);

#endif // MJ_HW_RP2040_CLOCKS_H
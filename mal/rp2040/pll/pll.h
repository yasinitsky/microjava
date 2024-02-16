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
 * @file    pll.h
 * @brief   API to configure PLL. See RP2040 Datasheet, Chapter 2.18
 */

#ifndef MJ_HW_RP2040_PLL_H
#define MJ_HW_RP2040_PLL_H

#include <shared/types.h>

typedef enum {
    PLL_SYS,
    PLL_USB,
    PLL_COUNT
} pll_t;

/**
 * @brief Initializa PLLs with default properties
 */
void pll_init();

/**
 * @brief               Initialize PLL with given properties.
 *                      Final frequency is calculated as (vco_frequency) / (postdiv1 * postdiv2).
 *                      See arguments description for values constraints
 * 
 * @param pll           PLL to configure
 * @param vco_frequency VCO frequency in range [750, 1600] MHz
 * @param postdiv1      First VCO frequency post-divider in range [1, 7]
 * @param postdiv2      Second VCO frequency post-divider in range [1, 7]
 */
void pll_configure(pll_t pll, mj_u32 vco_frequency, mj_u32 postdiv1, mj_u32 postdiv2);

/**
 * @brief Get PLL frequency
 */
mj_u32 pll_get_frequency(pll_t pll);

#endif // MJ_HW_RP2040_PLL_H
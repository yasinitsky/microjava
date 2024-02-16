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
 * @file    bootrom.h
 * @brief   API to interact with bootrom. See RP2040 Datasheet, Chapter 2.8
 */

#ifndef MJ_HW_RP2040_BOOTROM_H
#define MJ_HW_RP2040_BOOTROM_H

#include <shared/types.h>

/**
 * @brief   Get bootrom version
 * 
 * @return  Bootrom version
 */
mj_u8 bootrom_get_version();

/**
 * @brief   Get pointer to function from the bootrom lookup table
 * 
 * @param   code Code in the lookup table. See @ref bootrom_table_code()
 * @return  Pointer to function
 */
void *bootrom_func_lookup(mj_u32 code);

/**
 * @brief   Get pointer to data from the bootrom lookup table
 * 
 * @param   code Code in the lookup table. See @ref bootrom_table_code()
 * @return  Pointer to data
 */
void *bootrom_data_lookup(mj_u32 code);

/**
 * @brief   Get 32-bit code to use in lookup functions
 * 
 * @param   c1 First character
 * @param   c2 Second character
 * @return  Code
 */
mj_u32 bootrom_table_code(const char c1, const char c2);

/**
 * @brief   Bootrom functions. Members names correspond to functions names in datasheet.
 *          See @ref bootrom_funcs
 */
typedef struct {
    mj_u32 *(*memset4)(mj_u32 *ptr, mj_u8 c, mj_u32 n);
    mj_u32 *(*memcpy44)(mj_u32 *dest, mj_u32 *src, mj_u32 n);
} bootrom_funcs_t;

/**
 * @brief   Pointers to known bootrom functions. Save known pointers (obtained by @ref bootrom_func_lookup())
 *          here to use them later
 */
extern bootrom_funcs_t bootrom_funcs;

#endif // MJ_HW_RP2040_BOOTROM_H
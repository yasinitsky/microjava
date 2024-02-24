/*
 * Microjava - Java for microcontrollers
 * Copyright (C) 2024 Yaroslav Yasynytskyi
 * 
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
 * @file    interface.h
 * @brief   This file contains definition of MCU Abstraction Layer (MAL) interface
 */

#ifndef MJ_MAL_INTERFACE_H
#define MJ_MAL_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <shared/types.h>

/**
 * @brief MAL return codes. All MAL functions should use it as return value
 */
typedef enum {
    MJ_MAL_OK      = 0
} mj_mal_status_t;

extern const mj_u32 mj_mal_flash_block_size;
extern const mj_u32 mj_mal_flash_block_count;
extern const mj_u32 mj_mal_flash_read_size;
extern const mj_u32 mj_mal_flash_prog_size;

/**
 * @brief   Read `size` bytes from FLASH `block` to `buffer` \n
 *          `block` must be less than @ref mj_mal_flash_block_count \n
 *          `offset` must be a multiple of @ref mj_mal_flash_read_size \n
 *          `size` must be a multiple of @ref mj_mal_flash_read_size
 * 
 * @return  @ref MJ_MAL_OK on success 
 */
mj_mal_status_t mj_mal_flash_read(mj_u32 block, mj_u32 offset, void *buffer, mj_u32 size);

/**
 * @brief   Write `size` bytes from `buffer` to FLASH `block` at `offset` \n
 *          `block` must be less than @ref mj_mal_flash_block_count \n
 *          `offset` must be a multiple of @ref mj_mal_flash_prog_size \n
 *          `size` must be a multiple of @ref mj_mal_flash_prog_size
 * 
 * @return  @ref MJ_MAL_OK on success 
 */
mj_mal_status_t mj_mal_flash_prog(mj_u32 block, mj_u32 offset, const void *buffer, mj_u32 size);

/**
 * @brief   Erase `block` from FLASH \n
 *          `block` must be less than @ref mj_mal_flash_block_count \n
 * 
 * @return  @ref MJ_MAL_OK on success 
 */
mj_mal_status_t mj_mal_flash_erase(mj_u32 block);

/**
 * @brief   Sync state of FLASH device
 * 
 * @return  @ref MJ_MAL_OK on success 
 */
mj_mal_status_t mj_mal_flash_sync();

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // MJ_MAL_INTERFACE_H
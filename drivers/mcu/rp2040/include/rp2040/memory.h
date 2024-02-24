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
 * @file memory.h
 * @brief Helpers to work with memory
 */

#ifndef MJ_HW_RP2040_MEMORY_H
#define MJ_HW_RP2040_MEMORY_H

#include <shared/types.h>

/**
 * Macros only for internal use. See RP2040 Datasheet, Chapter 2.1.2.
*/
#define _MEMORY_ATOMIC_XOR_OFFSET   0x1000u
#define _MEMORY_ATOMIC_SET_OFFSET   0x2000u
#define _MEMORY_ATOMIC_CLEAR_OFFSET 0x3000u

/**
 * Macros to make 32-bits memory read/writes more readable
 */
#define memory_write(addr, value) *(mj_u32 *)(addr) = (mj_u32)(value)
#define memory_read(addr) *(mj_u32 *)(addr)

/**
 * Atomic operations for 32-bits values.
 */
#define memory_atomic_xor(addr, value) *(mj_u32 *)((mj_u8 *)(addr) + _MEMORY_ATOMIC_XOR_OFFSET) = (mj_u32)(value)
#define memory_atomic_set(addr, mask) *(mj_u32 *)((mj_u8 *)(addr) + _MEMORY_ATOMIC_SET_OFFSET) = (mj_u32)(mask)
#define memory_atomic_clear(addr, mask) *(mj_u32 *)((mj_u8 *)(addr) + _MEMORY_ATOMIC_CLEAR_OFFSET) = (mj_u32)(mask)

/**
 * @brief   Performs memory utils and runtime init (including bss, data and text sections).
 *          Should be called once as soon as possible.
 */
void memory_init(void);

/**
 * @brief Fast memset for 4-bytes aligned ptr
 */
mj_u32 *memory_set4(mj_u32 *ptr, mj_u8 c, mj_u32 n);

/**
 * @brief Fast memcpy for 4-bytes aligned source and destination
 */
mj_u32 *memory_copy4(mj_u32 *dest, mj_u32 *src, mj_u32 n);

/**
 * @brief Write bits of value specified by mask to addr
 */
inline static void memory_write_masked(mj_u32 *addr, mj_u32 value, mj_u32 mask) {
    memory_atomic_xor(addr, (*addr ^ value) & mask);
}

/**
 * @brief Same as @ref memory_write_masked(), but with address as 32-bits unsigned
 */
inline static void memory_write_masked_uint(mj_u32 addr, mj_u32 value, mj_u32 mask) {
    memory_write_masked((mj_u32 *)addr, value, mask);
}

#endif // MJ_HW_RP2040_MEMORY_H
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

#include <stdint.h>

/**
 * Macros only for internal use. See RP2040 Datasheet, Chapter 2.1.2.
*/
#define _MEMORY_ATOMIC_XOR_OFFSET   0x1000u
#define _MEMORY_ATOMIC_SET_OFFSET   0x2000u
#define _MEMORY_ATOMIC_CLEAR_OFFSET 0x3000u

/**
 * Macros to make 32-bits memory read/writes more readable
 */
#define memory_write(addr, value) *(uint32_t *)(addr) = (uint32_t)(value)
#define memory_read(addr) *(uint32_t *)(addr)

/**
 * Atomic operations for 32-bits values.
 */
#define memory_atomic_xor(addr, value) *(uint32_t *)((uint8_t *)(addr) + _MEMORY_ATOMIC_XOR_OFFSET) = (uint32_t)(value)
#define memory_atomic_set(addr, mask) *(uint32_t *)((uint8_t *)(addr) + _MEMORY_ATOMIC_SET_OFFSET) = (uint32_t)(mask)
#define memory_atomic_clear(addr, mask) *(uint32_t *)((uint8_t *)(addr) + _MEMORY_ATOMIC_CLEAR_OFFSET) = (uint32_t)(mask)

/**
 * @brief   Performs memory utils and runtime init (including bss, data and text sections).
 *          Should be called once as soon as possible.
 */
void memory_init(void);

/**
 * @brief Fast memset for 4-bytes aligned ptr
 */
uint32_t *memory_set4(uint32_t *ptr, uint8_t c, uint32_t n);

/**
 * @brief Fast memcpy for 4-bytes aligned source and destination
 */
uint32_t *memory_copy4(uint32_t *dest, uint32_t *src, uint32_t n);

/**
 * @brief Write bits of value specified by mask to addr
 */
inline static void memory_write_masked(uint32_t *addr, uint32_t value, uint32_t mask) {
    memory_atomic_xor(addr, (*addr ^ value) & mask);
}

/**
 * @brief Same as @ref memory_write_masked(), but with address as 32-bits unsigned
 */
inline static void memory_write_masked_uint(uint32_t addr, uint32_t value, uint32_t mask) {
    memory_write_masked((uint32_t *)addr, value, mask);
}

#endif // MJ_HW_RP2040_MEMORY_H
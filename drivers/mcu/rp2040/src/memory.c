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

#include <rp2040/memory.h>

#include <rp2040/bootrom.h>

/**
 * @brief Representation of __memory_info symbol in .memory_info section. See @ref crt0.S for definition
 */
typedef struct {
    void        *flash_end;
    void        *ram_text_begin;
    mj_u32    ram_text_size;
    void        *ram_data_begin;
    mj_u32    ram_data_size;
    void        *ram_bss_begin;
    mj_u32    ram_bss_size;
} memory_info_t;

void memory_init(void) {
    // __memory_info in .memory_info section holds data about ram memory layout
    extern volatile memory_info_t __memory_info;

    // don't save this functions to bootrom_funcs structure now, because it will be filled with zeros during bss initialization
    mj_u32 *(*memset4)(mj_u32 *, mj_u8, mj_u32) = bootrom_func_lookup(bootrom_table_code('M', 'S'));
    mj_u32 *(*memcpy44)(mj_u32 *, mj_u32 *, mj_u32) = bootrom_func_lookup(bootrom_table_code('C', '4'));

    // fill .ram.bss with zeros
    memset4(__memory_info.ram_bss_begin, 0, __memory_info.ram_bss_size);

    // .ram.data and .ram.text should be placed right after .memory_info by elf2uf2.py or another tool and be 4-bytes aligned 
    // code below copies them to the actual ram
    memcpy44(__memory_info.ram_data_begin, __memory_info.flash_end, __memory_info.ram_data_size);
    memcpy44(__memory_info.ram_text_begin, __memory_info.flash_end + __memory_info.ram_data_size, __memory_info.ram_text_size);

    // now we can safely fill this structure
    bootrom_funcs.memset4 = memset4;
    bootrom_funcs.memcpy44 = memcpy44;
}

mj_u32 *memory_set4(mj_u32 *ptr, mj_u8 c, mj_u32 n) {
    return bootrom_funcs.memset4(ptr, c, n);
}

mj_u32 *memory_copy4(mj_u32 *dest, mj_u32 *src, mj_u32 n) {
    return bootrom_funcs.memcpy44(dest, src, n);
}
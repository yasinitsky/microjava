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

#include "memory.h"

#include "bootrom/bootrom.h"

/**
 * @brief Representation of __memory_info symbol in .memory_info section. See @ref crt0.S for definition
 */
typedef struct {
    void        *flash_end;
    void        *ram_text_begin;
    uint32_t    ram_text_size;
    void        *ram_data_begin;
    uint32_t    ram_data_size;
    void        *ram_bss_begin;
    uint32_t    ram_bss_size;
} memory_info_t;

void memory_init(void) {
    // __memory_info in .memory_info section holds data about ram memory layout
    extern volatile memory_info_t __memory_info;

    // don't save this functions to bootrom_funcs structure now, because it will be filled with zeros during bss initialization
    uint32_t *(*memset4)(uint32_t *, uint8_t, uint32_t) = bootrom_func_lookup(bootrom_table_code('M', 'S'));
    uint32_t *(*memcpy44)(uint32_t *, uint32_t *, uint32_t) = bootrom_func_lookup(bootrom_table_code('C', '4'));

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

uint32_t *memory_set4(uint32_t *ptr, uint8_t c, uint32_t n) {
    return bootrom_funcs.memset4(ptr, c, n);
}

uint32_t *memory_copy4(uint32_t *dest, uint32_t *src, uint32_t n) {
    return bootrom_funcs.memcpy44(dest, src, n);
}
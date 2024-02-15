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

#include "bootrom.h"

/* Definitions from datasheet */
#define BOOTROM_BASE            0x00000000u
#define BOOTROM_MAGIC           (BOOTROM_BASE + 0x10u)
#define BOOTROM_VERSION         (BOOTROM_BASE + 0x13u)
#define BOOTROM_FUNC_TABLE      (BOOTROM_BASE + 0x14u)
#define BOOTROM_DATA_TABLE      (BOOTROM_BASE + 0x16u)
#define BOOTROM_TABLE_LOOKUP    (BOOTROM_BASE + 0x18u)

bootrom_funcs_t bootrom_funcs;

typedef void *(*table_lookup_fn_t)(uint16_t *table, uint32_t code);

/**
 * @brief   Get 16-bit value at 16-bit address and convert it to pointer
 */
static void *bootrom_ptr_at(uint16_t addr) {
    return (void *)(uintptr_t)(*(uint16_t *)(uintptr_t)addr);
}

uint8_t bootrom_get_version() {
    return *(uint8_t *)(uintptr_t) BOOTROM_VERSION;
}

void *bootrom_func_lookup(uint32_t code) {
    table_lookup_fn_t table_lookup = (table_lookup_fn_t) bootrom_ptr_at(BOOTROM_TABLE_LOOKUP);
    return table_lookup((uint16_t *) bootrom_ptr_at(BOOTROM_FUNC_TABLE), code);
}

void *bootrom_data_lookup(uint32_t code) {
    table_lookup_fn_t table_lookup = (table_lookup_fn_t) bootrom_ptr_at(BOOTROM_TABLE_LOOKUP);
    return table_lookup((uint16_t *) bootrom_ptr_at(BOOTROM_DATA_TABLE), code);
}

uint32_t bootrom_table_code(const char c1, const char c2) {
    return (c2 << 8) | c1;
}
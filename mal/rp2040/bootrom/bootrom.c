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

typedef void *(*table_lookup_fn_t)(mj_u16 *table, mj_u32 code);

/**
 * @brief   Get 16-bit value at 16-bit address and convert it to pointer
 */
static void *bootrom_ptr_at(mj_u16 addr) {
    return (void *)(mj_uptr)(*(mj_u16 *)(mj_uptr)addr);
}

mj_u8 bootrom_get_version() {
    return *(mj_u8 *)(mj_uptr) BOOTROM_VERSION;
}

void *bootrom_func_lookup(mj_u32 code) {
    table_lookup_fn_t table_lookup = (table_lookup_fn_t) bootrom_ptr_at(BOOTROM_TABLE_LOOKUP);
    return table_lookup((mj_u16 *) bootrom_ptr_at(BOOTROM_FUNC_TABLE), code);
}

void *bootrom_data_lookup(mj_u32 code) {
    table_lookup_fn_t table_lookup = (table_lookup_fn_t) bootrom_ptr_at(BOOTROM_TABLE_LOOKUP);
    return table_lookup((mj_u16 *) bootrom_ptr_at(BOOTROM_DATA_TABLE), code);
}

mj_u32 bootrom_table_code(const char c1, const char c2) {
    return (c2 << 8) | c1;
}
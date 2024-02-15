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

#include "resets.h"

#include "memory/memory.h"

#define RESETS_BASE         0x4000c000u
#define RESETS_RESET        (RESETS_BASE + 0x0u)
#define RESETS_RESET_DONE   (RESETS_BASE + 0x8u)

void resets_reset(uint32_t blocks) {
    memory_atomic_set(RESETS_RESET, blocks);
}

void resets_unreset(uint32_t blocks) {
    memory_atomic_clear(RESETS_RESET, blocks);

    while(~memory_read(RESETS_RESET_DONE) & blocks) { }
}
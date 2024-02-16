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

#ifndef MJ_SHARED_TYPES_H
#define MJ_SHARED_TYPES_H

/**
 * @file    types.h
 * @brief   Machine-independent fundamental types
 */

#include <stdint.h>
#include <stdbool.h>

/* Types from stdint.h are used, because it's the solution with the best portability */

typedef uint8_t     mj_u8;
typedef uint16_t    mj_u16;
typedef uint32_t    mj_u32;
typedef uint64_t    mj_u64;

typedef int8_t      mj_s8;
typedef int16_t     mj_s16;
typedef int32_t     mj_s32;
typedef int64_t     mj_s64;

typedef bool        mj_bool;

typedef uintptr_t   mj_uptr;

#endif // MJ_SHARED_TYPES_H
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
 * @file    mcu.h
 * @brief   This file contains definitions of MCU Abstraction Layer (MAL) functions
 */

#ifndef MJ_MAL_INTERFACE_H
#define MJ_MAL_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief MAL Interface return codes
 */
typedef enum {
    MCU_OK      = 0
} mcu_status_t;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // MJ_MAL_INTERFACE_H
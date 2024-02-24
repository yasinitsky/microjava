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
 * @file    floating_point.h
 * @brief   Floating point runtime routines
 */ 

#ifndef MJ_HW_RP2040_FLOATING_POINT_H
#define MJ_HW_RP2040_FLOATING_POINT_H

/**
 * @brief   Initialize floating point runtime.
 *          Must be called once before the first floating point operation occurs
 */
void floating_point_init();

#endif // MJ_HW_RP2040_FLOATING_POINT_H
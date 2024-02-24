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
 * @file    xosc.h
 * @brief   API to interact with XOSC. See RP2040 Datasheet, Chapter 2.16
 */

#ifndef MJ_HW_RP2040_XOSC_H
#define MJ_HW_RP2040_XOSC_H

/** 
 * On-board XOSC frequency
 * NOTE: This value can be different on custom boards. In that case the clocks with XOSC as source will produce wrong frequencies :(
*/
#define XOSC_FREQ 12000000u

/**
 * @brief Initialize and run XOSC
 */
void xosc_init(void);

#endif // MJ_HW_RP2040_XOSC_H
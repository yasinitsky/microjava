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

#include <rp2040/xosc.h>

#include <rp2040/memory.h>

#define XOSC_BASE       0x40024000u
#define XOSC_CTRL       (XOSC_BASE)
#define XOSC_STATUS     (XOSC_BASE + 0x04u)
#define XOSC_DORMANT    (XOSC_BASE + 0x08u)
#define XOSC_STARTUP    (XOSC_BASE + 0x0cu)
#define XOSC_COUNT      (XOSC_BASE + 0x1cu)

#define XOSC_CTRL_ENABLE_LSB                12u
#define XOSC_CTRL_ENABLE_BITS               0xfff000u
#define XOSC_CTRL_ENABLE_VALUE_DISABLE      (0xd1eu << XOSC_CTRL_ENABLE_LSB)
#define XOSC_CTRL_ENABLE_VALUE_ENABLE       (0xfabu << XOSC_CTRL_ENABLE_LSB)

#define XOSC_CTRL_FREQ_RANGE_LSB            0u
#define XOSC_CTRL_FREQ_RANGE_BITS           0xfffu
#define XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ  (0xaa0u << XOSC_CTRL_FREQ_RANGE_LSB)

#define XOSC_STATUS_STABLE_LSB              31u
#define XOSC_STATUS_STABLE_BITS             0x80000000u
#define XOSC_STATUS_STABLE_VALUE_TRUE       (1u << XOSC_STATUS_STABLE_LSB)
#define XOSC_STATUS_STABLE_VALUE_FALSE      (0u << XOSC_STATUS_STABLE_LSB)

#define XOSC_STARTUP_DELAY_LSB              0u
#define XOSC_STARTUP_DELAY_BITS             0x3fffu
/* Calculated as described in the datasheet */
#define XOSC_STARTUP_DELAY_VALUE            (((XOSC_FREQ / 1000) / 256) << XOSC_STARTUP_DELAY_LSB)

void xosc_init(void) {
    memory_write_masked_uint(XOSC_STARTUP, XOSC_STARTUP_DELAY_VALUE, XOSC_STARTUP_DELAY_BITS);
    memory_write_masked_uint(XOSC_CTRL, XOSC_CTRL_FREQ_RANGE_VALUE_1_15MHZ, XOSC_CTRL_FREQ_RANGE_BITS);
    memory_write_masked_uint(XOSC_CTRL, XOSC_CTRL_ENABLE_VALUE_ENABLE, XOSC_CTRL_ENABLE_BITS);
    
    while(!(memory_read(XOSC_STATUS) & XOSC_STATUS_STABLE_VALUE_TRUE)) { }
}
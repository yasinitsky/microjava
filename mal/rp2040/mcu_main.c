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

#include <shared/types.h>
#include <assert.h>

#include "memory/memory.h"
#include "bootrom/bootrom.h"
#include "floating_point/floating_point.h"
#include "clocks/clocks.h"
#include "resets/resets.h"

void main(void);

/**
 * @brief   The first C function executed on RP2040 target. It performs target-specific runtime initialization and calls Microjava cores entry point
 * 
 * @return  This function doesn't return, but halt on bkpt 0. If this happens, something went terribly wrong
 */
int mcu_main() {
    memory_init();
    floating_point_init();

    resets_reset(~(RESETS_RESET_IO_QSPI | 
        RESETS_RESET_PADS_QSPI | 
        RESETS_RESET_PLL_USB | 
        RESETS_RESET_USBCTRL |
        RESETS_RESET_SYSCFG |
        RESETS_RESET_PLL_SYS));

    resets_unreset(RESETS_RESET_ALL & ~(RESETS_RESET_ADC | 
        RESETS_RESET_RTC | 
        RESETS_RESET_SPI0 | 
        RESETS_RESET_SPI1 | 
        RESETS_RESET_UART0 |
        RESETS_RESET_UART1 |
        RESETS_RESET_USBCTRL));

    clocks_init();

    resets_unreset(RESETS_RESET_ALL);
}
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
 * @file    resets.h
 * @brief   API to perform subsystem resets. See RP2040 Datasheet, Chapter 2.14
 */

#ifndef MJ_HW_RP2040_RESETS_H
#define MJ_HW_RP2040_RESETS_H

#include <shared/types.h>

#define RESETS_RESET_ALL        0x01ffffffu
#define RESETS_RESET_USBCTRL    0x01000000u
#define RESETS_RESET_UART1      0x00800000u
#define RESETS_RESET_UART0      0x00400000u
#define RESETS_RESET_TIMER      0x00200000u
#define RESETS_RESET_TBMAN      0x00100000u
#define RESETS_RESET_SYSINFO    0x00080000u
#define RESETS_RESET_SYSCFG     0x00040000u
#define RESETS_RESET_SPI1       0x00020000u
#define RESETS_RESET_SPI0       0x00010000u
#define RESETS_RESET_RTC        0x00008000u
#define RESETS_RESET_PWM        0x00004000u
#define RESETS_RESET_PLL_USB    0x00002000u
#define RESETS_RESET_PLL_SYS    0x00001000u
#define RESETS_RESET_PIO1       0x00000800u
#define RESETS_RESET_PIO0       0x00000400u
#define RESETS_RESET_PADS_QSPI  0x00000200u
#define RESETS_RESET_PADS_BANK0 0x00000100u
#define RESETS_RESET_JTAG       0x00000080u
#define RESETS_RESET_IO_QSPI    0x00000040u
#define RESETS_RESET_IO_BANK0   0x00000020u
#define RESETS_RESET_I2C1       0x00000010u
#define RESETS_RESET_I2C0       0x00000008u
#define RESETS_RESET_DMA        0x00000004u
#define RESETS_RESET_BUSCTRL    0x00000002u
#define RESETS_RESET_ADC        0x00000001u

/**
 * @brief Reset blocks
 * 
 * @param blocks Bit OR of RESETS_RESET_* macros that indicates blocks to reset
 */
void resets_reset(mj_u32 blocks);

/**
 * @brief Unreset blocks and wait for the operation to finish
 * 
 * @param blocks Bit OR of RESETS_RESET_* macros that indicates blocks to unreset
 */
void resets_unreset(mj_u32 blocks);

#endif // MJ_HW_RP2040_RESETS_H
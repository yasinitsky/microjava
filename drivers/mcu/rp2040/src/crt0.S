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
    This file describes memory content right after second stage bootloader.
    It contains initialization necessary to start executing C code.
*/

.cpu cortex-m0plus
.thumb
.syntax unified

.section .vectors, "ax"

# this vector table used only for runtime initialization
.global __vector_table
__vector_table:
.word __stack_top
.word __reset_handler
.word __nmi_handler
.word __hardfault_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler
.word __dummy_handler

# just return without any exception handling
.global __dummy_handler
.thumb_func
__dummy_handler:
    ldr r0, =0xfffffff1 /* return to handler mode (see ARMv6-M Architecture Reference Manual B1.5) */
    bx r0

# while we are using vector table above, we don't have runtime to process critical exception
# so just halt core in bkpt 0
.global __hardfault_handler
.thumb_func
__hardfault_handler:
.global __nmi_handler
.thumb_func
__nmi_handler:
    bkpt #0

.global __reset_handler
.thumb_func
__reset_handler:
    ldr r0, =mcu_main
    blx r0
    b .

# section .memory_info holds memory layout to properly copy and fill .data and .bss sections respectively
.section .memory_info, "a"
.global __memory_info
__memory_info:
.word __flash_end
.word __ram_text_begin
.word __ram_text_size
.word __ram_data_begin
.word __ram_data_size
.word __ram_bss_begin
.word __ram_bss_size
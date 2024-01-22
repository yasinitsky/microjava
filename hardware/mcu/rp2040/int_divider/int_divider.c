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

#include "int_divider.h"

#include "memory/memory.h"

#include <stdint.h>

/* NOTE: There is no symbol DIV_BASE in the datasheet. This name used to clearly separate SIO functions without using SIO_BASE. */
#define DIV_BASE        0xd0000060u
#define DIV_UDIVIDEND   (DIV_BASE + 0x00u)
#define DIV_UDIVISOR    (DIV_BASE + 0x04u)
#define DIV_SDIVIDEND   (DIV_BASE + 0x08u)
#define DIV_SDIVISOR    (DIV_BASE + 0x0cu)
#define DIV_QUOTIENT    (DIV_BASE + 0x10u)
#define DIV_REMINDER    (DIV_BASE + 0x14u)
#define DIV_CSR         (DIV_BASE + 0x18u)

#define DIV_CSR_READY_LSB   1u
#define DIV_CSR_READY_BITS  0x2u

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;

typedef struct {
    unsigned long long quot;
    unsigned long long rem;
} ulldiv_t;

int __aeabi_idiv0(int return_value) {
    asm("bkpt #0");
    return return_value;
}

int __aeabi_idiv(int numerator, int denominator) {
    if(denominator == 0) return __aeabi_idiv0(numerator);

    memory_write(DIV_SDIVIDEND, numerator);
    memory_write(DIV_SDIVISOR, denominator);
    
    while(!(memory_read(DIV_CSR) & DIV_CSR_READY_BITS)) { }

    return memory_read(DIV_QUOTIENT);
}

unsigned __aeabi_uidiv(unsigned numerator, unsigned denominator) {
    memory_write(DIV_UDIVIDEND, numerator);
    memory_write(DIV_UDIVISOR, denominator);
    
    while(!(memory_read(DIV_CSR) & DIV_CSR_READY_BITS)) { }
    
    return memory_read(DIV_QUOTIENT);
}

/**
 * 64-bits division using basic long division algorithm.
 * TODO: Current implementation does not use advantages of 32-bits hardware divider. Optimize it!
 */
void __aeabi_uldivmod(unsigned long long n, unsigned long long d) {
    ulldiv_t result;

    result.quot = 0;
    result.rem = 0;

    for(int i = 63; i >= 0; i--) {
        result.rem <<= 1;
        result.rem |= (n >> i) & 1u;

        if(result.rem >= d) {
            result.rem -= d;
            result.quot |= (1 << i);
        }
    }

    uint32_t quot_upper = result.quot >> 32;
    uint32_t quot_lower = result.quot;
    uint32_t rem_upper = result.rem >> 32;
    uint32_t rem_lower = result.rem;

    /* Store result in registers as described in ARM32 Runtime ABI. It works only with little-endian byte order */
    __asm__ volatile (
        "\
        ldr r0, %0\n\
        ldr r1, %1\n\
        ldr r2, %2\n\
        ldr r3, %3\n\
        "
        :
        : "" (quot_lower), "" (quot_upper), "" (rem_lower), "" (rem_upper));
}
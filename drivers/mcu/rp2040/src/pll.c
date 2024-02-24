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

#include <rp2040/pll.h>

#include <assert.h>

#include <rp2040/xosc.h>
#include <rp2040/resets.h>
#include <rp2040/memory.h>

#define PLL_SYS_BASE    0x40028000u
#define PLL_USB_BASE    0x4002c000u

#define PLL_CS_LOCK_LSB             31u
#define PLL_CS_LOCK_BITS            0x80000000u
#define PLL_CS_LOCK_VALUE_LOCKED    (1u << PLL_CS_LOCK_LSB)
#define PLL_CS_LOCK_VALUE_UNLOCKED  (0u << PLL_CS_LOCK_LSB)

#define PLL_CS_REFDIV_LSB           0u
#define PLL_CS_REFDIV_BITS          0x0000001fu

#define PLL_PWR_VCOPD_LSB           5u
#define PLL_PWR_VCOPD_BITS          0x00000020u
#define PLL_PWR_VCOPD_VALUE_ON      (1u << PLL_PWR_VCOPD_LSB)
#define PLL_PWR_VCOPD_VALUE_OFF     (0u << PLL_PWR_VCOPD_LSB)

#define PLL_PWR_POSTDIVPD_LSB       3u
#define PLL_PWR_POSTDIVPD_BITS      0x00000008u
#define PLL_PWR_POSTDIVPD_VALUE_ON  (1u << PLL_PWR_POSTDIVPD_LSB)
#define PLL_PWR_POSTDIVPD_VALUE_OFF (0u << PLL_PWR_POSTDIVPD_LSB)

#define PLL_PWR_PD_LSB              0u
#define PLL_PWR_PD_BITS             0x00000001u
#define PLL_PWR_PD_VALUE_ON         (1u << PLL_PWR_PD_LSB)
#define PLL_PWR_PD_VALUE_OFF        (0u << PLL_PWR_PD_LSB)

#define PLL_FBDIV_INT_LSB           0u
#define PLL_FBDIV_INT_BITS          0x00000fffu

#define PLL_PRIM_POSTDIV1_LSB       16u
#define PLL_PRIM_POSTDIV1_BITS      0x00070000u

#define PLL_PRIM_POSTDIV2_LSB       12u
#define PLL_PRIM_POSTDIV2_BITS      0x00007000u

#define PLL_VCO_MIN_FREQ    750000000u
#define PLL_VCO_MAX_FREQ    1600000000u

#define PLL_SYS_VCO_FREQ    1500000000u
#define PLL_SYS_POSTDIV1    6u
#define PLL_SYS_POSTDIV2    2u

#define PLL_USB_VCO_FREQ    1200000000u
#define PLL_USB_POSTDIV1    5u
#define PLL_USB_POSTDIV2    5u

typedef struct {
    mj_u32 cs;
    mj_u32 pwr;
    mj_u32 fbdiv_int;
    mj_u32 prim;
} pll_hw_t;

static mj_u32 pll_frequencies[PLL_COUNT] = { 0 };

static pll_hw_t *select_pll(pll_t pll) {
    return (pll_hw_t *)((pll == PLL_SYS) ? PLL_SYS_BASE : PLL_USB_BASE);
}

void pll_init() {
    pll_configure(PLL_SYS, PLL_SYS_VCO_FREQ, PLL_SYS_POSTDIV1, PLL_SYS_POSTDIV2);
    pll_configure(PLL_USB, PLL_USB_VCO_FREQ, PLL_USB_POSTDIV1, PLL_USB_POSTDIV2);
}

void pll_configure(pll_t pll, mj_u32 vco_frequency, mj_u32 postdiv1, mj_u32 postdiv2) {
    assert(vco_frequency >= PLL_VCO_MIN_FREQ && vco_frequency <= PLL_VCO_MAX_FREQ);
    assert((postdiv1 >= 1 && postdiv1 <= 7) && (postdiv2 >= 1 && postdiv2 <= 7));
    assert((vco_frequency / 16) >= XOSC_FREQ);

    pll_hw_t *pll_hw = select_pll(pll);

    mj_u32 fbdiv = vco_frequency / XOSC_FREQ;
    assert(fbdiv >= 16 && fbdiv <= 320);

    mj_u32 postdiv = (postdiv1 << PLL_PRIM_POSTDIV1_LSB) | (postdiv2 << PLL_PRIM_POSTDIV2_LSB);

    mj_u32 reset = (pll == PLL_SYS) ? RESETS_RESET_PLL_SYS : RESETS_RESET_PLL_USB;
    resets_reset(reset);
    resets_unreset(reset);

    memory_write_masked(&pll_hw->cs, 1 << PLL_CS_REFDIV_LSB, PLL_CS_REFDIV_BITS);
    memory_write_masked(&pll_hw->fbdiv_int, fbdiv << PLL_FBDIV_INT_LSB, PLL_FBDIV_INT_BITS);

    memory_write_masked(
            &pll_hw->pwr, 
            PLL_PWR_PD_VALUE_OFF | PLL_PWR_VCOPD_VALUE_OFF,
            PLL_PWR_PD_BITS | PLL_PWR_VCOPD_BITS
    );

    while(!(pll_hw->cs & PLL_CS_LOCK_VALUE_LOCKED)) { }
 
    memory_write_masked(&pll_hw->prim, postdiv, PLL_PRIM_POSTDIV1_BITS | PLL_PRIM_POSTDIV2_BITS);
    memory_write_masked(&pll_hw->pwr, PLL_PWR_POSTDIVPD_VALUE_OFF, PLL_PWR_POSTDIVPD_BITS);

    pll_frequencies[pll] = vco_frequency / (postdiv1 * postdiv2);
}

mj_u32 pll_get_frequency(pll_t pll) {
    return pll_frequencies[pll];
}
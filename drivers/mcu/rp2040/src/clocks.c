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

#include <rp2040/clocks.h>

#include <assert.h>

#include <rp2040/memory.h>
#include <rp2040/pll.h>
#include <rp2040/xosc.h>

/* clock_clk_configure relies on this equality */
#if (CLOCKS_CLK_REF_SRC_AUXSRC != CLOCKS_CLK_SYS_SRC_AUXSRC)
    #error CLOCKS_CLK_REF_SRC_AUXSRC and CLOCKS_CLK_SYS_SRC_AUXSRC should be equal
#endif

#define CLOCKS_BASE 0x40008000u

#define CLOCKS_CLK_CTRL_ENABLE_LSB          11u
#define CLOCKS_CLK_CTRL_ENABLE_BITS         0x00000800u

#define CLOCKS_CLK_CTRL_AUXSRC_LSB          5u
#define CLOCKS_CLK_CTRL_AUXSRC_BITS         0x000001e0u
/* values of this field defined in clocks.h, but they're not shifted by LSB */

#define CLOCKS_CLK_CTRL_SRC_LSB             0u
#define CLOCKS_CLK_CTRL_SRC_BITS            0x00000003u
/* values of this field defined in clocks.h, but they're not shifted by LSB */

#define CLOCKS_CLK_DIV_INT_LSB              8u
#define CLOCKS_CLK_DIV_INT_BITS             0xffffff00u

#define CLOCKS_CLK_SYS_FREQ     125000000u
#define CLOCKS_CLK_REF_FREQ     XOSC_FREQ
#define CLOCKS_CLK_USB_FREQ     48000000u
#define CLOCKS_CLK_ADC_FREQ     48000000u
#define CLOCKS_CLK_RTC_FREQ     46875u
#define CLOCKS_CLK_PERI_FREQ    125000000u

static mj_u32 clocks_frequencies[CLOCKS_CLK_COUNT];

typedef struct {
    mj_u32 ctrl;
    mj_u32 div;
    mj_u32 selected;
} clock_hw_t;

static mj_bool has_main_source(clocks_clk_t clock) {
    return (clock == CLOCKS_CLK_REF || clock == CLOCKS_CLK_SYS);
}

static clock_hw_t *select_clock(clocks_clk_t clock) {
    clock_hw_t *clk = (clock_hw_t *) CLOCKS_BASE + clock;

    return ((clock_hw_t *) CLOCKS_BASE + clock);
}

void clocks_init() {
    xosc_init();

    clock_hw_t *clk = select_clock(CLOCKS_CLK_SYS);
    memory_write_masked(&clk->ctrl, CLOCKS_CLK_SYS_SRC_CLK_REF, CLOCKS_CLK_CTRL_SRC_BITS);
    while(clk->selected != 0x1) { }

    clk = select_clock(CLOCKS_CLK_REF);
    memory_write_masked(&clk->ctrl, CLOCKS_CLK_REF_SRC_ROSC, CLOCKS_CLK_CTRL_SRC_BITS);
    while(clk->selected != 0x1) { }

    pll_init();
    
    clocks_clk_configure(
        CLOCKS_CLK_REF, CLOCKS_CLK_REF_SRC_XOSC,
        CLOCKS_CLK_AUXSRC_NONE, XOSC_FREQ, CLOCKS_CLK_REF_FREQ
    );

    clocks_clk_configure(
        CLOCKS_CLK_SYS, CLOCKS_CLK_SYS_SRC_AUXSRC,
        CLOCKS_CLK_SYS_AUXSRC_PLL_SYS, pll_get_frequency(PLL_SYS), CLOCKS_CLK_SYS_FREQ
    );

    clocks_clk_configure(
        CLOCKS_CLK_USB, CLOCKS_CLK_SRC_NONE,
        CLOCKS_CLK_USB_AUXSRC_PLL_USB, pll_get_frequency(PLL_SYS), CLOCKS_CLK_USB_FREQ
    );

    clocks_clk_configure(
        CLOCKS_CLK_ADC, CLOCKS_CLK_SRC_NONE,
        CLOCKS_CLK_ADC_AUXSRC_PLL_USB, pll_get_frequency(PLL_SYS), CLOCKS_CLK_ADC_FREQ
    );

    clocks_clk_configure(
        CLOCKS_CLK_RTC, CLOCKS_CLK_SRC_NONE,
        CLOCKS_CLK_RTC_AUXSRC_PLL_USB, pll_get_frequency(PLL_SYS), CLOCKS_CLK_RTC_FREQ
    );

    clocks_clk_configure(
        CLOCKS_CLK_PERI, CLOCKS_CLK_SRC_NONE,
        CLOCKS_CLK_PERI_AUXSRC_CLK_SYS, clocks_clk_get_frequency(CLOCKS_CLK_SYS),
        CLOCKS_CLK_PERI_FREQ
    );
}

void clocks_clk_configure(clocks_clk_t clock, mj_u32 source, mj_u32 aux_source, mj_u32 source_frequency, mj_u32 frequency) {
    assert(frequency <= source_frequency);
    mj_u32 div = ((mj_u64) source_frequency << CLOCKS_CLK_DIV_INT_LSB) / frequency;
    clock_hw_t *clock_hw = select_clock(clock);

    if(div > clock_hw->div) {
        clock_hw->div = div;
    }

    if(has_main_source(clock) && source == CLOCKS_CLK_SYS_SRC_AUXSRC) {
        memory_atomic_clear(&clock_hw->ctrl, CLOCKS_CLK_CTRL_SRC_BITS);
        while(!(clock_hw->selected & 1u)) { }
    } else {
        memory_atomic_clear(&clock_hw->ctrl, CLOCKS_CLK_CTRL_ENABLE_BITS);

        if(clocks_frequencies[clock] > 0) {
            mj_u32 delay = clocks_frequencies[CLOCKS_CLK_SYS] / clocks_frequencies[clock] + 1;
            // wait at least delay cycles
            while(delay != 0) {
                delay--;
            }
        }
    }

    memory_write_masked(&clock_hw->ctrl, aux_source << CLOCKS_CLK_CTRL_AUXSRC_LSB, CLOCKS_CLK_CTRL_AUXSRC_BITS);

    if(has_main_source(clock)) {
        memory_write_masked(&clock_hw->ctrl, source << CLOCKS_CLK_CTRL_SRC_LSB, CLOCKS_CLK_CTRL_SRC_BITS);

        while(!(clock_hw->selected & (1u << source))) { }
    }

    memory_atomic_set(&clock_hw->ctrl, CLOCKS_CLK_CTRL_ENABLE_BITS);
    clock_hw->div = div;
    clocks_frequencies[clock] = frequency;
}

mj_u32 clocks_clk_get_frequency(clocks_clk_t clock) {
    return clocks_frequencies[clock];
}
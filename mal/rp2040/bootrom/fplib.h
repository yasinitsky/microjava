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
 * @file    fplib.h
 * @brief   This file contains functions offsets in bootrom floating point library.
 *          See RP2040 Datasheet, Chapter 2.8.3.2
 */

#ifndef MJ_HW_RP2040_BOOTROM_FPLIB_H
#define MJ_HW_RP2040_BOOTROM_FPLIB_H

#define BOOTROM_FPLIB_FADD          0x00u
#define BOOTROM_FPLIB_FSUB          0x04u
#define BOOTROM_FPLIB_FMUL          0x08u
#define BOOTROM_FPLIB_FDIV          0x0cu
#define BOOTROM_FPLIB_FSQRT         0x18u
#define BOOTROM_FPLIB_FLOAT2INT     0x1cu
#define BOOTROM_FPLIB_FLOAT2FIX     0x20u
#define BOOTROM_FPLIB_FLOAT2UINT    0x24u
#define BOOTROM_FPLIB_FLOAT2UFIX    0x28u
#define BOOTROM_FPLIB_INT2FLOAT     0x2cu
#define BOOTROM_FPLIB_FIX2FLOAT     0x30u
#define BOOTROM_FPLIB_UINT2FLOAT    0x34u
#define BOOTROM_FPLIB_UFIX2FLOAT    0x38u
#define BOOTROM_FPLIB_FCOS          0x3cu
#define BOOTROM_FPLIB_FSIN          0x40u
#define BOOTROM_FPLIB_FTAN          0x44u
#define BOOTROM_FPLIB_FEXP          0x4cu
#define BOOTROM_FPLIB_FLN           0x50u
#define BOOTROM_FPLIB_FCMP          0x54u
#define BOOTROM_FPLIB_FATAN2        0x58u
#define BOOTROM_FPLIB_INT642FLOAT   0x5cu
#define BOOTROM_FPLIB_FIX642FLOAT   0x60u
#define BOOTROM_FPLIB_UINT642FLOAT  0x64u
#define BOOTROM_FPLIB_UFIX642FLOAT  0x68u
#define BOOTROM_FPLIB_FLOAT2INT64   0x6cu
#define BOOTROM_FPLIB_FLOAT2FIX64   0x70u
#define BOOTROM_FPLIB_FLOAT2UINT64  0x74u
#define BOOTROM_FPLIB_FLOAT2UFIX64  0x78u
#define BOOTROM_FPLIB_FLOAT2DOUBLE  0x7cu

#define BOOTROM_FPLIB_DADD          0x00u
#define BOOTROM_FPLIB_DSUB          0x04u
#define BOOTROM_FPLIB_DMUL          0x08u
#define BOOTROM_FPLIB_DDIV          0x0cu
#define BOOTROM_FPLIB_DSQRT         0x18u
#define BOOTROM_FPLIB_DOUBLE2INT    0x1cu
#define BOOTROM_FPLIB_DOUBLE2FIX    0x20u
#define BOOTROM_FPLIB_DOUBLE2UINT   0x24u
#define BOOTROM_FPLIB_DOUBLE2UFIX   0x28u
#define BOOTROM_FPLIB_INT2DOUBLE    0x2cu
#define BOOTROM_FPLIB_FIX2DOUBLE    0x30u
#define BOOTROM_FPLIB_UINT2DOUBLE   0x34u
#define BOOTROM_FPLIB_UFIX2DOUBLE   0x38u
#define BOOTROM_FPLIB_DCOS          0x3cu
#define BOOTROM_FPLIB_DSIN          0x40u
#define BOOTROM_FPLIB_DTAN          0x44u
#define BOOTROM_FPLIB_DEXP          0x4cu
#define BOOTROM_FPLIB_DLN           0x50u
#define BOOTROM_FPLIB_DCMP          0x54u
#define BOOTROM_FPLIB_DATAN2        0x58u
#define BOOTROM_FPLIB_INT642DOUBLE  0x5cu
#define BOOTROM_FPLIB_FIX642DOUBLE  0x60u
#define BOOTROM_FPLIB_UINT642DOUBLE 0x64u
#define BOOTROM_FPLIB_UFIX642DOUBLE 0x68u
#define BOOTROM_FPLIB_DOUBLE2INT64  0x6cu
#define BOOTROM_FPLIB_DOUBLE2FIX64  0x70u
#define BOOTROM_FPLIB_DOUBLE2UINT64 0x74u
#define BOOTROM_FPLIB_DOUBLE2UFIX64 0x78u
#define BOOTROM_FPLIB_DOUBLE2FLOAT  0x7cu

#endif // MJ_HW_RP2040_BOOTROM_FPLIB_H
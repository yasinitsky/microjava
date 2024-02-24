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

#include <rp2040/floating_point.h>

#include <rp2040/bootrom.h>
#include <rp2040/fplib.h>

/**
 * @brief   Pointers to floating point functions in bootrom. Filled once by @ref floating_point_init().
 *          See RP2040 Datasheet, Chapter 2.8.3.2
 */
static struct {
    float (*fadd)(float, float);
    float (*fsub)(float, float);
    float (*fmul)(float, float);
    float (*fdiv)(float, float);
    int (*fcmp)(float, float);

    double (*dadd)(double, double);
    double (*dsub)(double, double);
    double (*dmul)(double, double);
    double (*ddiv)(double, double);
    int (*dcmp)(double, double);

    int (*float2int)(float);
    unsigned (*float2uint)(float);
    long long (*float2int64)(float);
    unsigned long long (*float2uint64)(float);

    int (*double2int)(double);
    unsigned (*double2uint)(double);
    long long (*double2int64)(double);
    unsigned long long (*double2uint64)(double);

    double (*float2double)(float);
    float (*double2float)(double);

    float (*int2float)(int);
    float (*uint2float)(unsigned);
    float (*int642float)(long long);
    float (*uint642float)(unsigned long long);

    double (*int2double)(int);
    double (*uint2double)(unsigned);
    double (*int642double)(long long);
    double (*uint642double)(unsigned long long);
} floating_point_funcs;

void floating_point_init() {
    void *float_base = bootrom_data_lookup(bootrom_table_code('S', 'F'));
    floating_point_funcs.fadd = *(void **)(float_base + BOOTROM_FPLIB_FADD);
    floating_point_funcs.fsub = *(void **)(float_base + BOOTROM_FPLIB_FSUB);
    floating_point_funcs.fmul = *(void **)(float_base + BOOTROM_FPLIB_FMUL);
    floating_point_funcs.fdiv = *(void **)(float_base + BOOTROM_FPLIB_FDIV);
    floating_point_funcs.fcmp = *(void **)(float_base + BOOTROM_FPLIB_FCMP);
    floating_point_funcs.float2int = *(void **)(float_base + BOOTROM_FPLIB_FLOAT2INT);
    floating_point_funcs.float2uint = *(void **)(float_base + BOOTROM_FPLIB_FLOAT2UINT);
    floating_point_funcs.float2int64 = *(void **)(float_base + BOOTROM_FPLIB_FLOAT2INT64);
    floating_point_funcs.float2uint64 = *(void **)(float_base + BOOTROM_FPLIB_FLOAT2UINT64);
    floating_point_funcs.float2double = *(void **)(float_base + BOOTROM_FPLIB_FLOAT2DOUBLE);
    floating_point_funcs.int2float = *(void **)(float_base + BOOTROM_FPLIB_INT2FLOAT);
    floating_point_funcs.uint2float = *(void **)(float_base + BOOTROM_FPLIB_UINT2FLOAT);
    floating_point_funcs.int642float = *(void **)(float_base + BOOTROM_FPLIB_INT642FLOAT);
    floating_point_funcs.uint642float = *(void **)(float_base + BOOTROM_FPLIB_UINT642FLOAT);

    void *double_base = bootrom_data_lookup(bootrom_table_code('S', 'D'));
    floating_point_funcs.dadd = *(void **)(double_base + BOOTROM_FPLIB_DADD);
    floating_point_funcs.dsub = *(void **)(double_base + BOOTROM_FPLIB_DSUB);
    floating_point_funcs.dmul = *(void **)(double_base + BOOTROM_FPLIB_DMUL);
    floating_point_funcs.ddiv = *(void **)(double_base + BOOTROM_FPLIB_DDIV);
    floating_point_funcs.dcmp = *(void **)(double_base + BOOTROM_FPLIB_DCMP);
    floating_point_funcs.double2int = *(void **)(double_base + BOOTROM_FPLIB_DOUBLE2INT);
    floating_point_funcs.double2uint = *(void **)(double_base + BOOTROM_FPLIB_DOUBLE2UINT);
    floating_point_funcs.double2int64 = *(void **)(double_base + BOOTROM_FPLIB_DOUBLE2INT64);
    floating_point_funcs.double2uint64 = *(void **)(double_base + BOOTROM_FPLIB_DOUBLE2UINT64);
    floating_point_funcs.double2float = *(void **)(double_base + BOOTROM_FPLIB_DOUBLE2FLOAT);
    floating_point_funcs.int2double = *(void **)(double_base + BOOTROM_FPLIB_INT2DOUBLE);
    floating_point_funcs.uint2double = *(void **)(double_base + BOOTROM_FPLIB_UINT2DOUBLE);
    floating_point_funcs.int642double = *(void **)(double_base + BOOTROM_FPLIB_INT642DOUBLE);
    floating_point_funcs.uint642double = *(void **)(double_base + BOOTROM_FPLIB_UINT642DOUBLE);
}

float __aeabi_fadd(float a, float b) {
    return floating_point_funcs.fadd(a, b);
}

float __aeabi_fdiv(float n, float d) {
    return floating_point_funcs.fdiv(n, d);
}

float __aeabi_fmul(float a, float b) {
    return floating_point_funcs.fmul(a, b);
}

float __aeabi_frsub(float x, float y) {
    return floating_point_funcs.fsub(y, x);
}

float __aeabi_fsub(float x, float y) {
    return floating_point_funcs.fsub(x, y);
}

int __aeabi_fcmpeq(float a, float b) {
    return floating_point_funcs.fcmp(a, b) == 0;
}

int __aeabi_fcmplt(float a, float b) {
    return floating_point_funcs.fcmp(a, b) == -1;
}

int __aeabi_fcmple(float a, float b) {
    int cmp = floating_point_funcs.fcmp(a, b);
    return cmp == -1 || cmp == 0; 
}

int __aeabi_fcmpge(float a, float b) {
    int cmp = floating_point_funcs.fcmp(a, b);
    return cmp == 0 || cmp == 1; 
}

int __aeabi_fcmpgt(float a, float b) {
    return floating_point_funcs.fcmp(a, b) == 1;
}

double __aeabi_dadd(double a, double b) {
    return floating_point_funcs.dadd(a, b);
}

double __aeabi_ddiv(double n, double d) {
    return floating_point_funcs.ddiv(n, d);
}

double __aeabi_dmul(double a, double b) {
    return floating_point_funcs.dmul(a, b);
}

double __aeabi_drsub(double x, double y) {
    return floating_point_funcs.dsub(y, x);
}

double __aeabi_dsub(double x, double y) {
    return floating_point_funcs.dsub(x, y);
}

int __aeabi_dcmpeq(double a, double b) {
    return floating_point_funcs.dcmp(a, b) == 0;
}

int __aeabi_dcmplt(double a, double b) {
    return floating_point_funcs.dcmp(a, b) == -1;
}

int __aeabi_dcmple(double a, double b) {
    int cmp = floating_point_funcs.dcmp(a, b);
    return cmp == -1 || cmp == 0; 
}

int __aeabi_dcmpge(double a, double b) {
    int cmp = floating_point_funcs.dcmp(a, b);
    return cmp == 0 || cmp == 1; 
}

int __aeabi_dcmpgt(double a, double b) {
    return floating_point_funcs.dcmp(a, b) == 1;
}

int __aeabi_f2iz(float v) {
    return floating_point_funcs.float2int(v);
}

unsigned __aeabi_f2uiz(float v) {
    return floating_point_funcs.float2uint(v);
}

long long __aeabi_f2lz(float v) {
    return floating_point_funcs.float2int64(v);
}

unsigned long long __aeabi_f2ulz(float v) {
    return floating_point_funcs.float2uint64(v);
}

int __aeabi_d2iz(double v) {
    return floating_point_funcs.double2int(v);
}

unsigned __aeabi_d2uiz(double v) {
    return floating_point_funcs.double2uint(v);
}

long long __aeabi_d2lz(double v) {
    return floating_point_funcs.double2int64(v);
}

unsigned long long __aeabi_d2ulz(double v) {
    return floating_point_funcs.double2uint64(v);
}

double __aeabi_f2d(float v) {
    return floating_point_funcs.float2double(v);
}

float __aeabi_d2f(double v) {
    return floating_point_funcs.double2float(v);
}

float __aeabi_i2f(int v) {
    return floating_point_funcs.int2float(v);
}

float __aeabi_ui2f(unsigned v) {
    return floating_point_funcs.uint2float(v);
}

float __aeabi_l2f(long long v) {
    return floating_point_funcs.int642float(v);
}

float __aeabi_ul2f(unsigned long long v) {
    return floating_point_funcs.uint642float(v);
}

double __aeabi_i2d(int v) {
    return floating_point_funcs.int2double(v);
}

double __aeabi_ui2d(unsigned v) {
    return floating_point_funcs.uint2double(v);
}

double __aeabi_l2d(long long v) {
    return floating_point_funcs.int642double(v);
}

double __aeabi_ul2d(unsigned long long v) {
    return floating_point_funcs.uint642double(v);
}
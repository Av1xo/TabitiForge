/*
 * Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
 * TabitiForge Simulation Engine
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_PLATFORM_TYPES_H
#define TABITIFORGE_PLATFORM_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "tabitiforge/numeric/types.h"
#include "tabitiforge/platform/compiler.h"

/* =========================================================================
 * EXPLICIT FLOATING-POINT ALIASES
 * ========================================================================= */

typedef float tf_f32;
typedef double tf_f64;

_Static_assert(sizeof(tf_f32) == 4, "tf_f32 must be exactly 4 bytes");

_Static_assert(sizeof(tf_f64) == 8, "tf_f64 must be exactly 8 bytes");

/* =========================================================================
 * 128-BIT FLOATING-POINT TYPE
 * ========================================================================= */

/*
 * IEEE 754 binary128 / quadruple precision.
 *
 * Supported by GCC/Clang through __float128.
 * _Float128 is used when the compiler exposes it.
 *
 * MSVC currently has no native 128-bit floating-point type.
 */

#if defined(__FLT128_MANT_DIG__) || defined(__SIZEOF_FLOAT128__)

#define TF_HAS_FLOAT128 1

#if defined(__FLT128_MANT_DIG__)
typedef _Float128 tf_f128;
#else
typedef __float128 tf_f128;
#endif

_Static_assert(sizeof(tf_f128) == 16, "tf_f128 must be exactly 16 bytes");

#else

#define TF_HAS_FLOAT128 0

#endif

/* =========================================================================
 * 128-BIT INTEGER TYPES
 * ========================================================================= */

/*
 * GCC and Clang expose __int128 as a language extension.
 *
 * This is independent from pointer width: a compiler may support
 * __int128 even when targeting a 32-bit ABI.
 */

#if (TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG) &&                        \
    defined(__SIZEOF_INT128__)

#define TF_HAS_INT128 1

typedef __int128 tf_i128;
typedef unsigned __int128 tf_u128;

_Static_assert(sizeof(tf_i128) == 16, "tf_i128 must be exactly 16 bytes");

_Static_assert(sizeof(tf_u128) == 16, "tf_u128 must be exactly 16 bytes");

#else

#define TF_HAS_INT128 0

#endif

/* =========================================================================
 * BOOLEAN TYPES
 * ========================================================================= */

typedef bool tf_b8;
typedef tf_u32 tf_b32;

#define TF_TRUE  1
#define TF_FALSE 0

/* =========================================================================
 * CHARACTER & STRING TYPES
 * ========================================================================= */

/*
 * Raw platform character.
 *
 * Signedness depends on the target/compiler configuration.
 * Use for ordinary C strings and standard library interfaces.
 */

typedef char tf_char;

/*
 * Explicit signed/unsigned character types.
 */

typedef signed char tf_schar;
typedef unsigned char tf_uchar;

/*
 * Unicode code units.
 *
 * UTF-8  -> 8-bit
 * UTF-16 -> 16-bit
 * UTF-32 -> 32-bit
 */

typedef tf_u8 tf_utf8;
typedef tf_u16 tf_utf16;
typedef tf_u32 tf_utf32;

_Static_assert(sizeof(tf_char) == 1, "tf_char must be exactly 1 byte");

_Static_assert(sizeof(tf_utf8) == 1, "tf_utf8 must be exactly 1 byte");

_Static_assert(sizeof(tf_utf16) == 2, "tf_utf16 must be exactly 2 bytes");

_Static_assert(sizeof(tf_utf32) == 4, "tf_utf32 must be exactly 4 bytes");

/* =========================================================================
 * POINTER & ADDRESS TYPES
 * ========================================================================= */

typedef uintptr_t tf_uintptr;
typedef intptr_t tf_intptr;

typedef tf_u8 tf_byte;

_Static_assert(sizeof(tf_uintptr) == sizeof(void *), "tf_uintptr must match pointer size");

_Static_assert(sizeof(tf_intptr) == sizeof(void *), "tf_intptr must match pointer size");

/* =========================================================================
 * COMMON MACROS & UTILITIES
 * ========================================================================= */

#ifndef TF_NULL

#ifdef __cplusplus

#define TF_NULL 0

#else

#define TF_NULL ((void *)0)

#endif

#endif

/* =========================================================================
 * STATIC ARRAY UTILITIES
 * ========================================================================= */

/*
 * Static array element count.
 *
 * Must only be used with actual arrays, not pointers.
 */

#define TF_ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))

/* =========================================================================
 * BYTE UNIT CONVERSION
 * ========================================================================= */

/*
 * Memory size helpers.
 *
 * The argument is converted to tf_size before multiplication.
 */

#define TF_KB(value) ((tf_size)(value) * (tf_size)1024)

#define TF_MB(value) (TF_KB(value) * (tf_size)1024)

#define TF_GB(value) (TF_MB(value) * (tf_size)1024)

/* =========================================================================
 * POINTER / OFFSET ALIGNMENT
 * ========================================================================= */

/*
 * Align an integer value to the next multiple of a power-of-two alignment.
 *
 * Requirements:
 *   - alignment != 0
 *   - alignment must be a power of two
 */

#define TF_ALIGN_POW2(value, alignment) (((value) + ((alignment) - 1)) & ~((alignment) - 1))

/*
 * Compile-time/runtime-friendly power-of-two check.
 */

#define TF_IS_POW2(value) ((value) != 0 && (((value) & ((value) - 1)) == 0))

#endif /* TABITIFORGE_PLATFORM_TYPES_H */
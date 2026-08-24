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
 * distributed undegir the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_PLATFORM_TYPES_H
#define TABITIFORGE_PLATFORM_TYPES_H

#include <stdbool.h>

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
 * 128-BIT FLOATING-POINT TYPE (OPTIONAL / EXTENSION)
 * ========================================================================= */

/*
 * IEEE 754 binary128 (Quadruple Precision).
 * Supported via _Float128 (C23 / ISO TS 18661-3 extension) or __float128 (GCC/Clang extension).
 * MSVC does not support 128-bit floating-point types natively.
 */
#if defined(__FLOAT128__) || defined(__SIZEOF_FLOAT128__) ||                                       \
    ((TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG) &&                       \
     (TF_ARCH == TF_ARCH_X86_64 || TF_ARCH == TF_ARCH_AARCH64))
#define TF_HAS_FLOAT128 1

/*
 * Check if standard C _Float128 keyword/type is enabled.
 * Otherwise fallback to GCC/Clang built-in __float128.
 */
#if defined(__FLT128_MANT_DIG__) || (defined(__HAVE_FLOAT128) && __HAVE_FLOAT128)
typedef _Float128 tf_f128;
#else
typedef __float128 tf_f128;
#endif
_Static_assert(sizeof(tf_f128) == 16, "tf_f128 must be exactly 16 bytes");
#else
#define TF_HAS_FLOAT128 0
#endif

/* =========================================================================
 * 128-BIT INTEGER TYPES (OPTIONAL / EXTENSION)
 * ========================================================================= */

/*
 * GCC and Clang support __int128 on 64-bit targets as a language extension.
 * MSVC does not support native 128-bit integer types in C.
 */
#if (TF_COMPILER == TF_COMPILER_GCC || TF_COMPILER == TF_COMPILER_CLANG) &&                        \
    (TF_PTR_BITS == TF_PTR_BITS_64)
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
 * POINTER & ADDRESS TYPES
 * ========================================================================= */
typedef uintptr_t tf_uintptr;
typedef intptr_t tf_intptr;
typedef tf_u8 tf_byte;

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

/*
 * Static array element count calculation.
 */
#define TF_ARRAY_COUNT(array) (sizeof(array) / sizeof((array)[0]))

/*
 * Byte unit conversion macros for memory allocators & arenas.
 */
#define TF_KB(value) ((tf_size)(value) * (tf_size)1024)
#define TF_MB(value) (TF_KB(value) * (tf_size)1024)
#define TF_GB(value) (TF_MB(value) * (tf_size)1024)

/*
 * Pointer / Offset alignment helpers.
 */
#define TF_ALIGN_POW2(value, alignment) (((value) + ((alignment) - 1)) & ~((alignment) - 1))
#define TF_IS_POW2(value)               ((value) != 0 && ((value) & ((value) - 1)) == 0)

#endif // TABITIFORGE_PLATFORM_TYPES_H
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

#ifndef TABITIFORGE_NUMERIC_TYPES_H
#define TABITIFORGE_NUMERIC_TYPES_H

#include <float.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/* ========================================================================= */
/* REAL TYPE CONFIGURATION                                                   */
/* ========================================================================= */

/*
 * Exactly one real representation may be selected.
 *
 * TF_REAL_FLOAT64 is the default configuration.
 *
 * The portable numeric contract intentionally supports only the standard
 * C floating-point types float and double.
 */

#if (defined(TF_REAL_FLOAT32) + defined(TF_REAL_FLOAT64)) > 1

#error "Multiple real types selected"

#endif

#if !defined(TF_REAL_FLOAT32) && !defined(TF_REAL_FLOAT64)

#define TF_REAL_FLOAT64

#endif

/* ========================================================================= */
/* REAL TYPE                                                                 */
/* ========================================================================= */

#if defined(TF_REAL_FLOAT32)

typedef float real_t;

#define TF_REAL_IS_FLOAT32 1
#define TF_REAL_IS_FLOAT64 0

#elif defined(TF_REAL_FLOAT64)

typedef double real_t;

#define TF_REAL_IS_FLOAT32 0
#define TF_REAL_IS_FLOAT64 1

#endif

/* ========================================================================= */
/* INTEGER TYPES                                                             */
/* ========================================================================= */

typedef int8_t tf_i8;
typedef uint8_t tf_u8;

typedef int16_t tf_i16;
typedef uint16_t tf_u16;

typedef int32_t tf_i32;
typedef uint32_t tf_u32;

typedef int64_t tf_i64;
typedef uint64_t tf_u64;

/* ========================================================================= */
/* PLATFORM-SIZED TYPES                                                      */
/* ========================================================================= */

typedef size_t tf_size;
typedef ptrdiff_t tf_isize;

/* ========================================================================= */
/* REAL TYPE PROPERTIES                                                      */
/* ========================================================================= */

_Static_assert(CHAR_BIT == 8, "TabitiForge requires 8-bit bytes (CHAR_BIT == 8)");

/*
 * Number of bits occupied by real_t.
 */
#define TF_REAL_SIZE (sizeof(real_t))
#define TF_REAL_BITS (sizeof(real_t) * CHAR_BIT)

/*
 * Radix of the real floating-point representation.
 */
#if defined(TF_REAL_FLOAT32)

#define TF_REAL_RADIX    FLT_RADIX
#define TF_REAL_MANT_DIG FLT_MANT_DIG
#define TF_REAL_MIN_EXP  FLT_MIN_EXP
#define TF_REAL_MAX_EXP  FLT_MAX_EXP

#elif defined(TF_REAL_FLOAT64)

#define TF_REAL_RADIX    FLT_RADIX
#define TF_REAL_MANT_DIG DBL_MANT_DIG
#define TF_REAL_MIN_EXP  DBL_MIN_EXP
#define TF_REAL_MAX_EXP  DBL_MAX_EXP

#endif

/* ========================================================================= */
/* IEEE 754 / IEC 60559 COMPATIBILITY CONTRACT                               */
/* ========================================================================= */

/*
 * These checks verify the fundamental parameters of the selected
 * binary floating-point representation.
 *
 * They do NOT prove complete IEEE 754 / ISO/IEC 60559 conformance.
 */

/* ------------------------------------------------------------------------- */
/* binary32                                                                   */
/* ------------------------------------------------------------------------- */

#if defined(TF_REAL_FLOAT32)

_Static_assert(sizeof(real_t) == 4, "TF_REAL_FLOAT32 requires a 32-bit real_t");

_Static_assert(FLT_RADIX == 2, "TF_REAL_FLOAT32 requires binary radix");

_Static_assert(FLT_MANT_DIG == 24, "TF_REAL_FLOAT32 requires binary32 precision");

_Static_assert(FLT_MAX_EXP == 128, "TF_REAL_FLOAT32 requires binary32 exponent range");

_Static_assert(FLT_MIN_EXP == -125, "TF_REAL_FLOAT32 requires binary32 exponent range");

#if !defined(FLT_TRUE_MIN)
#error "TF_REAL_FLOAT32 requires FLT_TRUE_MIN support"
#endif

/* ------------------------------------------------------------------------- */
/* binary64                                                                   */
/* ------------------------------------------------------------------------- */

#elif defined(TF_REAL_FLOAT64)

_Static_assert(sizeof(real_t) == 8, "TF_REAL_FLOAT64 requires a 64-bit real_t");

_Static_assert(FLT_RADIX == 2, "TF_REAL_FLOAT64 requires binary radix");

_Static_assert(DBL_MANT_DIG == 53, "TF_REAL_FLOAT64 requires binary64 precision");

_Static_assert(DBL_MAX_EXP == 1024, "TF_REAL_FLOAT64 requires binary64 exponent range");

_Static_assert(DBL_MIN_EXP == -1021, "TF_REAL_FLOAT64 requires binary64 exponent range");

#if !defined(DBL_TRUE_MIN)
#error "TF_REAL_FLOAT64 requires DBL_TRUE_MIN support"
#endif

#endif

/* ========================================================================= */
/* REAL LIMITS                                                               */
/* ========================================================================= */

#if defined(TF_REAL_FLOAT32)

#define TF_REAL_MIN_EXP10  FLT_MIN_10_EXP
#define TF_REAL_MAX_EXP10  FLT_MAX_10_EXP
#define TF_REAL_TRUE_MIN   FLT_TRUE_MIN
#define TF_REAL_MIN_NORMAL FLT_MIN
#define TF_REAL_MAX        FLT_MAX
#define TF_REAL_EPSILON    FLT_EPSILON

#elif defined(TF_REAL_FLOAT64)

#define TF_REAL_MIN_EXP10  DBL_MIN_10_EXP
#define TF_REAL_MAX_EXP10  DBL_MAX_10_EXP
#define TF_REAL_TRUE_MIN   DBL_TRUE_MIN
#define TF_REAL_MIN_NORMAL DBL_MIN
#define TF_REAL_MAX        DBL_MAX
#define TF_REAL_EPSILON    DBL_EPSILON

#endif

#endif /* TABITIFORGE_NUMERIC_TYPES_H */
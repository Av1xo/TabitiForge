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

#ifndef TABITIFORGE_NUMERIC_LIMITS_H
#define TABITIFORGE_NUMERIC_LIMITS_H

#include <limits.h>
#include <stdint.h>

#include "tabitiforge/numeric/types.h"

/* ========================================================================= */
/* INTEGER LIMITS                                                           */
/* ========================================================================= */

/* 8-bit */
#define TF_I8_MIN INT8_MIN
#define TF_I8_MAX INT8_MAX

#define TF_U8_MIN UINT8_C(0)
#define TF_U8_MAX UINT8_MAX

/* 16-bit */
#define TF_I16_MIN INT16_MIN
#define TF_I16_MAX INT16_MAX

#define TF_U16_MIN UINT16_C(0)
#define TF_U16_MAX UINT16_MAX

/* 32-bit */
#define TF_I32_MIN INT32_MIN
#define TF_I32_MAX INT32_MAX

#define TF_U32_MIN UINT32_C(0)
#define TF_U32_MAX UINT32_MAX

/* 64-bit */
#define TF_I64_MIN INT64_MIN
#define TF_I64_MAX INT64_MAX

#define TF_U64_MIN UINT64_C(0)
#define TF_U64_MAX UINT64_MAX

/* ========================================================================= */
/* PLATFORM LIMITS                                                          */
/* ========================================================================= */

/*
 * Native size type.
 */
#define TF_SIZE_MIN ((tf_size)0)
#define TF_SIZE_MAX SIZE_MAX

/*
 * ptrdiff_t range.
 */
#define TF_ISIZE_MIN PTRDIFF_MIN
#define TF_ISIZE_MAX PTRDIFF_MAX

/* ========================================================================= */
/* C FUNDAMENTAL LIMITS                                                     */
/* ========================================================================= */

/*
 * Number of bits in a byte.
 *
 * TabitiForge additionally requires CHAR_BIT == 8 in types.h.
 */
#define TF_CHAR_BIT CHAR_BIT

/*
 * Limits of native C integer types.
 *
 * These are exposed only when code explicitly needs the native C type.
 */
#define TF_INT_MIN INT_MIN
#define TF_INT_MAX INT_MAX

#define TF_UINT_MIN 0U
#define TF_UINT_MAX UINT_MAX

#define TF_LONG_MIN LONG_MIN
#define TF_LONG_MAX LONG_MAX

#define TF_ULONG_MIN 0UL
#define TF_ULONG_MAX ULONG_MAX

#define TF_LLONG_MIN LLONG_MIN
#define TF_LLONG_MAX LLONG_MAX

#define TF_ULLONG_MIN 0ULL
#define TF_ULLONG_MAX ULLONG_MAX

#endif /* TABITIFORGE_NUMERIC_LIMITS_H */
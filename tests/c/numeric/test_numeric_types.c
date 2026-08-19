/*
 * Copyright (C) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
 * SPDX-FileCopyrightText: 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include "tabitiforge/numeric/types.h"

int main(void) {
    /* Configuration */
#if defined(TF_REAL_FLOAT32)

    assert(TF_REAL_IS_FLOAT32 == 1);
    assert(TF_REAL_IS_FLOAT64 == 0);

    assert(sizeof(real_t) == sizeof(float));

    assert(TF_REAL_BITS == 32);
    assert(TF_REAL_RADIX == 2);
    assert(TF_REAL_MANT_DIG == 24);

    assert(TF_REAL_TRUE_MIN == FLT_TRUE_MIN);
    assert(TF_REAL_MIN_NORMAL == FLT_MIN);
    assert(TF_REAL_MAX == FLT_MAX);
    assert(TF_REAL_EPSILON == FLT_EPSILON);

#elif defined(TF_REAL_FLOAT64)

    assert(TF_REAL_IS_FLOAT32 == 0);
    assert(TF_REAL_IS_FLOAT64 == 1);

    assert(sizeof(real_t) == sizeof(double));

    assert(TF_REAL_BITS == 64);
    assert(TF_REAL_RADIX == 2);
    assert(TF_REAL_MANT_DIG == 53);

    assert(TF_REAL_TRUE_MIN == DBL_TRUE_MIN);
    assert(TF_REAL_MIN_NORMAL == DBL_MIN);
    assert(TF_REAL_MAX == DBL_MAX);
    assert(TF_REAL_EPSILON == DBL_EPSILON);

#endif

    /* Basic numerical ordering */

    assert(TF_REAL_TRUE_MIN > 0);
    assert(TF_REAL_MIN_NORMAL > TF_REAL_TRUE_MIN);
    assert(TF_REAL_MAX > TF_REAL_MIN_NORMAL);
    assert(TF_REAL_EPSILON > 0);

    /* Integer aliases */

    assert(sizeof(tf_i8) == 1);
    assert(sizeof(tf_u8) == 1);

    assert(sizeof(tf_i16) == 2);
    assert(sizeof(tf_u16) == 2);

    assert(sizeof(tf_i32) == 4);
    assert(sizeof(tf_u32) == 4);

    assert(sizeof(tf_i64) == 8);
    assert(sizeof(tf_u64) == 8);

    return 0;
}
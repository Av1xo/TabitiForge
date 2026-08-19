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

#ifndef TABITIFORGE_NUMERIC_COMPARE_H
#define TABITIFORGE_NUMERIC_COMPARE_H

#include <math.h>
#include <stdbool.h>

#include "tabitiforge/numeric/tolerance.h"
#include "tabitiforge/numeric/types.h"

/* ========================================================================= */
/* SCALAR OPERATIONS                                                         */
/* ========================================================================= */

static inline real_t tf_abs(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return fabsf(x);
#elif defined(TF_REAL_FLOAT64)
    return fabs(x);
#endif
}

static inline real_t tf_max(real_t a, real_t b) {
#if defined(TF_REAL_FLOAT32)
    return fmaxf(a, b);
#elif defined(TF_REAL_FLOAT64)
    return fmax(a, b);
#endif
}

/* ========================================================================= */
/* ZERO PREDICATES                                                           */
/* ========================================================================= */

static inline bool tf_is_zero(real_t x) {
    return tf_abs(x) <= TF_TOL_ZERO;
}

static inline bool tf_is_zero_sq(real_t x_sq) {
    return x_sq >= (real_t)0 && x_sq <= TF_TOL_ZERO_SQ;
}

/* ========================================================================= */
/* APPROXIMATE COMPARISON                                                    */
/* ========================================================================= */

static inline bool tf_is_close_ext(real_t a, real_t b, real_t abs_tol, real_t rel_tol) {
    const real_t diff = tf_abs(a - b);

    if (diff <= abs_tol) {
        return true;
    }

    const real_t scale = tf_max(tf_abs(a), tf_abs(b));

    return diff <= rel_tol * scale;
}

static inline bool tf_is_close(real_t a, real_t b) {
    return tf_is_close_ext(a, b, TF_TOL_ABS, TF_TOL_REL);
}

/* ========================================================================= */
/* TOLERANCE-AWARE ORDERING                                                  */
/* ========================================================================= */

static inline bool tf_is_greater_tol(real_t a, real_t b) {
    return (a - b) > TF_TOL_ABS;
}

static inline bool tf_is_less_tol(real_t a, real_t b) {
    return (b - a) > TF_TOL_ABS;
}

/* ========================================================================= */
/* STRICT ORDERING                                                           */
/* ========================================================================= */

static inline bool tf_is_greater(real_t a, real_t b) {
    return a > b;
}

static inline bool tf_is_less(real_t a, real_t b) {
    return a < b;
}

#endif /* TABITIFORGE_NUMERIC_COMPARE_H */
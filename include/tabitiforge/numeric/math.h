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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_NUMERIC_MATH_H
#define TABITIFORGE_NUMERIC_MATH_H

#include <math.h>

#include "tabitiforge/numeric/constants.h"
#include "tabitiforge/numeric/types.h"

/* ========================================================================= */
/* TRIGONOMETRY                                                              */
/* ========================================================================= */

static inline real_t tf_sin(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return sinf(x);
#elif defined(TF_REAL_FLOAT64)
    return sin(x);
#endif
}

static inline real_t tf_cos(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return cosf(x);
#elif defined(TF_REAL_FLOAT64)
    return cos(x);
#endif
}

static inline real_t tf_tan(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return tanf(x);
#elif defined(TF_REAL_FLOAT64)
    return tan(x);
#endif
}

/*
 * C17 has no standard sincos() function.
 *
 * This wrapper therefore computes both values through the standard
 * scalar C math interface. A platform/backend implementation may
 * provide a specialized version later.
 */
static inline void tf_sincos(real_t x, real_t *sin_out, real_t *cos_out) {
    *sin_out = tf_sin(x);
    *cos_out = tf_cos(x);
}

static inline real_t tf_asin(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return asinf(x);
#elif defined(TF_REAL_FLOAT64)
    return asin(x);
#endif
}

static inline real_t tf_acos(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return acosf(x);
#elif defined(TF_REAL_FLOAT64)
    return acos(x);
#endif
}

static inline real_t tf_atan(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return atanf(x);
#elif defined(TF_REAL_FLOAT64)
    return atan(x);
#endif
}

static inline real_t tf_atan2(real_t y, real_t x) {
#if defined(TF_REAL_FLOAT32)
    return atan2f(y, x);
#elif defined(TF_REAL_FLOAT64)
    return atan2(y, x);
#endif
}

/* ========================================================================= */
/* ROOTS / POWERS / EXPONENTIALS                                             */
/* ========================================================================= */

static inline real_t tf_sqrt(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return sqrtf(x);
#elif defined(TF_REAL_FLOAT64)
    return sqrt(x);
#endif
}

static inline real_t tf_inv_sqrt(real_t x) {
    return (real_t)1 / tf_sqrt(x);
}

static inline real_t tf_cbrt(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return cbrtf(x);
#elif defined(TF_REAL_FLOAT64)
    return cbrt(x);
#endif
}

static inline real_t tf_pow(real_t x, real_t y) {
#if defined(TF_REAL_FLOAT32)
    return powf(x, y);
#elif defined(TF_REAL_FLOAT64)
    return pow(x, y);
#endif
}

static inline real_t tf_exp(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return expf(x);
#elif defined(TF_REAL_FLOAT64)
    return exp(x);
#endif
}

static inline real_t tf_log(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return logf(x);
#elif defined(TF_REAL_FLOAT64)
    return log(x);
#endif
}

static inline real_t tf_log2(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return log2f(x);
#elif defined(TF_REAL_FLOAT64)
    return log2(x);
#endif
}

static inline real_t tf_log10(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return log10f(x);
#elif defined(TF_REAL_FLOAT64)
    return log10(x);
#endif
}

/* ========================================================================= */
/* ABS / SIGN / ROUNDING / REMAINDER                                         */
/* ========================================================================= */

static inline real_t tf_abs(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return fabsf(x);
#elif defined(TF_REAL_FLOAT64)
    return fabs(x);
#endif
}

static inline int tf_sign(real_t x) {
    if (x > (real_t)0) {
        return 1;
    }

    if (x < (real_t)0) {
        return -1;
    }

    return 0;
}

static inline real_t tf_copysign(real_t x, real_t y) {
#if defined(TF_REAL_FLOAT32)
    return copysignf(x, y);
#elif defined(TF_REAL_FLOAT64)
    return copysign(x, y);
#endif
}

static inline real_t tf_floor(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return floorf(x);
#elif defined(TF_REAL_FLOAT64)
    return floor(x);
#endif
}

static inline real_t tf_ceil(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return ceilf(x);
#elif defined(TF_REAL_FLOAT64)
    return ceil(x);
#endif
}

static inline real_t tf_round(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return roundf(x);
#elif defined(TF_REAL_FLOAT64)
    return round(x);
#endif
}

static inline real_t tf_trunc(real_t x) {
#if defined(TF_REAL_FLOAT32)
    return truncf(x);
#elif defined(TF_REAL_FLOAT64)
    return trunc(x);
#endif
}

static inline real_t tf_fmod(real_t x, real_t y) {
#if defined(TF_REAL_FLOAT32)
    return fmodf(x, y);
#elif defined(TF_REAL_FLOAT64)
    return fmod(x, y);
#endif
}

/*
 * Alias for tf_fmod().
 */
static inline real_t tf_mod(real_t x, real_t y) {
    return tf_fmod(x, y);
}

/* ========================================================================= */
/* MIN / MAX / CLAMP                                                         */
/* ========================================================================= */

static inline real_t tf_min(real_t a, real_t b) {
#if defined(TF_REAL_FLOAT32)
    return fminf(a, b);
#elif defined(TF_REAL_FLOAT64)
    return fmin(a, b);
#endif
}

static inline real_t tf_max(real_t a, real_t b) {
#if defined(TF_REAL_FLOAT32)
    return fmaxf(a, b);
#elif defined(TF_REAL_FLOAT64)
    return fmax(a, b);
#endif
}

static inline real_t tf_clamp(real_t x, real_t min_value, real_t max_value) {
    return tf_min(tf_max(x, min_value), max_value);
}

static inline real_t tf_saturate(real_t x) {
    return tf_clamp(x, (real_t)0, (real_t)1);
}

/* ========================================================================= */
/* ANGLE CONVERSION                                                           */
/* ========================================================================= */

static inline real_t tf_rad_to_deg(real_t radians) {
    return radians * TF_DEG_PER_RAD;
}

static inline real_t tf_deg_to_rad(real_t degrees) {
    return degrees * TF_RAD_PER_DEG;
}

/* ========================================================================= */
/* INTERPOLATION                                                             */
/* ========================================================================= */

static inline real_t tf_lerp(real_t a, real_t b, real_t t) {
    return a + (b - a) * t;
}

static inline real_t tf_smoothstep(real_t edge0, real_t edge1, real_t x) {
    const real_t width = edge1 - edge0;

    if (width == (real_t)0) {
        return x < edge0 ? (real_t)0 : (real_t)1;
    }

    real_t t = (x - edge0) / width;

    t = tf_clamp(t, (real_t)0, (real_t)1);

    return t * t * ((real_t)3 - (real_t)2 * t);
}

static inline real_t tf_smootherstep(real_t edge0, real_t edge1, real_t x) {
    const real_t width = edge1 - edge0;

    if (width == (real_t)0) {
        return x < edge0 ? (real_t)0 : (real_t)1;
    }

    real_t t = (x - edge0) / width;

    t = tf_clamp(t, (real_t)0, (real_t)1);

    return t * t * t * (t * (t * (real_t)6 - (real_t)15) + (real_t)10);
}

/* ========================================================================= */
/* PERIODIC FUNCTIONS                                                        */
/* ========================================================================= */

/*
 * Wrap x into [0, length).
 *
 * Unlike fmod(), this also behaves correctly for negative x.
 */
static inline real_t tf_repeat(real_t x, real_t length) {
    if (length <= (real_t)0) {
        return (real_t)0;
    }

    real_t result = tf_fmod(x, length);

    if (result < (real_t)0) {
        result += length;
    }

    return result;
}

/*
 * Ping-pong x over [0, length].
 *
 * Example for length = 1:
 *
 *   0 -> 1 -> 0 -> 1 ...
 */
static inline real_t tf_pingpong(real_t x, real_t length) {
    if (length <= (real_t)0) {
        return (real_t)0;
    }

    const real_t period = length * (real_t)2;
    const real_t t = tf_repeat(x, period);

    return length - tf_abs(t - length);
}

#endif /* TABITIFORGE_NUMERIC_MATH_H */
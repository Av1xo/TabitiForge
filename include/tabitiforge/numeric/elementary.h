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

#ifndef TABITIFORGE_NUMERIC_ELEMENTARY_H
#define TABITIFORGE_NUMERIC_ELEMENTARY_H

#include "tabitiforge/numeric/types.h"

/* ========================================================================= */
/* ALGEBRAIC PRIMITIVES                                                      */
/* ========================================================================= */
static inline real_t tf_square(real_t x) {
    return x * x;
}

static inline real_t tf_cube(real_t x) {
    return x * x * x;
}

static inline real_t tf_rcp(real_t x) {
    return (real_t)1.0 / x;
}

/* ========================================================================= */
/* EUCLIDEAN NORMS                                                           */
/* ========================================================================= */
real_t tf_hypot2(real_t x, real_t y);
real_t tf_hypot3(real_t x, real_t y, real_t z);
real_t tf_hypot4(real_t x, real_t y, real_t z, real_t w);

/* ========================================================================= */
/* SAFE / SPECIAL FUNCTIONS                                                 */
/* ========================================================================= */
real_t tf_sinc(real_t x);
real_t tf_clamped_acos(real_t x);
real_t tf_clamped_asin(real_t x);
real_t tf_wrap_radians(real_t rad);
real_t tf_wrap_radians_signed(real_t rad);

/* ========================================================================= */
/* POWERS, POLYNOMIALS & SOLVERS                                             */
/* ========================================================================= */
real_t tf_powi(real_t base, tf_i32 exp);

real_t tf_poly_eval(const real_t *coeffs, tf_size count, real_t x);
real_t tf_poly_eval_ascending(const real_t *coeffs, tf_size count, real_t x);

tf_u64 tf_factorial(tf_u32 n);
real_t tf_factorial_real(tf_u32 n);

tf_u64 tf_binomial(tf_u32 n, tf_u32 k);
real_t tf_binomial_real(tf_u32 n, tf_u32 k);

real_t tf_poly_bernstein(tf_u32 i, tf_u32 n, real_t t);

/* Orthogonal Polynomials */
real_t tf_poly_legendre(tf_u32 n, real_t x);
real_t tf_poly_chebyshev_t(tf_u32 n, real_t x);
real_t tf_poly_chebyshev_u(tf_u32 n, real_t x);
real_t tf_poly_hermite(tf_u32 n, real_t x);
real_t tf_poly_laguerre(tf_u32 n, real_t x);

tf_i32 tf_solve_quadratic(real_t a, real_t b, real_t c, real_t out_roots[2]);
tf_i32 tf_solve_trinomial_pow2n(real_t a, real_t b, real_t c, tf_u32 n, real_t out_roots[4]);

#endif
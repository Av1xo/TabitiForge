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

#include "tabitiforge/numeric/elementary.h"
#include "tabitiforge/numeric/compare.h"
#include "tabitiforge/numeric/limits.h"
#include "tabitiforge/numeric/math.h"

// optimized hypot: max * sqrt(1 + (min/max)^2)
real_t tf_hypot2(real_t x, real_t y) {
#if defined(TF_REAL_FLOAT32)
    return hypotf(x, y);
#elif defined(TF_REAL_FLOAT64)
    return hypot(x, y);
#endif
}

real_t tf_hypot3(real_t x, real_t y, real_t z) {
    const real_t ax = tf_abs(x), ay = tf_abs(y), az = tf_abs(z);
    const real_t scale = tf_max(tf_max(ax, ay), az);

    if (scale == (real_t)0.)
        return (real_t)0.;

    const real_t ix = ax / scale;
    const real_t iy = ay / scale;
    const real_t iz = az / scale;

    real_t sum = tf_square(iz);
    sum = tf_fma(iy, iy, sum);
    sum = tf_fma(ix, ix, sum);

    return scale * tf_sqrt(sum);
}

real_t tf_hypot4(real_t x, real_t y, real_t z, real_t w) {
    const real_t ax = tf_abs(x), ay = tf_abs(y), az = tf_abs(z), aw = tf_abs(w);
    const real_t scale = tf_max(tf_max(ax, ay), tf_max(az, aw));

    if (scale == (real_t)0.)
        return (real_t)0.;

    const real_t ix = ax / scale;
    const real_t iy = ay / scale;
    const real_t iz = az / scale;
    const real_t iw = aw / scale;

    real_t sum = tf_square(iw);
    sum = tf_fma(iz, iz, sum);
    sum = tf_fma(iy, iy, sum);
    sum = tf_fma(ix, ix, sum);

    return scale * tf_sqrt(sum);
}

real_t tf_sinc(real_t x) {
#if defined(TF_REAL_FLOAT32)
    static const real_t sinc_tol = (real_t)1e-3f;
#else
    static const real_t sinc_tol = (real_t)1e-4;
#endif

    const real_t ax = tf_abs(x);

    if (ax <= sinc_tol) {
        const real_t x2 = tf_square(x);

#if defined(TF_REAL_FLOAT32)
        // float: 1 - x ^ 2 / 6
        return tf_fma(x2, (real_t)(-1.0 / 6.0), (real_t)1.0);
#else
        // double: 1 - x^2 / 6 + x^4 / 120  =>  1 + x^2 * (-1/6 + x^2 * (1/120))
        const real_t poly = tf_fma(x2, (real_t)(1.0 / 120.0), (real_t)(-1.0 / 6.0));

        return tf_fma(x2, poly, (real_t)1.0);
#endif
    }

    return tf_sin(x) / x;
}

real_t tf_clamped_acos(real_t x) {
    return tf_acos(tf_clamp(x, (real_t)-1., (real_t)1.));
}

real_t tf_clamped_asin(real_t x) {
    return tf_asin(tf_clamp(x, (real_t)-1., (real_t)1.));
}

real_t tf_wrap_radians(real_t rad) {
    return tf_repeat(rad, TF_TAU);
}

real_t tf_wrap_radians_signed(real_t rad) {
    return tf_repeat(rad + TF_PI, TF_TAU) - TF_PI;
}

real_t tf_powi(real_t base, tf_i32 exp) {
    if (exp == 0)
        return (real_t)1.;
    bool negative = exp < 0;

    // Avoid -INT_MIN overflow
    tf_u32 power = negative ? (tf_u32)(-(exp + 1)) + 1u : (tf_u32)exp;

    real_t result = (real_t)1.;

    while (power != 0u) {
        if (power & 1u)
            result *= base;

        power >>= 1u;

        if (power != 0u)
            base *= base;
    }

    return negative ? ((real_t)1 / result) : result;
}

real_t tf_poly_eval(const real_t *coeffs, tf_size count, real_t x) {
    if (count == 0 || coeffs == NULL)
        return (real_t)0.;
    real_t result = coeffs[0];

    for (tf_size i = 1; i < count; ++i)
        result = tf_fma(result, x, coeffs[i]);

    return result;
}

real_t tf_poly_eval_ascending(const real_t *coeffs, tf_size count, real_t x) {
    if (count == 0 || coeffs == NULL)
        return (real_t)0.;
    real_t result = coeffs[count - 1];

    for (tf_size i = count - 1; i > 0; --i)
        result = tf_fma(result, x, coeffs[i - 1]);

    return result;
}

tf_u64 tf_factorial(tf_u32 n) {
    static const tf_u64 TF_FACTORIAL_TABLE[21] = {0x1ULL,
                                                  0x1ULL,
                                                  0x2ULL,
                                                  0x6ULL,
                                                  0x18ULL,
                                                  0x78ULL,
                                                  0x2d0ULL,
                                                  0x13b0ULL,
                                                  0x9d80ULL,
                                                  0x58980ULL,
                                                  0x375f00ULL,
                                                  0x2611500ULL,
                                                  0x1c8cfc00ULL,
                                                  0x17328cc00ULL,
                                                  0x144c3b2800ULL,
                                                  0x13077775800ULL,
                                                  0x130777758000ULL,
                                                  0x1437eeecd8000ULL,
                                                  0x16beecca730000ULL,
                                                  0x1b02b9306890000ULL,
                                                  0x21c3677c82b40000ULL};

    if (n > 20u) {
        return TF_U64_MAX;
    }

    return TF_FACTORIAL_TABLE[n];
}

real_t tf_factorial_real(tf_u32 n) {
#if defined(TF_REAL_FLOAT32)
    static const tf_u32 type_limit = 34u;
    static const real_t TF_FACTORIAL_TABLE[35] = {
        0x1.0000000000000p+0f,   0x1.0000000000000p+0f,   0x1.0000000000000p+1f,
        0x1.8000000000000p+2f,   0x1.8000000000000p+4f,   0x1.e000000000000p+6f,
        0x1.6800000000000p+9f,   0x1.3b00000000000p+12f,  0x1.3b00000000000p+15f,
        0x1.6260000000000p+18f,  0x1.baf8000000000p+21f,  0x1.308a800000000p+25f,
        0x1.c8cfc00000000p+28f,  0x1.7328cc0000000p+32f,  0x1.44c3b20000000p+36f,
        0x1.3077780000000p+40f,  0x1.3077780000000p+44f,  0x1.437eee0000000p+48f,
        0x1.6beecc0000000p+52f,  0x1.b02b940000000p+56f,  0x1.0e1b3c0000000p+61f,
        0x1.6283be0000000p+65f,  0x1.e775260000000p+69f,  0x1.5e5c340000000p+74f,
        0x1.06c5260000000p+79f,  0x1.9a940c0000000p+83f,  0x1.4d984a0000000p+88f,
        0x1.19787e0000000p+93f,  0x1.ec92de0000000p+97f,  0x1.be65180000000p+102f,
        0x1.a27ec60000000p+107f, 0x1.956ad00000000p+112f, 0x1.956ad00000000p+117f,
        0x1.a216280000000p+122f, 0x1.bc378a0000000p+127f};
#else
    static const tf_u32 type_limit = 170u;
    static const real_t TF_FACTORIAL_TABLE[171] = {
        0x1.0000000000000p+0,    0x1.0000000000000p+0,    0x1.0000000000000p+1,
        0x1.8000000000000p+2,    0x1.8000000000000p+4,    0x1.e000000000000p+6,
        0x1.6800000000000p+9,    0x1.3b00000000000p+12,   0x1.3b00000000000p+15,
        0x1.6260000000000p+18,   0x1.baf8000000000p+21,   0x1.308a800000000p+25,
        0x1.c8cfc00000000p+28,   0x1.7328cc0000000p+32,   0x1.44c3b28000000p+36,
        0x1.3077775800000p+40,   0x1.3077775800000p+44,   0x1.437eeecd80000p+48,
        0x1.6beecca730000p+52,   0x1.b02b930689000p+56,   0x1.0e1b3be415a00p+61,
        0x1.6283be9b5c620p+65,   0x1.e77526159f06cp+69,   0x1.5e5c335f8a4cep+74,
        0x1.06c52687a7b9ap+79,   0x1.9a940c33f6121p+83,   0x1.4d9849ea37eebp+88,
        0x1.19787e5d9f316p+93,   0x1.ec92dd23d6967p+97,   0x1.be6518687a785p+102,
        0x1.a27ec6e1f2d0dp+107,  0x1.956ad0aae33a4p+112,  0x1.956ad0aae33a4p+117,
        0x1.a21627303a541p+122,  0x1.bc3789a33df96p+127,  0x1.e5dcbe8a8bc8cp+132,
        0x1.114c2b2deea0fp+138,  0x1.3c0011ed1bea1p+143,  0x1.774015499125fp+148,
        0x1.c95619f1a8e64p+153,  0x1.1dd5d037098fep+159,  0x1.6e39f2c684406p+164,
        0x1.e0ac0ea48d948p+169,  0x1.42f399d68f1fcp+175,  0x1.bc0ef38704cbbp+180,
        0x1.383a833aef5f3p+186,  0x1.c0d41ca4b818ep+191,  0x1.499bc508f7324p+197,
        0x1.ee69a78d72cb6p+202,  0x1.7a88e4484be3bp+208,  0x1.27baf2587b49ep+214,
        0x1.d751f23d047dcp+219,  0x1.7ef294d193a63p+225,  0x1.3d20e33d8e45ap+231,
        0x1.0b93bfbbf00acp+237,  0x1.cbe5f18b04928p+242,  0x1.92693359a4003p+248,
        0x1.6665b1bbd6102p+254,  0x1.44cc291239feap+260,  0x1.2b6c35dccd76cp+266,
        0x1.18b5727f009f5p+272,  0x1.0b8cf1210c97ep+278,  0x1.0330899804332p+284,
        0x1.fe478ee34844ap+289,  0x1.fe478ee34844ap+295,  0x1.0320568f6ab2ep+302,
        0x1.0b395943e6087p+308,  0x1.17c0097314d0dp+314,  0x1.293c0a0a461dep+320,
        0x1.4074bad313983p+326,  0x1.5e7fac56dd6e8p+332,  0x1.84d5a3305da69p+338,
        0x1.b5705796695b6p+344,  0x1.f2f423e7902c4p+350,  0x1.207524c1df599p+357,
        0x1.5209471331bd0p+363,  0x1.916b0466cb107p+369,  0x1.e2f4c14bac4fcp+375,
        0x1.264d25ca1d009p+382,  0x1.6b473aa57bcccp+388,  0x1.c619094edabffp+394,
        0x1.1f5bd7e3e66d7p+401,  0x1.702dac9bff3c4p+407,  0x1.dd7b3bda4f022p+413,
        0x1.3958df4743d96p+420,  0x1.a02a088aa61cbp+426,  0x1.179c3dbd279b5p+433,
        0x1.7c1863ed21d72p+439,  0x1.0550c4b30743ep+446,  0x1.6b645188f61a6p+452,
        0x1.ff0512a89a152p+458,  0x1.6b4d9b43dd8b0p+465,  0x1.051fc798c73bfp+472,
        0x1.7b722e0a01831p+478,  0x1.16a7d9cf591c4p+485,  0x1.9da1274fc845fp+491,
        0x1.3638dd7bd6347p+498,  0x1.d62e2fafb0a78p+504,  0x1.67fb5c8283404p+511,
        0x1.166c698cf183bp+518,  0x1.b30964ec395dcp+524,  0x1.574569a265440p+531,
        0x1.118b502d68b23p+538,  0x1.b83c3509147ecp+544,  0x1.65b0eb1760a70p+551,
        0x1.256b20d92d490p+558,  0x1.e5f96e67b300ep+564,  0x1.963e824aafa2cp+571,
        0x1.56c4bdef04315p+578,  0x1.23e389bd89920p+585,  0x1.f5af14bdc472fp+591,
        0x1.b30dd3fc905bap+598,  0x1.7cac197cfe503p+605,  0x1.500fee805882dp+612,
        0x1.2b4e306a4ed48p+619,  0x1.0ce83f7f82d2fp+626,  0x1.e764f3171d1e4p+632,
        0x1.bd824633209dbp+639,  0x1.9ab418b722116p+646,  0x1.7dd36efa41ac2p+653,
        0x1.65f6380a9d916p+660,  0x1.5262c0fa08f37p+667,  0x1.42861fee50880p+674,
        0x1.35ece2af0162bp+681,  0x1.2c3d7b998957ap+688,  0x1.25340ab3f01f9p+695,
        0x1.209f3a89205f1p+702,  0x1.1e5dfc140e1e5p+709,  0x1.1e5dfc140e1e5p+716,
        0x1.209ab80c363a9p+723,  0x1.251d22ec67138p+730,  0x1.2bfbd1bdf17dfp+737,
        0x1.355bb04be109ep+744,  0x1.4171452ed7d44p+751,  0x1.5082946d09f23p+758,
        0x1.62e9b88b007d7p+765,  0x1.79185413b0855p+772,  0x1.939c09fd12eebp+779,
        0x1.b3243ac4d8695p+786,  0x1.d88957d1c3026p+793,  0x1.026b1c06b6a55p+801,
        0x1.1ca9fcdf65321p+808,  0x1.3bcc9487d4439p+815,  0x1.60ce8defbf238p+822,
        0x1.8ce85fadb707ep+829,  0x1.c19f3c62c956fp+836,  0x1.006cd07056d39p+844,
        0x1.267cf76103b70p+851,  0x1.54807e082c4b9p+858,  0x1.8c5d92b583900p+865,
        0x1.d07da7ecb62ccp+872,  0x1.11fa1e0c9f746p+880,  0x1.455903aefd5a3p+887,
        0x1.84e466672ad5dp+894,  0x1.d3e2cb341f894p+901,  0x1.1b4a51088f182p+909,
        0x1.594292c26e656p+916,  0x1.a77ba8027b686p+923,  0x1.055e51b1882a7p+931,
        0x1.44ab297a8724bp+938,  0x1.95d5f3d928edep+945,  0x1.fe771cb7257b3p+952,
        0x1.4307602be5b7fp+960,  0x1.9b5b6477e6884p+967,  0x1.07868c5ccfaf4p+975,
        0x1.53b370efa3b7fp+982,  0x1.b88cb676c8529p+989,  0x1.1f63cb077cadep+997,
        0x1.7932fa79d3a43p+1004, 0x1.f2054eb4d96ecp+1011, 0x1.4ab7864418639p+1019};
#endif
    if (n > type_limit)
        return TF_REAL_INFINITY;

    return TF_FACTORIAL_TABLE[n];
}

tf_u64 tf_binomial(tf_u32 n, tf_u32 k) {
    if (k > n)
        return TF_U64_MIN;
    if (k == TF_U32_MIN || k == n)
        return 1ULL;

    if (n <= 20u)
        return tf_factorial(n) / (tf_factorial(k) * tf_factorial(n - k));

    if (k > n / 2u)
        k = n - k;
    tf_u64 res = 1ULL;
    for (tf_u32 i = 1u; i <= k; ++i) {
        tf_u64 term = (tf_u64)(n - k + i);
        tf_u64 divisor = (tf_u64)i;
        tf_u64 common_div = gcd_u64(res, divisor);

        res = (res / common_div) * (term / (divisor / common_div));
    }
    return res;
}

real_t tf_binomial_real(tf_u32 n, tf_u32 k) {
    if (k > n)
        return (real_t)0.;
    if (k == TF_U32_MIN || k == n)
        return (real_t)1.;

#if defined(TF_REAL_FLOAT32)
    static const tf_u32 max_factorial_n = 34u;
#else
    static const tf_u32 max_factorial_n = 170u;
#endif

    if (n <= max_factorial_n)
        return tf_factorial_real(n) / (tf_factorial_real(k) * tf_factorial_real(n - k));

    if (k > n / 2u)
        k = n - k;

    real_t res = (real_t)1;
    for (tf_u32 i = 1u; i <= k; ++i) {
        res *= (real_t)(n - k + i) / (real_t)i;
    }

    return res;
}

real_t tf_poly_bernstein(tf_u32 i, tf_u32 n, real_t t) {
    if (i > n)
        return (real_t)0.;

    if (t <= (real_t)0.)
        return (i == TF_U32_MIN) ? (real_t)1. : (real_t)0.;
    if (t >= (real_t)1.)
        return (i == n) ? (real_t)1. : (real_t)0.;

    /* B_{i,n}(x) = C(n, i) * x^i * (1 - x)^(n - i) */
    const real_t comb = tf_binomial_real(n, i);
    const real_t term_t = tf_powi(t, (tf_i32)i);
    const real_t term_1t = tf_powi((real_t)1. - t, (tf_i32)(n - i));

    return comb * term_t * term_1t;
}

real_t tf_poly_legendre(tf_u32 n, real_t x) {
    if (n == TF_U32_MIN)
        return (real_t)1.;
    if (n == 1u)
        return x;

    real_t p_prev2 = (real_t)1.;
    real_t p_prev1 = x;
    real_t p_curr = x;

    for (tf_u32 i = 2u; i <= n; ++i) {
        const real_t fi = (real_t)i;
        const real_t two_i_minus_1 = (real_t)2. * fi - (real_t)1.;
        const real_t one_minus_i = (real_t)1. - fi;

        /*
         * (2i - 1) * x * P_{i-1} + (1 - i) * P_{i-2}
         * fma(a * b, c, d)
         */
        const real_t num = tf_fma(two_i_minus_1 * x, p_prev1, one_minus_i * p_prev2);
        p_curr = num / fi;

        p_prev2 = p_prev1;
        p_prev1 = p_curr;
    }

    return p_curr;
}

real_t tf_poly_chebyshev_t(tf_u32 n, real_t x) {
    if (n == TF_U32_MIN)
        return (real_t)1.;
    if (n == 1u)
        return x;

    real_t t_prev2 = (real_t)1.;
    real_t t_prev1 = x;
    real_t t_curr = x;

    const real_t two_x = (real_t)2. * x;

    for (tf_u32 i = 2u; i <= n; ++i) {
        /* T_i(x) = 2x * T_{i-1}(x) - T_{i-2}(x) */
        t_curr = tf_fma(two_x, t_prev1, -t_prev2);

        t_prev2 = t_prev1;
        t_prev1 = t_curr;
    }

    return t_curr;
}

real_t tf_poly_chebyshev_u(tf_u32 n, real_t x) {
    if (n == TF_U32_MIN)
        return (real_t)1.;

    real_t u_prev2 = (real_t)1.;
    real_t u_prev1 = (real_t)2. * x;

    if (n == 1u)
        return u_prev1;

    real_t u_curr = u_prev1;
    const real_t two_x = (real_t)2. * x;

    for (tf_u32 i = 2u; i <= n; ++i) {
        /* U_i(x) = 2x * U_{i-1}(x) - U_{i-2}(x) */
        u_curr = tf_fma(two_x, u_prev1, -u_prev2);

        u_prev2 = u_prev1;
        u_prev1 = u_curr;
    }

    return u_curr;
}

real_t tf_poly_hermite(tf_u32 n, real_t x) {
    if (n == TF_U32_MIN)
        return (real_t)1.;

    real_t h_prev2 = (real_t)1.;
    real_t h_prev1 = (real_t)2. * x;

    if (n == 1u)
        return h_prev1;

    real_t h_curr = h_prev1;
    const real_t two_x = (real_t)2. * x;

    for (tf_u32 i = 2u; i <= n; ++i) {
        /*
         * H_i(x) = 2x * H_{i-1}(x) - 2(i - 1) * H_{i-2}(x)
         * fma(2x, H_{i-1}, -2(i - 1) * H_{i-2})
         */
        const real_t two_i_minus_2 = (real_t)(2u * (i - 1u));
        h_curr = tf_fma(two_x, h_prev1, -two_i_minus_2 * h_prev2);

        h_prev2 = h_prev1;
        h_prev1 = h_curr;
    }

    return h_curr;
}

real_t tf_poly_laguerre(tf_u32 n, real_t x) {
    if (n == TF_U32_MIN)
        return (real_t)1.;

    real_t l_prev2 = (real_t)1.;     /* L_0(x) */
    real_t l_prev1 = (real_t)1. - x; /* L_1(x) */

    if (n == 1u)
        return l_prev1;

    real_t l_curr = l_prev1;

    for (tf_u32 i = 2u; i <= n; ++i) {
        const real_t fi = (real_t)i;
        const real_t term1 = (real_t)2. * fi - (real_t)1. - x; /* (2i - 1 - x) */
        const real_t one_minus_i = (real_t)1. - fi;            /* -(i - 1) */

        /*
         * (2i - 1 - x) * L_{i-1} + (1 - i) * L_{i-2}
         * fma(a, b, c) -> a * b + c
         */
        const real_t num = tf_fma(term1, l_prev1, one_minus_i * l_prev2);
        l_curr = num / fi;

        l_prev2 = l_prev1;
        l_prev1 = l_curr;
    }

    return l_curr;
}

tf_i32 tf_solve_quadratic(real_t a, real_t b, real_t c, real_t out_roots[2]) {
    if (out_roots == NULL)
        return 0;

    /* b * x + c = 0 */
    if (a == (real_t)0.) {
        if (b == (real_t)0.)
            return 0;
        out_roots[0] = -c / b;
        return 1;
    }

    /* D = b^2 - 4ac */
    const real_t discriminant = tf_fma(b, b, (real_t)-4. * a * c);

    if (discriminant < (real_t)0.)
        return 0;

    if (discriminant == (real_t)0.) {
        out_roots[0] = (real_t)-0.5 * b / a;
        return 1;
    }

    const real_t sqrt_d = tf_sqrt(discriminant);

    /*
     * q = -0.5 * (b + sign(b) * sqrt(D))
     */
    const real_t sign_b = tf_sign_nz(b);
    const real_t q = (real_t)-0.5 * tf_fma(sign_b, sqrt_d, b);

    out_roots[0] = q / a;
    out_roots[1] = c / q;

    return 2;
}

tf_i32 tf_solve_trinomial_pow2n(real_t a, real_t b, real_t c, tf_u32 n, real_t out_roots[4]) {
    if (n == TF_U32_MIN || out_roots == NULL)
        return 0;

    /* a * y^2 + b * y + c = 0 */
    real_t y_roots[2];
    const tf_i32 y_count = tf_solve_quadratic(a, b, c, y_roots);

    if (y_count == 0)
        return 0;

    tf_i32 x_count = 0;
    const real_t inv_n = (real_t)1. / (real_t)n;
    const bool is_even = (n % 2u == 0u);

    /* x from x^n = y */
    for (tf_i32 i = 0; i < y_count; ++i) {
        const real_t y = y_roots[i];

        if (is_even) {
            /* y >= 0 */
            if (y > (real_t)0.) {
                const real_t x_pos = tf_pow(y, inv_n);
                out_roots[x_count++] = x_pos;
                out_roots[x_count++] = -x_pos;
            } else if (y == (real_t)0.) {
                out_roots[x_count++] = (real_t)0.;
            }
        } else {
            if (y >= (real_t)0.) {
                out_roots[x_count++] = tf_powi(y, inv_n);
            } else {
                out_roots[x_count++] = -tf_powi(-y, inv_n);
            }
        }
    }

    return x_count;
}
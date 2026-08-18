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
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_MAT3x3_H
#define TABITIFORGE_MAT3x3_H

#ifdef __cplusplus
extern "C" {
#endif

#include "math_types.h"
#include "vec3.h"

#include <math.h>
#include <stdbool.h>

typedef struct {
    union {
        double flat[9];
        double m[3][3];
        Vec3 row[3];
    };
} Mat3x3;

#define mat3x3(...) ((Mat3x3){.flat = {__VA_ARGS__}})

#ifndef MAT3x3_ZERO
#define MAT3x3_ZERO ((Mat3x3){0})
#endif

#ifndef MAT3x3_IDENTITY
#define MAT3x3_IDENTITY ((Mat3x3){.flat = {1., 0., 0., 0., 1., 0., 0., 0., 1.}})
#endif

#ifndef MAT3x3_NAN
#define MAT3x3_NAN ((Mat3x3){.flat = {NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN}})
#endif

#if defined(__GNUC__) || defined(__clang__)
#define TF_NODISCARD __attribute__((warn_unused_result))
#else
#define TF_NODISCARD
#endif

Mat3x3 mat3x3_transpose(Mat3x3 mat);
void mat3x3_itranspose(Mat3x3 *mat);

Vec3 mat3x3_vecmul(Vec3 v, Mat3x3 mat);
void mat3x3_ivecmul(Vec3 *v, Mat3x3 mat);

Mat3x3 mat3x3_mul(Mat3x3 a, Mat3x3 b);
void mat3x3_imul(Mat3x3 *a, Mat3x3 b);

Mat3x3 mat3x3_add(Mat3x3 a, Mat3x3 b);
void mat3x3_iadd(Mat3x3 *a, Mat3x3 b);

Mat3x3 mat3x3_sub(Mat3x3 a, Mat3x3 b);
void mat3x3_isub(Mat3x3 *a, Mat3x3 b);

Mat3x3 mat3x3_neg(Mat3x3 mat);
void mat3x3_ineg(Mat3x3 *mat);

Mat3x3 mat3x3_scale(Mat3x3 mat, double s);
void mat3x3_iscale(Mat3x3 *mat, double s);

double mat3x3_det(Mat3x3 a);
Mat3x3 mat3x3_cofactor(Mat3x3 mat);

TF_NODISCARD bool mat3x3_inv(Mat3x3 mat, Mat3x3 *out_inv);

Mat3x3 mat3x3_outer(Vec3 a, Vec3 b);
Mat3x3 mat3x3_skew(Vec3 k);
Mat3x3 mat3x3_rotation(Vec3 k, double theta);

double mat3x3_trace(Mat3x3 mat);
double mat3x3_so3_angle_between(Mat3x3 a, Mat3x3 b);
double mat3x3_angle_between(Mat3x3 a, Mat3x3 b);

bool mat3x3_eq(Mat3x3 a, Mat3x3 b);
bool mat3x3_eps_eq(Mat3x3 a, Mat3x3 b, double eps);

#ifdef __cplusplus
}
#endif

#endif // TABITIFORGE_MAT3x3_H
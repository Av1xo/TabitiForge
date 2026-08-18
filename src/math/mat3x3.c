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

#include "tabitiforge/math/mat3x3.h"

Mat3x3 mat3x3_transpose(Mat3x3 mat) {
    return mat3x3(mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[0][1], mat.m[1][1], mat.m[2][1],
                  mat.m[0][2], mat.m[1][2], mat.m[2][2]);
}

void mat3x3_itranspose(Mat3x3 *mat) {
    double tmp;

    tmp = mat->m[0][1];
    mat->m[0][1] = mat->m[1][0];
    mat->m[1][0] = tmp;

    tmp = mat->m[0][2];
    mat->m[0][2] = mat->m[2][0];
    mat->m[2][0] = tmp;

    tmp = mat->m[1][2];
    mat->m[1][2] = mat->m[2][1];
    mat->m[2][1] = tmp;
}

Vec3 mat3x3_vecmul(Vec3 v, Mat3x3 mat) {
    return vec3(vec3_dot(mat.row[0], v), vec3_dot(mat.row[1], v), vec3_dot(mat.row[2], v));
}

void mat3x3_ivecmul(Vec3 *v, Mat3x3 mat) {
    *v = mat3x3_vecmul(*v, mat);
}

Mat3x3 mat3x3_mul(Mat3x3 a, Mat3x3 b) {
    return mat3x3(a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0],
                  a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1],
                  a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2],

                  a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0],
                  a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1],
                  a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2],

                  a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0],
                  a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1],
                  a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2]);
}

void mat3x3_imul(Mat3x3 *a, Mat3x3 b) {
    *a = mat3x3_mul(*a, b);
}

Mat3x3 mat3x3_add(Mat3x3 a, Mat3x3 b) {
    return (Mat3x3){.row = {
                        vec3_add(a.row[0], b.row[0]),
                        vec3_add(a.row[1], b.row[1]),
                        vec3_add(a.row[2], b.row[2]),
                    }};
}

void mat3x3_iadd(Mat3x3 *a, Mat3x3 b) {
    vec3_iadd(&a->row[0], b.row[0]);
    vec3_iadd(&a->row[1], b.row[1]);
    vec3_iadd(&a->row[2], b.row[2]);
}

Mat3x3 mat3x3_sub(Mat3x3 a, Mat3x3 b) {
    return (Mat3x3){.row = {
                        vec3_sub(a.row[0], b.row[0]),
                        vec3_sub(a.row[1], b.row[1]),
                        vec3_sub(a.row[2], b.row[2]),
                    }};
}

void mat3x3_isub(Mat3x3 *a, Mat3x3 b) {
    vec3_isub(&a->row[0], b.row[0]);
    vec3_isub(&a->row[1], b.row[1]);
    vec3_isub(&a->row[2], b.row[2]);
}

Mat3x3 mat3x3_neg(Mat3x3 mat) {
    return (Mat3x3){.row = {
                        vec3_neg(mat.row[0]),
                        vec3_neg(mat.row[1]),
                        vec3_neg(mat.row[2]),
                    }};
}

void mat3x3_ineg(Mat3x3 *mat) {
    vec3_ineg(&mat->row[0]);
    vec3_ineg(&mat->row[1]);
    vec3_ineg(&mat->row[2]);
}

Mat3x3 mat3x3_scale(Mat3x3 mat, double s) {
    return (Mat3x3){
        .row = {vec3_scale(mat.row[0], s), vec3_scale(mat.row[1], s), vec3_scale(mat.row[2], s)}};
}

void mat3x3_iscale(Mat3x3 *mat, double s) {
    vec3_iscale(&mat->row[0], s);
    vec3_iscale(&mat->row[1], s);
    vec3_iscale(&mat->row[2], s);
}

double mat3x3_det(Mat3x3 a) {
    return ((a.m[0][0] * a.m[1][1] * a.m[2][2] + a.m[0][1] * a.m[1][2] * a.m[2][0] +
             a.m[0][2] * a.m[1][0] * a.m[2][1]) -
            (a.m[2][0] * a.m[1][1] * a.m[0][2] + a.m[2][1] * a.m[1][2] * a.m[0][0] +
             a.m[2][2] * a.m[1][0] * a.m[0][1]));
}

Mat3x3 mat3x3_cofactor(Mat3x3 mat) {
    return mat3x3(+(mat.m[1][1] * mat.m[2][2] - mat.m[2][1] * mat.m[1][2]),
                  -(mat.m[1][0] * mat.m[2][2] - mat.m[2][0] * mat.m[1][2]),
                  +(mat.m[1][0] * mat.m[2][1] - mat.m[2][0] * mat.m[1][1]),

                  -(mat.m[0][1] * mat.m[2][2] - mat.m[2][1] * mat.m[0][2]),
                  +(mat.m[0][0] * mat.m[2][2] - mat.m[2][0] * mat.m[0][2]),
                  -(mat.m[0][0] * mat.m[2][1] - mat.m[2][0] * mat.m[0][1]),

                  +(mat.m[0][1] * mat.m[1][2] - mat.m[1][1] * mat.m[0][2]),
                  -(mat.m[0][0] * mat.m[1][2] - mat.m[1][0] * mat.m[0][2]),
                  +(mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1]));
}

bool mat3x3_inv(Mat3x3 mat, Mat3x3 *out_inv) {
    double det = mat3x3_det(mat);
    if (fabs(det) < TF_EPS_DET) {
        return false;
    }

    Mat3x3 result = mat3x3_cofactor(mat);
    double inv_det = 1.0 / det;
    mat3x3_itranspose(&result);
    mat3x3_iscale(&result, inv_det);

    if (out_inv)
        *out_inv = result;
    return true;
}

Mat3x3 mat3x3_outer(Vec3 a, Vec3 b) {
    return (Mat3x3){.row = {
                        vec3_scale(b, a.x),
                        vec3_scale(b, a.y),
                        vec3_scale(b, a.z),
                    }};
}

Mat3x3 mat3x3_skew(Vec3 k) {
    return (Mat3x3){.row = {vec3(0., -k.z, k.y), vec3(k.z, 0., -k.x), vec3(-k.y, k.x, 0.)}};
}

Mat3x3 mat3x3_rotation(Vec3 k, double theta) {
    double len_sq = vec3_len2(k);
    if (len_sq < TF_EPS_LENGTH_SQ)
        return MAT3x3_IDENTITY;

    k = vec3_norm(k);
    Mat3x3 rotation = mat3x3_scale(MAT3x3_IDENTITY, cos(theta));
    mat3x3_iadd(&rotation, mat3x3_scale(mat3x3_outer(k, k), 1.0 - cos(theta)));
    mat3x3_iadd(&rotation, mat3x3_scale(mat3x3_skew(k), sin(theta)));
    return rotation;
}

double mat3x3_trace(Mat3x3 mat) {
    return mat.m[0][0] + mat.m[1][1] + mat.m[2][2];
}

double mat3x3_so3_angle_between(Mat3x3 a, Mat3x3 b) {
    double trace_AtB = 0.0;
    for (int i = 0; i < 9; ++i)
        trace_AtB += a.flat[i] * b.flat[i];

    double cos_theta = (trace_AtB - 1.0) * 0.5;

    if (cos_theta < -1.0)
        cos_theta = -1.0;
    if (cos_theta > 1.0)
        cos_theta = 1.0;

    return acos(cos_theta);
}

double mat3x3_angle_between(Mat3x3 a, Mat3x3 b) {
    double dot = 0.0;
    double norm_a_sq = 0.0;
    double norm_b_sq = 0.0;

    for (int i = 0; i < 9; ++i) {
        dot += a.flat[i] * b.flat[i];
        norm_a_sq += a.flat[i] * a.flat[i];
        norm_b_sq += b.flat[i] * b.flat[i];
    }

    double denom = sqrt(norm_a_sq * norm_b_sq);
    if (denom < TF_EPS_DENOM) {
        return 0.0;
    }

    double cos_theta = dot / denom;
    if (cos_theta < -1.0)
        cos_theta = -1.0;
    if (cos_theta > 1.0)
        cos_theta = 1.0;

    return acos(cos_theta);
}

bool mat3x3_eq(Mat3x3 a, Mat3x3 b) {
    for (int i = 0; i < 9; ++i) {
        if (a.flat[i] != b.flat[i])
            return false;
    }
    return true;
}

bool mat3x3_eps_eq(Mat3x3 a, Mat3x3 b, double eps) {
    for (int i = 0; i < 9; ++i) {
        if (fabs(a.flat[i] - b.flat[i]) > eps)
            return false;
    }
    return true;
}
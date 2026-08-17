/*
 * Copyright 2026 Rostyslav Zhurbenko
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TABITIFORGE_VEC3_H
#define TABITIFORGE_VEC3_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    double x, y, z;
} Vec3;

/*
 * Initialize Vec3 by coords (x, y, z)
 * Return a Vec3 struct
 */
#define vec3(x, y, z) ((Vec3){x, y, z})

/*
 * Zero vector
 */
#define VEC3_ZERO ((Vec3){0., 0., 0.})


/* Addition */
Vec3 vec3_add(Vec3 a, Vec3 b);

/* Inplace addition */
void vec3_iadd(Vec3 *a, Vec3 b);

/* Subtraction */
Vec3 vec3_sub(Vec3 a, Vec3 b);

/* Inplace subtraction */
void vec3_isub(Vec3 *a, Vec3 b);

/* Scale */
Vec3 vec3_scale(Vec3 v, double s);

/* Inplace scale */
void vec3_iscale(Vec3 *v, double s);

/* Dot product */
double vec3_dot(Vec3 a, Vec3 b);

/* Cross product */
Vec3 vec3_cross(Vec3 a, Vec3 b);

/* Length */
double vec3_len(Vec3 v);

/* Squared length */
double vec3_len2(Vec3 v);

/* Normalize */
Vec3 vec3_norm(Vec3 v);

/* Inplace normalize */
void vec3_inorm(Vec3 *v);

/* Distance */
double vec3_dist(Vec3 a, Vec3 b);

/* Projection */
Vec3 vec3_proj(Vec3 a, Vec3 b);

/* Reflection */
Vec3 vec3_reflect(Vec3 v, Vec3 n);

/* Reflection with normalized normal */
Vec3 vec3_nreflect(Vec3 v, Vec3 n);

/* Negative */
Vec3 vec3_neg(Vec3 v);

/* Inplace negative */
void vec3_ineg(Vec3 *v);

/* Hadamard product */
Vec3 vec3_mul(Vec3 a, Vec3 b);

/* Inplace Hadamard product */
void vec3_imul(Vec3 *a, Vec3 b);

/* Clamp length */
Vec3 vec3_clamp(Vec3 v, double max_len);

/* Inplace clamp length */
void vec3_iclamp(Vec3 *v, double max_len);

/* Linear interpolation */
Vec3 vec3_lerp(Vec3 a, Vec3 b, double t);

/* Inplace linear interpolation */
void vec3_ilerp(Vec3 *a, Vec3 b, double t);

/* Angle between vectors, radians */
double vec3_angle_between(Vec3 a, Vec3 b);

/* Absolute value */
Vec3 vec3_abs(Vec3 v);

/* Inplace absolute value */
void vec3_iabs(Vec3 *v);

/* Equality */
int vec3_eq(Vec3 a, Vec3 b);

/* Rotation */
Vec3 vec3_rotate(Vec3 v, Vec3 k, double theta);

/* Rotation with normalized axis */
Vec3 vec3_nrotate(Vec3 v, Vec3 k, double theta);

#ifdef __cplusplus
}
#endif

#endif
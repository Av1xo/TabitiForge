/*
 * Copyright 2026 Rostyslav Zhurbenko
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "tabitiforge/math/vec3.h"

#include <assert.h>
#include <math.h>

Vec3 vec3_add(Vec3 a, Vec3 b)
{
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

void vec3_iadd(Vec3 *a, Vec3 b)
{
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

Vec3 vec3_sub(Vec3 a, Vec3 b)
{
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

void vec3_isub(Vec3 *a, Vec3 b)
{
    a->x -= b.x;
    a->y -= b.y;
    a->z -= b.z;
}

void vec3_iscale(Vec3 *v, double s)
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

Vec3 vec3_scale(Vec3 v, double s)
{
    return vec3(v.x * s, v.y * s, v.z * s);
}

double vec3_dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_cross(Vec3 a, Vec3 b)
{
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

double vec3_len(Vec3 v)
{
    return sqrt(vec3_dot(v, v));
}

double vec3_len2(Vec3 v)
{
    return vec3_dot(v, v);
}

Vec3 vec3_norm(Vec3 v)
{
    double l = vec3_len(v);

    if (l <= 1e-9)
        return VEC3_ZERO;

    return vec3_scale(v, 1. / l);
}

void vec3_inorm(Vec3 *v)
{
    double l = vec3_len(*v);

    if (l <= 1e-9)
        return;

    vec3_iscale(v, 1. / l);
}

double vec3_dist(Vec3 a, Vec3 b)
{
    return vec3_len(vec3_sub(a, b));
}

Vec3 vec3_proj(Vec3 a, Vec3 b)
{
    double dot_prod_ab = vec3_dot(a, b);
    double len2_b = vec3_len2(b);

    if (len2_b <= 1e-15)
        return VEC3_ZERO;

    return vec3_scale(b, dot_prod_ab / len2_b);
}

Vec3 vec3_reflect(Vec3 v, Vec3 n)
{
    Vec3 n_norm = vec3_norm(n);
    double dot_vn = vec3_dot(v, n_norm);

    return vec3_sub(v, vec3_scale(n_norm, 2. * dot_vn));
}

Vec3 vec3_nreflect(Vec3 v, Vec3 n)
{
    double dot_vn = vec3_dot(v, n);

    return vec3_sub(v, vec3_scale(n, 2. * dot_vn));
}

Vec3 vec3_neg(Vec3 v)
{
    return vec3(-v.x, -v.y, -v.z);
}

void vec3_ineg(Vec3 *v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

Vec3 vec3_mul(Vec3 a, Vec3 b)
{
    return vec3(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    );
}

void vec3_imul(Vec3 *a, Vec3 b)
{
    a->x *= b.x;
    a->y *= b.y;
    a->z *= b.z;
}

Vec3 vec3_clamp(Vec3 v, double max_len)
{
    assert(max_len >= 0 && "max_len must be non-negative");

    double v_len = vec3_len(v);

    if (v_len <= max_len || v_len <= 1e-9)
        return v;

    double scale = max_len / v_len;

    return vec3_scale(v, scale);
}

void vec3_iclamp(Vec3 *v, double max_len)
{
    assert(max_len >= 0 && "max_len must be non-negative");

    double v_len = vec3_len(*v);

    if (v_len <= max_len || v_len <= 1e-9)
        return;

    double scale = max_len / v_len;

    vec3_iscale(v, scale);
}

Vec3 vec3_lerp(Vec3 a, Vec3 b, double t)
{
    t = t < 0. ? 0. : t > 1. ? 1. : t;

    Vec3 path = vec3_sub(b, a);
    path = vec3_scale(path, t);

    return vec3_add(a, path);
}

void vec3_ilerp(Vec3 *a, Vec3 b, double t)
{
    t = t < 0. ? 0. : t > 1. ? 1. : t;

    Vec3 path = vec3_sub(b, *a);
    path = vec3_scale(path, t);

    vec3_iadd(a, path);
}

double vec3_angle_between(Vec3 a, Vec3 b)
{
    double len_ab = sqrt(vec3_len2(a) * vec3_len2(b));

    if (len_ab < 1e-9)
        return 0.;

    double cos_theta = vec3_dot(a, b) / len_ab;

    cos_theta = cos_theta < -1.
        ? -1.
        : cos_theta > 1.
            ? 1.
            : cos_theta;

    return acos(cos_theta);
}

Vec3 vec3_abs(Vec3 v)
{
    return vec3(
        v.x < 0. ? -v.x : v.x,
        v.y < 0. ? -v.y : v.y,
        v.z < 0. ? -v.z : v.z
    );
}

void vec3_iabs(Vec3 *v)
{
    v->x = v->x < 0. ? -v->x : v->x;
    v->y = v->y < 0. ? -v->y : v->y;
    v->z = v->z < 0. ? -v->z : v->z;
}

int vec3_eq(Vec3 a, Vec3 b)
{
    return vec3_len2(vec3_sub(a, b)) < 1e-18;
}

Vec3 vec3_rotate(Vec3 v, Vec3 k, double theta)
{
    double half_theta = theta * 0.5;

    double w = cos(half_theta);
    double sin_half = sin(half_theta);

    Vec3 q_v = vec3_scale(k, sin_half);
    Vec3 cross_qv_v = vec3_cross(q_v, v);
    Vec3 w_v = vec3_scale(v, w);
    Vec3 internal = vec3_add(cross_qv_v, w_v);

    Vec3 final_cross = vec3_cross(q_v, internal);
    Vec3 scaled_final_cross = vec3_scale(final_cross, 2.0);

    return vec3_add(v, scaled_final_cross);
}

Vec3 vec3_nrotate(Vec3 v, Vec3 k, double theta)
{
    Vec3 axis = vec3_norm(k);

    return vec3_rotate(v, axis, theta);
}
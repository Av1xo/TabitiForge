#ifndef VEC3_H
#define VEC3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <assert.h>

typedef struct
{
    double x, y, z;
} Vec3;

/*
* Initialize Vec3 by coords(x, y, z)
* - Return a Vec3 struct
*/
#define vec3(x, y, z) ((Vec3){x, y, z})

/*
* Initialize Vec3 by coords(x, y, z)
* - Return a zeros Vec3 struct
*/
#define VEC3_ZERO ((Vec3){0., 0., 0.})

/*
* Addition two vectors
* Return a new Vec3
*/
static inline Vec3 vec3_add(Vec3 a, Vec3 b)
{ return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }

/*
* Inplace addition two vectors
* ### Function change left vector!!!
*/
static inline void vec3_iadd(Vec3 *a, Vec3 b)
{ a->x += b.x; a->y += b.y; a->z += b.z; }

/*
* Substraction two vectors
* Return a new Vec3
*/
static inline Vec3 vec3_sub(Vec3 a, Vec3 b)
{ return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }

/*
* Inplace substraction two vectors
* ### Function change left vector!!!
*/
static inline void vec3_isub(Vec3 *a, Vec3 b)
{ a->x -= b.x; a->y -= b.y; a->z -= b.z; }

/*
* Inplace scale vector by scalar
* ### Function change original vector!!!
*/
static inline void vec3_iscale(Vec3 *v, double s)
{ v->x *= s; v->y *= s; v->z *= s; }

/*
* Scale vector by scalar
* return a new scaled Vec3
*/
static inline Vec3 vec3_scale(Vec3 v, double s)
{ return vec3(v.x*s, v.y * s, v.z * s); }

/*
* Dot product two vectors
*/
static inline double vec3_dot(Vec3 a, Vec3 b)
{ return a.x*b.x + a.y*b.y + a.z*b.z; }

/*
* Crossing two vectors
* return a new vector
*/
static inline Vec3 vec3_cross(Vec3 a, Vec3 b)
{ return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }

/*
* Find length of vector
* return a double value of vector length
*/
static inline double vec3_len(Vec3 v)
{ return sqrt(vec3_dot(v, v)); }

/* 
* Find length^2 of vector
*/
static inline double vec3_len2(Vec3 v)
{
    return vec3_dot(v, v);
}

/*
* Normalize vector
* Return a new normalized vector or VEC3_ZERO (zero vector)
*/
static inline Vec3 vec3_norm(Vec3 v)
{
    double l = vec3_len(v);
    if (l <= 1e-9) return VEC3_ZERO;
    return vec3_scale(v, 1. / l);
}

/*
* Inplace normalize vector
* ### Function change original vector!!!
*/
static inline void vec3_inorm(Vec3 *v)
{
    double l = vec3_len(*v);
    if (l <= 1e-9) return;
    vec3_iscale(v, 1. / l);
}

/*
* Get a distance between two vectors
* return a double distance
*/
static inline double vec3_dist(Vec3 a, Vec3 b)
{
    return vec3_len(vec3_sub(a, b));
}

/*
* Get a projection vector a to vector b
* return a new proj vector or VEC3_ZERO
*/
static inline Vec3 vec3_proj(Vec3 a, Vec3 b)
{
    double dot_prod_ab = vec3_dot(a, b);
    double len2_b = vec3_len2(b);

    if(len2_b <= 1e-15)
        return VEC3_ZERO;

    return vec3_scale(b, dot_prod_ab/len2_b);
}

/*
* Get a reflection vector v from vector n 
* # EMBEDDED NORMALIZE VECTOR N!!!
* return a new reflected vector
*/
static inline Vec3 vec3_reflect(Vec3 v, Vec3 n)
{
    Vec3 n_norm = vec3_norm(n);
    double dot_vn = vec3_dot(v, n_norm);
    return vec3_sub(v, vec3_scale(n_norm, 2. * dot_vn));
}

/*
* Get a reflection vector v from vector n 
* # ATENTION: n vector is expected to be already normalized
* return a new reflected vector
*/
static inline Vec3 vec3_nreflect(Vec3 v, Vec3 n)
{
    double dot_vn = vec3_dot(v, n);
    return vec3_sub(v, vec3_scale(n, 2. * dot_vn));
}

/*
* Get a negative vector
* Return new negative vector to input v
*/
static inline Vec3 vec3_neg(Vec3 v)
{
    return vec3(-v.x, -v.y, -v.z);
}

/*
* Inplace negative vector
* ### Function change original vector!!!
*/
static inline void vec3_ineg(Vec3 *v)
{
    v->x = -v->x; v->y = -v->y; v->z = -v->z;
}

/*
* Get a hadamard product vector
* Return new hadamard product vector a*b
*/
static inline Vec3 vec3_mul(Vec3 a, Vec3 b)
{
    return vec3(a.x*b.x, a.y*b.y, a.z*b.z);
}

/*
* Inplace hadamard product vector
* ### Function change original vector!!!
*/
static inline void vec3_imul(Vec3 *a, Vec3 b)
{
    a->x = a->x*b.x;
    a->y = a->y*b.y;
    a->z = a->z*b.z;
}

/*
* Clamp vector to the given length
* return a new clamped vector
*/
static inline Vec3 vec3_clamp(Vec3 v, double max_len)
{
    assert(max_len >= 0 && "max_len must be non-negative");
    double v_len = vec3_len(v);
    if (v_len <= max_len || v_len <= 1e-9)
        return v;
    double scale = max_len / v_len;
    return vec3_scale(v, scale);
}

/*
* Clamp vector to the given length
* ### Function change original vector!!!
*/
static inline void vec3_iclamp(Vec3 *v, double max_len)
{
    assert(max_len >= 0 && "max_len must be non-negative");
    double v_len = vec3_len(*v);
    if (v_len <= max_len ||  v_len <= 1e-9) return;
    double scale = max_len / v_len;
    vec3_iscale(v, scale);
}

/*
* Linear vector interpolation
* Get a interpolated vector between a b with coef t
* 0. <= t <= 1. autoclamp
* return a new interpolated vector
*/
static inline Vec3 vec3_lerp(Vec3 a, Vec3 b, double t)
{
    // clamp t, muhahahah i known this is evil 0:)
    t = t < 0. ? 0. : t > 1. ? 1. : t;
    Vec3 path = vec3_sub(b, a);
    path = vec3_scale(path, t);
    return vec3_add(a, path);
}

/*
* Linear vector interpolation
* Get a interpolated vector between a b with coef t
* 0. <= t <= 1. autoclamp
* ### Function change left vector!!!
*/
static inline void vec3_ilerp(Vec3 *a, Vec3 b, double t)
{
    // clamp t, muhahahah i known this is evil 0:)
    t = t < 0. ? 0. : t > 1. ? 1. : t;
    Vec3 path = vec3_sub(b, *a);
    path = vec3_scale(path, t);
    vec3_iadd(a, path);
}

/*
* Get angle between vectors a and b
* Returns angle in RADIANS between 0 and PI
*/
static inline double vec3_angle_between(Vec3 a, Vec3 b)
{
    double len_ab = sqrt(vec3_len2(a) * vec3_len2(b));
    if (len_ab < 1e-9) return 0.;

    double cos_theta = vec3_dot(a, b) / len_ab;

    cos_theta = cos_theta < -1. ? -1. : cos_theta > 1. ? 1.0 : cos_theta;

    return acos(cos_theta);
}

/*
* Get absolute vector
*/
static inline Vec3 vec3_abs(Vec3 v)
{
    return vec3(
        v.x < 0. ? -v.x : v.x,
        v.y < 0. ? -v.y : v.y,
        v.z < 0. ? -v.z : v.z
    );
}

static inline void vec3_iabs(Vec3 *v)
{
    v->x = v->x < 0. ? -v->x : v->x;
    v->y = v->y < 0. ? -v->y : v->y;
    v->z = v->z < 0. ? -v->z : v->z;
}

static inline int vec3_eq(Vec3 a, Vec3 b)
{
    return (vec3_len2(vec3_sub(a, b)) < 1e-18);
}

static inline Vec3 vec3_rotate(Vec3 v, Vec3 k, double theta)
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

static inline Vec3 vec3_nrotate(Vec3 v, Vec3 k, double theta)
{
    Vec3 axis = vec3_norm(k);
    return vec3_rotate(v, axis, theta);
}

#ifdef __cplusplus
}
#endif

#endif
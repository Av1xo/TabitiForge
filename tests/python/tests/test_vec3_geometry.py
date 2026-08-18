# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

import ctypes
import math

import pytest

from bindings.vec3 import Vec3, lib, VEC3_ZERO


# DOT
def test_vec3_dot_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)

    result = lib.vec3_dot(a, b)

    assert lib.vec3_eq(a, Vec3(1.0, 2.0, 3.0))
    assert lib.vec3_eq(b, Vec3(4.0, 5.0, 6.0))
    assert result == pytest.approx(32.0)


def test_vec3_dot_orthogonal():
    a = Vec3(1.0, 0.0, 0.0)
    b = Vec3(0.0, 1.0, 0.0)

    result = lib.vec3_dot(a, b)

    assert result == pytest.approx(0.0)


def test_vec3_dot_zero():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_dot(a, VEC3_ZERO)

    assert result == pytest.approx(0.0)


def test_vec3_dot_self_equals_len2():
    a = Vec3(1.0, 2.0, 3.0)

    dot_result = lib.vec3_dot(a, a)
    len2_result = lib.vec3_len2(a)

    assert dot_result == pytest.approx(len2_result)


def test_vec3_dot_commutative():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, -5.0, 6.0)

    result1 = lib.vec3_dot(a, b)
    result2 = lib.vec3_dot(b, a)

    assert result1 == pytest.approx(result2)


# CROSS
def test_vec3_cross_basic():
    a = Vec3(1.0, 0.0, 0.0)
    b = Vec3(0.0, 1.0, 0.0)

    result = lib.vec3_cross(a, b)

    assert result.x == pytest.approx(0.0)
    assert result.y == pytest.approx(0.0)
    assert result.z == pytest.approx(1.0)


def test_vec3_cross_anti_commutative():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)

    result1 = lib.vec3_cross(a, b)
    result2 = lib.vec3_cross(b, a)

    assert result1.x == pytest.approx(-result2.x)
    assert result1.y == pytest.approx(-result2.y)
    assert result1.z == pytest.approx(-result2.z)


def test_vec3_cross_self_zero():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_cross(a, a)

    assert result.x == pytest.approx(0.0)
    assert result.y == pytest.approx(0.0)
    assert result.z == pytest.approx(0.0)


def test_vec3_cross_zero():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_cross(a, VEC3_ZERO)

    assert result.x == pytest.approx(0.0)
    assert result.y == pytest.approx(0.0)
    assert result.z == pytest.approx(0.0)


def test_vec3_cross_orthogonal_to_inputs():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 0.0, -1.0)

    result = lib.vec3_cross(a, b)

    assert lib.vec3_dot(result, a) == pytest.approx(0.0, abs=1e-9)
    assert lib.vec3_dot(result, b) == pytest.approx(0.0, abs=1e-9)


# LEN / LEN2
def test_vec3_len_basic():
    a = Vec3(3.0, 4.0, 0.0)

    result = lib.vec3_len(a)

    assert result == pytest.approx(5.0)


def test_vec3_len_zero():
    result = lib.vec3_len(VEC3_ZERO)

    assert result == pytest.approx(0.0)


def test_vec3_len_negative_components():
    a = Vec3(-3.0, -4.0, 0.0)

    result = lib.vec3_len(a)

    assert result == pytest.approx(5.0)


def test_vec3_len2_basic():
    a = Vec3(3.0, 4.0, 0.0)

    result = lib.vec3_len2(a)

    assert result == pytest.approx(25.0)


def test_vec3_len2_zero():
    result = lib.vec3_len2(VEC3_ZERO)

    assert result == pytest.approx(0.0)


def test_vec3_len2_equals_len_squared():
    a = Vec3(1.0, 2.0, 3.0)

    len_result = lib.vec3_len(a)
    len2_result = lib.vec3_len2(a)

    assert len2_result == pytest.approx(len_result ** 2)


# NORM / INORM
def test_vec3_norm_basic():
    a = Vec3(3.0, 4.0, 0.0)

    result = lib.vec3_norm(a)

    assert a.x == 3.0
    assert a.y == 4.0
    assert a.z == 0.0

    assert result.x == pytest.approx(0.6)
    assert result.y == pytest.approx(0.8)
    assert result.z == pytest.approx(0.0)


def test_vec3_norm_zero_vector():
    result = lib.vec3_norm(VEC3_ZERO)

    assert lib.vec3_eq(result, VEC3_ZERO)


def test_vec3_norm_near_zero_vector():
    # below the 1e-9 length threshold used internally
    tiny = Vec3(1e-12, 0.0, 0.0)

    result = lib.vec3_norm(tiny)

    assert lib.vec3_eq(result, VEC3_ZERO)


def test_vec3_norm_length_is_one():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_norm(a)

    assert lib.vec3_len(result) == pytest.approx(1.0)


def test_vec3_norm_already_unit():
    a = Vec3(1.0, 0.0, 0.0)

    result = lib.vec3_norm(a)

    assert result.x == pytest.approx(1.0)
    assert result.y == pytest.approx(0.0)
    assert result.z == pytest.approx(0.0)


def test_vec3_norm_preserves_direction():
    a = Vec3(2.0, 0.0, 0.0)

    result = lib.vec3_norm(a)

    # scaling a normalized vector back up by the original length
    # should reproduce the original vector
    rescaled = lib.vec3_scale(result, lib.vec3_len(a))

    assert lib.vec3_eq(rescaled, a)


def test_vec3_inorm_basic():
    a = Vec3(3.0, 4.0, 0.0)

    lib.vec3_inorm(ctypes.byref(a))

    assert a.x == pytest.approx(0.6)
    assert a.y == pytest.approx(0.8)
    assert a.z == pytest.approx(0.0)
    assert lib.vec3_len(a) == pytest.approx(1.0)


def test_vec3_inorm_zero_vector():
    a = Vec3(0.0, 0.0, 0.0)

    lib.vec3_inorm(ctypes.byref(a))

    assert lib.vec3_eq(a, VEC3_ZERO)

def test_vec3_inorm_near_zero_vector():
    a = Vec3(1e-12, 0.0, 0.0)

    lib.vec3_inorm(ctypes.byref(a))

    assert a.x == pytest.approx(1e-12)

def test_vec3_inorm_eq_to_norm():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(1.0, 2.0, 3.0)

    expected = lib.vec3_norm(a)
    lib.vec3_inorm(ctypes.byref(b))

    assert b.x == pytest.approx(expected.x)
    assert b.y == pytest.approx(expected.y)
    assert b.z == pytest.approx(expected.z)


# DIST
def test_vec3_dist_basic():
    a = Vec3(0.0, 0.0, 0.0)
    b = Vec3(3.0, 4.0, 0.0)

    result = lib.vec3_dist(a, b)

    assert result == pytest.approx(5.0)


def test_vec3_dist_self_zero():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_dist(a, a)

    assert result == pytest.approx(0.0)


def test_vec3_dist_symmetric():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, -5.0, 6.0)

    result1 = lib.vec3_dist(a, b)
    result2 = lib.vec3_dist(b, a)

    assert result1 == pytest.approx(result2)


def test_vec3_dist_equals_len_of_sub():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, -5.0, 6.0)

    dist_result = lib.vec3_dist(a, b)
    len_of_sub = lib.vec3_len(lib.vec3_sub(a, b))

    assert dist_result == pytest.approx(len_of_sub)


# PROJ
def test_vec3_proj_onto_axis():
    a = Vec3(2.0, 3.0, 0.0)
    b = Vec3(1.0, 0.0, 0.0)

    result = lib.vec3_proj(a, b)

    assert result.x == pytest.approx(2.0)
    assert result.y == pytest.approx(0.0)
    assert result.z == pytest.approx(0.0)


def test_vec3_proj_orthogonal_is_zero():
    a = Vec3(0.0, 1.0, 0.0)
    b = Vec3(1.0, 0.0, 0.0)

    result = lib.vec3_proj(a, b)

    assert result.x == pytest.approx(0.0)
    assert result.y == pytest.approx(0.0)
    assert result.z == pytest.approx(0.0)


def test_vec3_proj_onto_self():
    a = Vec3(2.0, 3.0, 4.0)

    result = lib.vec3_proj(a, a)

    assert result.x == pytest.approx(a.x)
    assert result.y == pytest.approx(a.y)
    assert result.z == pytest.approx(a.z)


def test_vec3_proj_onto_zero():
    a = Vec3(2.0, 3.0, 4.0)

    result = lib.vec3_proj(a, VEC3_ZERO)

    # projecting onto a zero-length vector is undefined; document actual
    # behaviour rather than assume a crash-free NaN or a zero result
    assert math.isnan(result.x) or result.x == pytest.approx(0.0)


# REFLECT / NREFLECT
def test_vec3_reflect_basic():
    # incident travelling down-right, bouncing off a flat horizontal surface
    # (unit normal pointing straight up)
    incident = Vec3(1.0, -1.0, 0.0)
    normal = Vec3(0.0, 1.0, 0.0)

    result = lib.vec3_reflect(incident, normal)

    assert result.x == pytest.approx(1.0)
    assert result.y == pytest.approx(1.0)
    assert result.z == pytest.approx(0.0)


def test_vec3_reflect_does_not_mutate_inputs():
    incident = Vec3(1.0, -1.0, 0.0)
    normal = Vec3(0.0, 1.0, 0.0)

    lib.vec3_reflect(incident, normal)

    assert lib.vec3_eq(incident, Vec3(1.0, -1.0, 0.0))
    assert lib.vec3_eq(normal, Vec3(0.0, 1.0, 0.0))


def test_vec3_reflect_parallel_to_normal():
    incident = Vec3(0.0, -1.0, 0.0)
    normal = Vec3(0.0, 1.0, 0.0)

    result = lib.vec3_reflect(incident, normal)

    assert result.x == pytest.approx(0.0)
    assert result.y == pytest.approx(1.0)
    assert result.z == pytest.approx(0.0)


def test_vec3_reflect_preserves_length():
    incident = Vec3(3.0, -4.0, 0.0)
    normal = Vec3(0.0, 1.0, 0.0)

    result = lib.vec3_reflect(incident, normal)

    assert lib.vec3_len(result) == pytest.approx(lib.vec3_len(incident))


def test_vec3_nreflect_matches_reflect_with_unit_normal():
    incident = Vec3(1.0, -1.0, 0.0)
    unit_normal = Vec3(0.0, 1.0, 0.0)

    expected = lib.vec3_reflect(incident, unit_normal)
    result = lib.vec3_nreflect(incident, unit_normal)

    assert result.x == pytest.approx(expected.x)
    assert result.y == pytest.approx(expected.y)
    assert result.z == pytest.approx(expected.z)


def test_vec3_reflect_normalizes_non_unit_normal():
    incident = Vec3(1.0, -1.0, 0.0)
    unit_normal = Vec3(0.0, 1.0, 0.0)
    scaled_normal = Vec3(0.0, 5.0, 0.0)

    expected = lib.vec3_reflect(incident, unit_normal)
    result = lib.vec3_reflect(incident, scaled_normal)

    assert result.x == pytest.approx(expected.x)
    assert result.y == pytest.approx(expected.y)
    assert result.z == pytest.approx(expected.z)

def test_vec3_nreflect_uses_normal_as_is():
    incident = Vec3(1.0, -1.0, 0.0)
    scaled_normal = Vec3(0.0, 5.0, 0.0)

    dot_vn = lib.vec3_dot(incident, scaled_normal)
    expected = lib.vec3_sub(incident, lib.vec3_scale(scaled_normal, 2.0 * dot_vn))

    result = lib.vec3_nreflect(incident, scaled_normal)

    assert result.x == pytest.approx(expected.x)
    assert result.y == pytest.approx(expected.y)
    assert result.z == pytest.approx(expected.z)

def test_vec3_reflect_and_nreflect_diverge_for_non_unit_normal():
    incident = Vec3(1.0, -1.0, 0.0)
    scaled_normal = Vec3(0.0, 5.0, 0.0)

    reflect_result = lib.vec3_reflect(incident, scaled_normal)
    nreflect_result = lib.vec3_nreflect(incident, scaled_normal)

    assert reflect_result.y == pytest.approx(1.0)
    assert nreflect_result.y == pytest.approx(49.0)


# ANGLE_BETWEEN
def test_vec3_angle_between_zero_vector():
    assert lib.vec3_angle_between(
        Vec3(0, 0, 0),
        Vec3(1, 0, 0)
    ) == 0.0


def test_vec3_angle_between_orthogonal():
    a = Vec3(1.0, 0.0, 0.0)
    b = Vec3(0.0, 1.0, 0.0)

    result = lib.vec3_angle_between(a, b)

    assert result == pytest.approx(math.pi / 2)


def test_vec3_angle_between_same_direction():
    a = Vec3(1.0, 0.0, 0.0)
    b = Vec3(2.0, 0.0, 0.0)

    result = lib.vec3_angle_between(a, b)

    assert result == pytest.approx(0.0, abs=1e-9)


def test_vec3_angle_between_opposite_direction():
    a = Vec3(1.0, 0.0, 0.0)
    b = Vec3(-1.0, 0.0, 0.0)

    result = lib.vec3_angle_between(a, b)

    assert result == pytest.approx(math.pi)

def test_vec3_angle_between_zero_vector():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_angle_between(a, VEC3_ZERO)

    assert result == pytest.approx(0.0)


def test_vec3_angle_between_both_zero_vectors():
    result = lib.vec3_angle_between(VEC3_ZERO, VEC3_ZERO)

    assert result == pytest.approx(0.0)


def test_vec3_angle_between_symmetric():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, -5.0, 6.0)

    result1 = lib.vec3_angle_between(a, b)
    result2 = lib.vec3_angle_between(b, a)

    assert result1 == pytest.approx(result2)
#
# Copyright 2026 Rostyslav Zhurbenko
#
# SPDX-License-Identifier: Apache-2.0
#

import ctypes
import math

import pytest

from bindings.vec3 import Vec3, lib, VEC3_ZERO


# ROTATE / NROTATE
def test_vec3_rotate_90_degrees_around_z():
    v = Vec3(1.0, 0.0, 0.0)
    axis = Vec3(0.0, 0.0, 1.0)

    result = lib.vec3_rotate(v, axis, math.pi / 2)

    assert result.x == pytest.approx(0.0, abs=1e-9)
    assert result.y == pytest.approx(1.0)
    assert result.z == pytest.approx(0.0, abs=1e-9)


def test_vec3_rotate_does_not_mutate_inputs():
    v = Vec3(1.0, 0.0, 0.0)
    axis = Vec3(0.0, 0.0, 1.0)

    lib.vec3_rotate(v, axis, math.pi / 2)

    assert lib.vec3_eq(v, Vec3(1.0, 0.0, 0.0))
    assert lib.vec3_eq(axis, Vec3(0.0, 0.0, 1.0))


def test_vec3_rotate_zero_angle():
    v = Vec3(1.0, 2.0, 3.0)
    axis = Vec3(0.0, 0.0, 1.0)

    result = lib.vec3_rotate(v, axis, 0.0)

    assert result.x == pytest.approx(v.x)
    assert result.y == pytest.approx(v.y)
    assert result.z == pytest.approx(v.z)


def test_vec3_rotate_full_circle():
    v = Vec3(1.0, 2.0, 3.0)
    axis = Vec3(0.0, 0.0, 1.0)

    result = lib.vec3_rotate(v, axis, 2 * math.pi)

    assert result.x == pytest.approx(v.x, abs=1e-9)
    assert result.y == pytest.approx(v.y, abs=1e-9)
    assert result.z == pytest.approx(v.z, abs=1e-9)


def test_vec3_rotate_preserves_length():
    v = Vec3(1.0, 2.0, 3.0)
    axis = Vec3(0.0, 0.0, 1.0)

    result = lib.vec3_rotate(v, axis, 1.234)

    assert lib.vec3_len(result) == pytest.approx(lib.vec3_len(v))


def test_vec3_nrotate_matches_rotate_with_unit_axis():
    v = Vec3(1.0, 0.0, 0.0)
    unit_axis = Vec3(0.0, 0.0, 1.0)

    expected = lib.vec3_rotate(v, unit_axis, math.pi / 2)
    result = lib.vec3_nrotate(v, unit_axis, math.pi / 2)

    assert result.x == pytest.approx(expected.x)
    assert result.y == pytest.approx(expected.y)
    assert result.z == pytest.approx(expected.z)


def test_vec3_nrotate_normalizes_non_unit_axis():
    v = Vec3(1.0, 0.0, 0.0)
    unit_axis = Vec3(0.0, 0.0, 1.0)
    scaled_axis = Vec3(0.0, 0.0, 5.0)

    expected = lib.vec3_nrotate(v, unit_axis, math.pi / 2)
    result = lib.vec3_nrotate(v, scaled_axis, math.pi / 2)

    assert result.x == pytest.approx(expected.x)
    assert result.y == pytest.approx(expected.y)
    assert result.z == pytest.approx(expected.z)


# LERP / ILERP
def test_vec3_lerp_clamps_t_below_zero():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(5.0, 6.0, 7.0)

    result = lib.vec3_lerp(a, b, -1.0)

    assert lib.vec3_eq(result, a)


def test_vec3_lerp_clamps_t_above_one():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(5.0, 6.0, 7.0)

    result = lib.vec3_lerp(a, b, 2.0)

    assert lib.vec3_eq(result, b)


def test_vec3_ilerp_clamps_t_below_zero():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(5.0, 6.0, 7.0)

    lib.vec3_ilerp(ctypes.byref(a), b, -1.0)

    assert lib.vec3_eq(a, Vec3(1.0, 2.0, 3.0))


def test_vec3_ilerp_clamps_t_above_one():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(5.0, 6.0, 7.0)

    lib.vec3_ilerp(ctypes.byref(a), b, 2.0)

    assert lib.vec3_eq(a, b)
    
def test_vec3_lerp_t_zero():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(5.0, 6.0, 7.0)

    result = lib.vec3_lerp(a, b, 0.0)

    assert result.x == pytest.approx(a.x)
    assert result.y == pytest.approx(a.y)
    assert result.z == pytest.approx(a.z)


def test_vec3_lerp_t_one():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(5.0, 6.0, 7.0)

    result = lib.vec3_lerp(a, b, 1.0)

    assert result.x == pytest.approx(b.x)
    assert result.y == pytest.approx(b.y)
    assert result.z == pytest.approx(b.z)


def test_vec3_lerp_midpoint():
    a = Vec3(0.0, 0.0, 0.0)
    b = Vec3(4.0, 8.0, 10.0)

    result = lib.vec3_lerp(a, b, 0.5)

    assert result.x == pytest.approx(2.0)
    assert result.y == pytest.approx(4.0)
    assert result.z == pytest.approx(5.0)


def test_vec3_lerp_does_not_mutate_inputs():
    a = Vec3(0.0, 0.0, 0.0)
    b = Vec3(4.0, 8.0, 10.0)

    lib.vec3_lerp(a, b, 0.5)

    assert lib.vec3_eq(a, Vec3(0.0, 0.0, 0.0))
    assert lib.vec3_eq(b, Vec3(4.0, 8.0, 10.0))


def test_vec3_ilerp_basic():
    a = Vec3(0.0, 0.0, 0.0)
    b = Vec3(4.0, 8.0, 10.0)

    lib.vec3_ilerp(ctypes.byref(a), b, 0.5)

    assert a.x == pytest.approx(2.0)
    assert a.y == pytest.approx(4.0)
    assert a.z == pytest.approx(5.0)
    assert lib.vec3_eq(b, Vec3(4.0, 8.0, 10.0))


def test_vec3_ilerp_eq_to_lerp():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(1.0, 2.0, 3.0)
    target = Vec3(9.0, -3.0, 4.0)
    t = 0.3

    expected = lib.vec3_lerp(a, target, t)
    lib.vec3_ilerp(ctypes.byref(b), target, t)

    assert b.x == pytest.approx(expected.x)
    assert b.y == pytest.approx(expected.y)
    assert b.z == pytest.approx(expected.z)


# CLAMP / ICLAMP

def test_vec3_clamp_near_zero_vector():
    v = Vec3(1e-12, 0.0, 0.0)

    result = lib.vec3_clamp(v, 0.0)

    assert lib.vec3_eq(result, v)


def test_vec3_iclamp_near_zero_vector():
    v = Vec3(1e-12, 0.0, 0.0)

    lib.vec3_iclamp(ctypes.byref(v), 0.0)

    assert v.x == pytest.approx(1e-12)
    assert v.y == pytest.approx(0.0)
    assert v.z == pytest.approx(0.0)

def test_vec3_clamp_within_limit_unchanged():
    a = Vec3(1.0, 0.0, 0.0)

    result = lib.vec3_clamp(a, 5.0)

    assert result.x == pytest.approx(a.x)
    assert result.y == pytest.approx(a.y)
    assert result.z == pytest.approx(a.z)


def test_vec3_clamp_exceeds_limit_scaled_down():
    a = Vec3(3.0, 4.0, 0.0)  # length 5

    result = lib.vec3_clamp(a, 1.0)

    assert lib.vec3_len(result) == pytest.approx(1.0)


def test_vec3_clamp_preserves_direction():
    a = Vec3(3.0, 4.0, 0.0)  # length 5

    result = lib.vec3_clamp(a, 1.0)

    assert result.x == pytest.approx(0.6)
    assert result.y == pytest.approx(0.8)
    assert result.z == pytest.approx(0.0)


def test_vec3_clamp_does_not_mutate_input():
    a = Vec3(3.0, 4.0, 0.0)

    lib.vec3_clamp(a, 1.0)

    assert lib.vec3_eq(a, Vec3(3.0, 4.0, 0.0))


def test_vec3_iclamp_basic():
    a = Vec3(3.0, 4.0, 0.0)  # length 5

    lib.vec3_iclamp(ctypes.byref(a), 1.0)

    assert lib.vec3_len(a) == pytest.approx(1.0)
    assert a.x == pytest.approx(0.6)
    assert a.y == pytest.approx(0.8)


def test_vec3_iclamp_within_limit_unchanged():
    a = Vec3(1.0, 0.0, 0.0)

    lib.vec3_iclamp(ctypes.byref(a), 5.0)

    assert a.x == pytest.approx(1.0)
    assert a.y == pytest.approx(0.0)
    assert a.z == pytest.approx(0.0)


# ABS / IABS
def test_vec3_abs_each_component_branch():
    assert lib.vec3_eq(
        lib.vec3_abs(Vec3(-1.0, 2.0, 3.0)),
        Vec3(1.0, 2.0, 3.0),
    )

    assert lib.vec3_eq(
        lib.vec3_abs(Vec3(1.0, -2.0, 3.0)),
        Vec3(1.0, 2.0, 3.0),
    )

    assert lib.vec3_eq(
        lib.vec3_abs(Vec3(1.0, 2.0, -3.0)),
        Vec3(1.0, 2.0, 3.0),
    )

def test_vec3_iabs_each_component_branch():
    v = Vec3(-1.0, 2.0, 3.0)
    lib.vec3_iabs(ctypes.byref(v))
    assert lib.vec3_eq(v, Vec3(1.0, 2.0, 3.0))

    v = Vec3(1.0, -2.0, 3.0)
    lib.vec3_iabs(ctypes.byref(v))
    assert lib.vec3_eq(v, Vec3(1.0, 2.0, 3.0))

    v = Vec3(1.0, 2.0, -3.0)
    lib.vec3_iabs(ctypes.byref(v))
    assert lib.vec3_eq(v, Vec3(1.0, 2.0, 3.0))

def test_vec3_abs_basic():
    a = Vec3(-1.0, 2.0, -3.0)

    result = lib.vec3_abs(a)

    assert a.x == -1.0
    assert a.y == 2.0
    assert a.z == -3.0

    assert result.x == pytest.approx(1.0)
    assert result.y == pytest.approx(2.0)
    assert result.z == pytest.approx(3.0)


def test_vec3_abs_already_positive():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_abs(a)

    assert result.x == pytest.approx(1.0)
    assert result.y == pytest.approx(2.0)
    assert result.z == pytest.approx(3.0)


def test_vec3_abs_zero():
    result = lib.vec3_abs(VEC3_ZERO)

    assert lib.vec3_eq(result, VEC3_ZERO)


def test_vec3_iabs_basic():
    a = Vec3(-1.0, 2.0, -3.0)

    lib.vec3_iabs(ctypes.byref(a))

    assert a.x == pytest.approx(1.0)
    assert a.y == pytest.approx(2.0)
    assert a.z == pytest.approx(3.0)


def test_vec3_iabs_eq_to_abs():
    a = Vec3(-1.0, 2.0, -3.0)
    b = Vec3(-1.0, 2.0, -3.0)

    expected = lib.vec3_abs(a)
    lib.vec3_iabs(ctypes.byref(b))

    assert b.x == pytest.approx(expected.x)
    assert b.y == pytest.approx(expected.y)
    assert b.z == pytest.approx(expected.z)
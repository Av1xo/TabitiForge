#
# Copyright 2026 Rostyslav Zhurbenko
#
# SPDX-License-Identifier: Apache-2.0
#

# EQ

from bindings.vec3 import lib, Vec3, VEC3_ZERO

def test_vec3_eq_same():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_eq(a, a)

    assert result == 1


def test_vec3_eq_different():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(1.0, 2.0, 4.0)

    result = lib.vec3_eq(a, b)

    assert result == 0


def test_vec3_eq_zero():
    result = lib.vec3_eq(VEC3_ZERO, VEC3_ZERO)

    assert result == 1


def test_vec3_eq_zero_different():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_eq(a, VEC3_ZERO)

    assert result == 0


def test_vec3_eq_negative():
    a = Vec3(-1.0, -2.0, -3.0)
    b = Vec3(-1.0, -2.0, -3.0)

    result = lib.vec3_eq(a, b)

    assert result == 1


def test_vec3_eq_symmetric():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)

    result_ab = lib.vec3_eq(a, b)
    result_ba = lib.vec3_eq(b, a)

    assert result_ab == result_ba


def test_vec3_eq_within_tolerance():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(1.0 + 1e-10, 2.0, 3.0)

    result = lib.vec3_eq(a, b)

    assert result == 1
    
def test_vec3_eq_outside_tolerance():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(1.0 + 1e-8, 2.0, 3.0)

    result = lib.vec3_eq(a, b)

    assert result == 0
# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

import math

from bindings.core import lib
from bindings.mat3x3 import Mat3x3
from bindings.vec3 import Vec3


def test_mat3x3_eq_and_eps_eq():
    a = Mat3x3.identity()
    b = Mat3x3.identity()
    c = Mat3x3.identity()
    c.flat[0] += 1e-5

    assert a.eq(b)
    assert not a.eq(c)
    assert a.eps_eq(c, 1e-4)
    assert not a.eps_eq(c, 1e-6)


def test_mat3x3_so3_angle_between():
    eye = Mat3x3.identity()
    rot = Mat3x3.rotation(Vec3(0, 0, 1), math.pi / 2.0)

    angle = eye.so3_angle_between(rot)
    assert abs(angle - (math.pi / 2.0)) < 1e-6


def test_mat3x3_angle_between_edge_cases():
    a = Mat3x3.identity()
    b = Mat3x3.zero()

    # (denom < TF_EPS_DENOM)
    assert a.angle_between(b) == 0.0


def test_mat3x3_angle_between_robustness_and_edge_cases():
    eye = Mat3x3.identity()
    zero = Mat3x3.zero()

    # (denom < TF_EPS_DENOM)
    assert eye.angle_between(zero) == 0.0
    assert zero.angle_between(eye) == 0.0
    assert zero.angle_between(zero) == 0.0

    # clamping for acos
    m1 = Mat3x3.identity()
    m2 = Mat3x3.identity()

    angle_self = m1.angle_between(m2)
    assert not math.isnan(angle_self)
    assert abs(angle_self) < 1e-9


def test_mat3x3_so3_angle_between_edge_cases():
    rot1 = Mat3x3.rotation(Vec3(0, 0, 1), 0.0)
    rot2 = Mat3x3.rotation(Vec3(0, 0, 1), 1e-15)

    angle = rot1.so3_angle_between(rot2)
    assert not math.isnan(angle)
    assert angle >= 0.0


def test_mat3x3_explicit_clamping_execution():
    a = Mat3x3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)

    b_high = Mat3x3(1.0, 1e-5, 0.0, 1e-5, 1.0, 0.0, 0.0, 0.0, 1.0)
    b_high.flat[0] = 1.000000000000002

    res_high = lib.mat3x3_angle_between(a, b_high)
    assert not math.isnan(res_high)

    m1 = Mat3x3(1.0, 2.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
    m2 = Mat3x3(1.0, 2.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.9999999)
    lib.mat3x3_angle_between(m1, m2)

    m_so3_high = Mat3x3(2.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 2.0)
    m_so3_low = Mat3x3(-2.0, 0.0, 0.0, 0.0, -2.0, 0.0, 0.0, 0.0, -2.0)

    lib.mat3x3_so3_angle_between(a, m_so3_high)
    lib.mat3x3_so3_angle_between(a, m_so3_low)


def test_mat3x3_angle_between_clamping_exact():
    m1 = Mat3x3(1e16, 1.0, 0.0, 0.0, 1e16, 0.0, 0.0, 0.0, 1.0)
    m2 = Mat3x3(1e16, 1.0, 0.0, 0.0, 1e16, 0.0, 0.0, 0.0, 1.0)

    res_pos = lib.mat3x3_angle_between(m1, m2)
    assert not math.isnan(res_pos)

    m_a = Mat3x3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
    m_b = Mat3x3(
        math.nextafter(1.0, 2.0),
        1e-15,
        1e-15,
        1e-15,
        math.nextafter(1.0, 2.0),
        1e-15,
        1e-15,
        1e-15,
        math.nextafter(1.0, 2.0),
    )
    lib.mat3x3_angle_between(m_a, m_b)

    m_c = Mat3x3(
        -math.nextafter(1.0, 2.0),
        -1e-15,
        -1e-15,
        -1e-15,
        -math.nextafter(1.0, 2.0),
        -1e-15,
        -1e-15,
        -1e-15,
        -math.nextafter(1.0, 2.0),
    )
    lib.mat3x3_angle_between(m_a, m_c)


def test_mat3x3_so3_angle_identity():
    eye = Mat3x3.identity()

    assert abs(eye.so3_angle_between(eye)) < 1e-12


def test_mat3x3_so3_angle_composition():
    r1 = Mat3x3.rotation(Vec3(0, 0, 1), math.pi / 4)
    r2 = Mat3x3.rotation(Vec3(0, 0, 1), math.pi / 2)

    angle = r1.so3_angle_between(r2)

    assert abs(angle - math.pi / 4) < 1e-6

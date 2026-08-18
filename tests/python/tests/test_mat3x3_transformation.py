# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

from bindings.mat3x3 import Mat3x3
from bindings.vec3 import Vec3


def test_mat3x3_transpose_complex():
    m = Mat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)

    # (M^T)^T == M
    assert m.transpose().transpose().eps_eq(m, 1e-9)

    # In-place transpose
    m_copy = Mat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)
    m_copy.itranspose().itranspose()
    assert m_copy.eps_eq(m, 1e-9)


def test_mat3x3_vecmul_complex():
    # Scaling matrix
    m = Mat3x3(2, 0, 0, 0, 3, 0, 0, 0, 4)
    v = Vec3(1.0, 2.0, 3.0)

    v_res = m.vecmul(v)
    assert v_res.x == 2.0 and v_res.y == 6.0 and v_res.z == 12.0

    # In-place vecmul
    v_copy = Vec3(1.0, 2.0, 3.0)
    m.ivecmul(v_copy)
    assert v_copy.x == 2.0 and v_copy.y == 6.0 and v_copy.z == 12.0


def test_mat3x3_outer_and_skew():
    a = Vec3(1, 2, 3)
    b = Vec3(4, 5, 6)

    # Outer product
    outer = Mat3x3.outer(a, b)
    assert outer.m[0][0] == 4.0 and outer.m[0][1] == 5.0 and outer.m[2][2] == 18.0

    # Skew-symmetric property: [k]_x * v == k x v
    k = Vec3(1, 2, 3)
    v = Vec3(4, 5, 6)

    skew = Mat3x3.skew(k)
    res_skew = skew.vecmul(v)

    # cross product
    cross_expected = Vec3(
        k.y * v.z - k.z * v.y,
        k.z * v.x - k.x * v.z,
        k.x * v.y - k.y * v.x,
    )
    assert abs(res_skew.x - cross_expected.x) < 1e-9
    assert abs(res_skew.y - cross_expected.y) < 1e-9
    assert abs(res_skew.z - cross_expected.z) < 1e-9

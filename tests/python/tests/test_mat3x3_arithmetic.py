# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

from bindings.mat3x3 import Mat3x3


def test_mat3x3_add_sub_complex():
    a = Mat3x3(*range(1, 10))
    b = Mat3x3(*range(9, 0, -1))

    # Immutable
    c_add = a.add(b)
    assert list(c_add.flat) == [10.0] * 9

    c_sub = c_add.sub(b)
    assert c_sub.eps_eq(a, 1e-9)

    # In-place chainability
    a_copy = Mat3x3(*range(1, 10))
    res = a_copy.iadd(b).isub(b)
    assert res is a_copy
    assert a_copy.eps_eq(a, 1e-9)


def test_mat3x3_scale_neg_complex():
    m = Mat3x3(*range(1, 10))

    # Negation: -(-M) == M
    assert m.neg().neg().eps_eq(m, 1e-9)

    # Scaling
    m_scaled = m.scale(2.5).scale(0.4)
    assert m_scaled.eps_eq(m, 1e-9)

    # In-place neg and scale
    m_copy = Mat3x3(*range(1, 10))
    m_copy.ineg().iscale(-1.0)
    assert m_copy.eps_eq(m, 1e-9)


def test_mat3x3_mul_complex():
    a = Mat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)
    eye = Mat3x3.identity()

    # M * I = I * M = M
    assert a.mul(eye).eps_eq(a, 1e-9)
    assert eye.mul(a).eps_eq(a, 1e-9)

    a_copy = Mat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)
    a_copy.imul(eye)
    assert a_copy.eps_eq(a, 1e-9)

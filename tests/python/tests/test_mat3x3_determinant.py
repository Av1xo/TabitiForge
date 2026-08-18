# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

from bindings.mat3x3 import Mat3x3


def test_mat3x3_det_properties():
    eye = Mat3x3.identity()
    assert eye.det() == 1.0

    m = Mat3x3(1, 2, 3, 0, 1, 4, 5, 6, 0)
    # det(M^T) == det(M)
    assert abs(m.det() - m.transpose().det()) < 1e-9

    # det(a * M) == a^3 * det(M) for 3x3
    assert abs(m.scale(2.0).det() - (8.0 * m.det())) < 1e-9


def test_mat3x3_trace_and_cofactor():
    m = Mat3x3(1, 2, 3, 0, 4, 5, 1, 0, 6)
    assert m.trace() == 11.0  # 1 + 4 + 6

    # Fundamental Property: A * C^T = det(A) * I
    cofactor = m.cofactor()
    res = m.mul(cofactor.transpose())
    expected = Mat3x3.identity().scale(m.det())

    assert res.eps_eq(expected, 1e-6)


def test_mat3x3_det_basic_cases():
    assert Mat3x3.zero().det() == 0.0

    diagonal = Mat3x3(
        2,
        0,
        0,
        0,
        3,
        0,
        0,
        0,
        4,
    )

    assert diagonal.det() == 24.0

    upper = Mat3x3(
        2,
        5,
        7,
        0,
        3,
        8,
        0,
        0,
        4,
    )

    assert upper.det() == 24.0


def test_mat3x3_det_negative():
    m = Mat3x3(
        -1,
        0,
        0,
        0,
        2,
        0,
        0,
        0,
        3,
    )

    assert m.det() == -6.0


def test_mat3x3_trace_additivity():
    a = Mat3x3(
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
    )

    b = Mat3x3(
        9,
        8,
        7,
        6,
        5,
        4,
        3,
        2,
        1,
    )

    assert abs(a.add(b).trace() - (a.trace() + b.trace())) < 1e-12


def test_mat3x3_cofactor_identity():
    eye = Mat3x3.identity()

    assert eye.cofactor().eps_eq(eye, 1e-12)

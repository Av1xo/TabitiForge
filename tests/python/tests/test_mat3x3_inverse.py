# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

from bindings.core import lib
from bindings.mat3x3 import Mat3x3


def test_mat3x3_inv_success():
    m = Mat3x3(1, 2, 3, 0, 1, 4, 5, 6, 0)
    ok, inv = m.inv()

    assert ok
    # M * M^-1 == I
    identity1 = m.mul(inv)
    identity2 = inv.mul(m)

    assert identity1.eps_eq(Mat3x3.identity(), 1e-6)
    assert identity2.eps_eq(Mat3x3.identity(), 1e-6)


def test_mat3x3_inv_singular_fallback():
    singular = Mat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)
    ok, _ = singular.inv()
    assert not ok


def test_mat3x3_inv_null_pointer_coverage():
    m = Mat3x3.identity()
    ok = lib.mat3x3_inv(m, None)
    assert ok


def test_mat3x3_inv_null_pointer_singular():
    singular = Mat3x3(1, 2, 3, 4, 5, 6, 7, 8, 9)

    ok = lib.mat3x3_inv(singular, None)

    assert not ok


def test_mat3x3_inv_negative_determinant():
    m = Mat3x3(-1, 0, 0, 0, 2, 0, 0, 0, 3)

    assert m.det() == -6.0

    ok, inv = m.inv()

    assert ok
    assert m.mul(inv).eps_eq(Mat3x3.identity(), 1e-12)


def test_mat3x3_inv_known_result():
    m = Mat3x3(1, 2, 3, 0, 1, 4, 5, 6, 0)

    ok, inv = m.inv()

    assert ok

    expected = Mat3x3(-24, 18, 5, 20, -15, -4, -5, 4, 1)

    assert inv.eps_eq(expected, 1e-12)

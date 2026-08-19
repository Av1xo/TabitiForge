# Copyright (c) 2026 Rostyslav Zhurbenko, Valeriia Syrotenko
# SPDX-License-Identifier: Apache-2.0

import math

from bindings.mat3x3 import Mat3x3
from bindings.vec3 import Vec3
from hypothesis import given
from hypothesis import strategies as st

floats = st.floats(min_value=-1e3, max_value=1e3, allow_nan=False, allow_infinity=False)


@st.composite
def mat3x3_strategy(draw):
    scalars = [draw(floats) for _ in range(9)]
    return Mat3x3(*scalars)


@st.composite
def vec3_strategy(draw):
    return Vec3(draw(floats), draw(floats), draw(floats))


@given(m=mat3x3_strategy())
def test_property_double_transpose(m):
    # (M^T)^T == M (чистий та in-place)
    assert m.transpose().transpose().eps_eq(m, 1e-5)

    m_copy = Mat3x3(*m.flat)
    m_copy.itranspose().itranspose()
    assert m_copy.eps_eq(m, 1e-5)


@given(a=mat3x3_strategy(), b=mat3x3_strategy())
def test_property_transpose_multiplication(a, b):
    # (A * B)^T == B^T * A^T
    lhs = a.mul(b).transpose()
    rhs = b.transpose().mul(a.transpose())
    assert lhs.eps_eq(rhs, 1e-4)


@given(a=mat3x3_strategy(), b=mat3x3_strategy())
def test_property_inplace_arithmetic_equivalence(a, b):
    # iadd / isub / imul == add / sub / mul
    add_pure = a.add(b)
    a_add = Mat3x3(*a.flat)
    a_add.iadd(b)
    assert a_add.eps_eq(add_pure, 1e-5)

    sub_pure = a.sub(b)
    a_sub = Mat3x3(*a.flat)
    a_sub.isub(b)
    assert a_sub.eps_eq(sub_pure, 1e-5)

    mul_pure = a.mul(b)
    a_mul = Mat3x3(*a.flat)
    a_mul.imul(b)
    assert a_mul.eps_eq(mul_pure, 1e-4)


@given(m=mat3x3_strategy(), s=floats)
def test_property_inplace_scale_neg_equivalence(m, s):
    # iscale / ineg VS scale / neg
    scale_pure = m.scale(s)
    m_scale = Mat3x3(*m.flat)
    m_scale.iscale(s)
    assert m_scale.eps_eq(scale_pure, 1e-5)

    neg_pure = m.neg()
    m_neg = Mat3x3(*m.flat)
    m_neg.ineg()
    assert m_neg.eps_eq(neg_pure, 1e-5)


@given(m=mat3x3_strategy(), v=vec3_strategy())
def test_property_inplace_ivecmul_equivalence(m, v):
    # vecmul vs ivecmul
    v_pure = m.vecmul(v)

    v_copy = Vec3(v.x, v.y, v.z)
    m.ivecmul(v_copy)

    assert abs(v_copy.x - v_pure.x) < 1e-5
    assert abs(v_copy.y - v_pure.y) < 1e-5
    assert abs(v_copy.z - v_pure.z) < 1e-5


@given(k=vec3_strategy(), theta=st.floats(min_value=-math.pi, max_value=math.pi))
def test_property_rotation_determinant_is_one(k, theta):
    rot = Mat3x3.rotation(k, theta)
    assert abs(rot.det() - 1.0) < 1e-5


@given(
    a=mat3x3_strategy(),
    b=mat3x3_strategy(),
    c=mat3x3_strategy(),
)
def test_property_multiplication_associativity(a, b, c):
    lhs = a.mul(b).mul(c)
    rhs = a.mul(b.mul(c))

    assert lhs.eps_eq(rhs, 1e-4)


@given(
    a=mat3x3_strategy(),
    b=mat3x3_strategy(),
    c=mat3x3_strategy(),
)
def test_property_multiplication_distributivity(a, b, c):
    lhs = a.mul(b.add(c))
    rhs = a.mul(b).add(a.mul(c))

    assert lhs.eps_eq(rhs, 1e-4)


@given(
    a=mat3x3_strategy(),
    b=mat3x3_strategy(),
    c=mat3x3_strategy(),
)
def test_property_right_distributivity(a, b, c):
    lhs = a.add(b).mul(c)
    rhs = a.mul(c).add(b.mul(c))

    assert lhs.eps_eq(rhs, 1e-4)


@given(a=mat3x3_strategy())
def test_property_inplace_returns_self(a):
    result = a.iadd(Mat3x3.zero())

    assert result is a


@given(a=mat3x3_strategy())
def test_property_inplace_scale_zero(a):
    Mat3x3(*a.flat)

    a.iscale(0.0)

    assert a.eps_eq(Mat3x3.zero(), 1e-12)


@given(
    k=vec3_strategy(),
    theta=st.floats(
        min_value=-math.pi,
        max_value=math.pi,
        allow_nan=False,
        allow_infinity=False,
    ),
)
def test_property_rotation_is_orthogonal(k, theta):
    rot = Mat3x3.rotation(k, theta)

    identity = rot.transpose().mul(rot)

    assert identity.eps_eq(Mat3x3.identity(), 1e-5)

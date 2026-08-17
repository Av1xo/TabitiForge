#
# Copyright 2026 Rostyslav Zhurbenko
#
# SPDX-License-Identifier: Apache-2.0
#

import ctypes
from bindings.vec3 import Vec3, lib, VEC3_ZERO

# ADD
def test_vec3_add_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    
    result = lib.vec3_add(a, b)
    
    assert lib.vec3_eq(a, Vec3(1.0, 2.0, 3.0))
    assert lib.vec3_eq(b, Vec3(4.0, 5.0, 6.0))
    assert lib.vec3_eq(result, Vec3(5.0, 7.0, 9.0))

def test_vec3_iadd_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    
    lib.vec3_iadd(ctypes.byref(a), b)
    
    assert lib.vec3_eq(a, Vec3(5.0, 7.0, 9.0))
    assert lib.vec3_eq(b, Vec3(4.0, 5.0, 6.0))
    
def test_vec3_add_negative():
    a = Vec3(-1.0, 2.0, -3.0)
    b = Vec3(4.0, -5.0, 6.0)
    
    result = lib.vec3_add(a, b)
    
    assert a.x == -1.0
    assert a.y == 2.0
    assert a.z == -3.0
    
    assert b.x == 4.0
    assert b.y == -5.0
    assert b.z == 6.0
    
    assert result.x == 3.0
    assert result.y == -3.0
    assert result.z == 3.0

def test_vec3_iadd_negative():
    a = Vec3(-1.0, 2.0, -3.0)
    b = Vec3(4.0, -5.0, 6.0)
    
    lib.vec3_iadd(ctypes.byref(a), b)
    
    assert a.x == 3.0
    assert a.y == -3.0
    assert a.z == 3.0
    
    assert b.x == 4.0
    assert b.y == -5.0
    assert b.z == 6.0
    
def test_vec3_add_zero():
    a = Vec3(2.0, 3.2, 3.0)
    
    result = lib.vec3_add(a, VEC3_ZERO)
    
    assert a.x == 2.0
    assert a.y == 3.2
    assert a.z == 3.0
    
    assert result.x == 2.0
    assert result.y == 3.2
    assert result.z == 3.0

def test_vec3_iadd_zero():
    a = Vec3(2.0, 3.2, 3.0)
    
    lib.vec3_iadd(ctypes.byref(a), VEC3_ZERO)
    
    assert a.x == 2.0
    assert a.y == 3.2
    assert a.z == 3.0

def test_vec3_add_commutative():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    
    result1 = lib.vec3_add(a, b)
    result2 = lib.vec3_add(b, a)
    
    assert result1.x == result2.x
    assert result1.y == result2.y
    assert result1.z == result2.z
    
def test_vec3_iadd_commutative():
    a1 = Vec3(1.0, 2.0, 3.0)
    b1 = Vec3(4.0, 5.0, 6.0)
    
    a2 = Vec3(1.0, 2.0, 3.0)
    b2 = Vec3(4.0, 5.0, 6.0)
    
    lib.vec3_iadd(ctypes.byref(a1), b1)
    lib.vec3_iadd(ctypes.byref(b2), a2)
    
    assert a1.x == b2.x
    assert a1.y == b2.y
    assert a1.z == b2.z

# SUB
def test_vec3_sub_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    
    result = lib.vec3_sub(a, b)

    assert a.x == 1.0
    assert a.y == 2.0
    assert a.z == 3.0
    
    assert b.x == 4.0
    assert b.y == 5.0
    assert b.z == 6.0
    
    assert result.x == -3.0
    assert result.y == -3.0
    assert result.z == -3.0
    
def test_vec3_isub_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    
    lib.vec3_isub(ctypes.byref(a), b)
    
    assert b.x == 4.0
    assert b.y == 5.0
    assert b.z == 6.0
    
    assert a.x == -3.0
    assert a.y == -3.0
    assert a.z == -3.0
    
def test_vec3_sub_negative():
    a = Vec3(-3.0, 5.0, -3.0)
    b = Vec3(2.0, -3.0, 2.0)
    
    result = lib.vec3_sub(a, b)
    
    assert result.x == -5.0
    assert result.y == 8.0
    assert result.z == -5.0
    
def test_vec3_isub_negative():
    a = Vec3(-3.0, 5.0, -3.0)
    b = Vec3(2.0, -3.0, 2.0)
    
    lib.vec3_isub(ctypes.byref(a), b)
    
    assert a.x == -5.0
    assert a.y == 8.0
    assert a.z == -5.0

def test_vec3_sub_zero():
    a = Vec3(1.0, 1.0, 1.0)
    
    result = lib.vec3_sub(a, VEC3_ZERO)
    
    assert result.x == a.x
    assert result.y == a.y
    assert result.z == a.z
    
    result = lib.vec3_sub(VEC3_ZERO, a)
    
    assert result.x == -a.x
    assert result.y == -a.y
    assert result.z == -a.z

def test_vec3_isub_zero():
    a = Vec3(1.0, 1.0, 1.0)
    
    lib.vec3_isub(ctypes.byref(a), VEC3_ZERO)
    
    assert a.x == 1.0
    assert a.y == 1.0
    assert a.z == 1.0
    
    zero_vec = Vec3(0.0, 0.0, 0.0)
    
    lib.vec3_isub(ctypes.byref(zero_vec), a)
    
    assert zero_vec.x == -a.x
    assert zero_vec.y == -a.y
    assert zero_vec.z == -a.z
    
def test_vec3_sub_self():
    a = Vec3(1.0, 1.0, 1.0)
    
    result = lib.vec3_sub(a, a)
    
    assert result.x == VEC3_ZERO.x
    assert result.y == VEC3_ZERO.y
    assert result.z == VEC3_ZERO.z

def test_vec3_isub_self():
    a = Vec3(1.0, 1.0, 1.0)
    
    lib.vec3_isub(ctypes.byref(a), a)
    
    assert a.x == VEC3_ZERO.x
    assert a.y == VEC3_ZERO.y
    assert a.z == VEC3_ZERO.z

def test_vec3_sub_anti_commutative():
    a = Vec3(1.0, 1.0, 1.0)
    b = Vec3(2.0, 2.0, 2.0)
    
    result1 = lib.vec3_sub(a, b)
    result2 = lib.vec3_sub(b, a)
    
    assert result1.x == -result2.x
    assert result1.y == -result2.y
    assert result1.z == -result2.z

def test_vec3_isub_anti_commutative():
    a1 = Vec3(1.0, 1.0, 1.0)
    b1 = Vec3(2.0, 2.0, 2.0)
    
    lib.vec3_isub(ctypes.byref(a1), b1)
    
    a2 = Vec3(1.0, 1.0, 1.0)
    b2 = Vec3(2.0, 2.0, 2.0)

    lib.vec3_isub(ctypes.byref(b2), a2)
    
    assert a1.x == -b2.x
    assert a1.y == -b2.y
    assert a1.z == -b2.z


# SCALE
def test_vec3_scale_basic():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_scale(a, 2.0)

    assert a.x == 1.0
    assert a.y == 2.0
    assert a.z == 3.0

    assert result.x == 2.0
    assert result.y == 4.0
    assert result.z == 6.0


def test_vec3_iscale_basic():
    a = Vec3(1.0, 2.0, 3.0)

    lib.vec3_iscale(ctypes.byref(a), 2.0)

    assert a.x == 2.0
    assert a.y == 4.0
    assert a.z == 6.0


def test_vec3_scale_zero():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_scale(a, 0.0)

    assert lib.vec3_eq(result, VEC3_ZERO)
    assert a.x == 1.0
    assert a.y == 2.0
    assert a.z == 3.0


def test_vec3_iscale_zero():
    a = Vec3(1.0, 2.0, 3.0)

    lib.vec3_iscale(ctypes.byref(a), 0.0)

    assert lib.vec3_eq(a, VEC3_ZERO)


def test_vec3_scale_one():
    a = Vec3(1.0, 2.0, 3.0)

    result = lib.vec3_scale(a, 1.0)

    assert lib.vec3_eq(result, a)


def test_vec3_iscale_one():
    a = Vec3(1.0, 2.0, 3.0)
    original = Vec3(1.0, 2.0, 3.0)

    lib.vec3_iscale(ctypes.byref(a), 1.0)

    assert lib.vec3_eq(a, original)


def test_vec3_scale_negative():
    a = Vec3(1.0, -2.0, 3.0)

    result = lib.vec3_scale(a, -1.0)

    assert result.x == -1.0
    assert result.y == 2.0
    assert result.z == -3.0


def test_vec3_iscale_negative():
    a = Vec3(1.0, -2.0, 3.0)

    lib.vec3_iscale(ctypes.byref(a), -1.0)

    assert a.x == -1.0
    assert a.y == 2.0
    assert a.z == -3.0


def test_vec3_scale_double():
    a = Vec3(1.5, -2.5, 4.0)

    result = lib.vec3_scale(a, 2.0)

    assert result.x == 3.0
    assert result.y == -5.0
    assert result.z == 8.0


def test_vec3_iscale_double():
    a = Vec3(1.5, -2.5, 4.0)

    lib.vec3_iscale(ctypes.byref(a), 2.0)

    assert a.x == 3.0
    assert a.y == -5.0
    assert a.z == 8.0


def test_vec3_scale_distributive():
    # k*(a+b) == k*a + k*b
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, -1.0, 2.0)
    k = 3.0

    lhs = lib.vec3_scale(lib.vec3_add(a, b), k)
    rhs = lib.vec3_add(lib.vec3_scale(a, k), lib.vec3_scale(b, k))

    assert lib.vec3_eq(lhs, rhs)


def test_vec3_iscale_eq_to_scale():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(1.0, 2.0, 3.0)
    k = 2.5

    expected = lib.vec3_scale(a, k)
    lib.vec3_iscale(ctypes.byref(b), k)

    assert lib.vec3_eq(b, expected)


# MUL (component-wise)
def test_vec3_mul_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)

    result = lib.vec3_mul(a, b)

    assert lib.vec3_eq(a, Vec3(1.0, 2.0, 3.0))
    assert lib.vec3_eq(b, Vec3(4.0, 5.0, 6.0))
    assert result.x == 4.0
    assert result.y == 10.0
    assert result.z == 18.0


def test_vec3_imul_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)

    lib.vec3_imul(ctypes.byref(a), b)

    assert a.x == 4.0
    assert a.y == 10.0
    assert a.z == 18.0
    assert lib.vec3_eq(b, Vec3(4.0, 5.0, 6.0))


def test_vec3_mul_zero():
    a = Vec3(2.0, 3.0, 4.0)

    result = lib.vec3_mul(a, VEC3_ZERO)

    assert lib.vec3_eq(result, VEC3_ZERO)


def test_vec3_imul_zero():
    a = Vec3(2.0, 3.0, 4.0)

    lib.vec3_imul(ctypes.byref(a), VEC3_ZERO)

    assert lib.vec3_eq(a, VEC3_ZERO)


def test_vec3_mul_identity():
    a = Vec3(2.0, 3.0, 4.0)
    ones = Vec3(1.0, 1.0, 1.0)

    result = lib.vec3_mul(a, ones)

    assert lib.vec3_eq(result, a)


def test_vec3_imul_identity():
    a = Vec3(2.0, 3.0, 4.0)
    ones = Vec3(1.0, 1.0, 1.0)

    lib.vec3_imul(ctypes.byref(a), ones)

    assert lib.vec3_eq(a, Vec3(2.0, 3.0, 4.0))


def test_vec3_mul_negative():
    a = Vec3(2.0, -3.0, 4.0)
    b = Vec3(-1.0, -1.0, 2.0)

    result = lib.vec3_mul(a, b)

    assert result.x == -2.0
    assert result.y == 3.0
    assert result.z == 8.0


def test_vec3_imul_negative():
    a = Vec3(2.0, -3.0, 4.0)
    b = Vec3(-1.0, -1.0, 2.0)

    lib.vec3_imul(ctypes.byref(a), b)

    assert a.x == -2.0
    assert a.y == 3.0
    assert a.z == 8.0


def test_vec3_mul_commutative():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)

    result1 = lib.vec3_mul(a, b)
    result2 = lib.vec3_mul(b, a)

    assert result1.x == result2.x
    assert result1.y == result2.y
    assert result1.z == result2.z


# NEG
def test_vec3_neg_basic():
    a = Vec3(1.0, -2.0, 3.0)

    result = lib.vec3_neg(a)

    assert a.x == 1.0
    assert a.y == -2.0
    assert a.z == 3.0

    assert result.x == -1.0
    assert result.y == 2.0
    assert result.z == -3.0


def test_vec3_neg_zero():
    result = lib.vec3_neg(VEC3_ZERO)

    assert lib.vec3_eq(result, VEC3_ZERO)


def test_vec3_neg_double_negation():
    a = Vec3(1.0, -2.0, 3.0)

    result = lib.vec3_neg(lib.vec3_neg(a))

    assert lib.vec3_eq(result, a)
    
def test_vec3_ineg_basic():
    a = Vec3(1.0, -2.0, 3.0)

    lib.vec3_ineg(ctypes.byref(a))

    assert a.x == -1.0
    assert a.y == 2.0
    assert a.z == -3.0

def test_vec3_ineg_zero():
    a = Vec3(0.0, 0.0, 0.0)

    lib.vec3_ineg(ctypes.byref(a))

    assert lib.vec3_eq(a, VEC3_ZERO)

def test_vec3_ineg_eq_to_neg():
    a = Vec3(1.0, -2.0, 3.0)
    b = Vec3(1.0, -2.0, 3.0)

    expected = lib.vec3_neg(a)
    lib.vec3_ineg(ctypes.byref(b))

    assert lib.vec3_eq(b, expected)

def test_vec3_ineg_double_negation():
    a = Vec3(1.0, -2.0, 3.0)
    original = Vec3(1.0, -2.0, 3.0)

    lib.vec3_ineg(ctypes.byref(a))
    lib.vec3_ineg(ctypes.byref(a))

    assert lib.vec3_eq(a, original)

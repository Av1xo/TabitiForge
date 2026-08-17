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
    
    assert a.x == 1.0
    assert a.y == 2.0
    assert a.z == 3.0
    
    assert b.x == 4.0
    assert b.y == 5.0
    assert b.z == 6.0
    
    assert result.x == 5.0
    assert result.y == 7.0
    assert result.z == 9.0

def test_vec3_iadd_basic():
    a = Vec3(1.0, 2.0, 3.0)
    b = Vec3(4.0, 5.0, 6.0)
    
    lib.vec3_iadd(ctypes.byref(a), b)
    
    assert a.x == 5.0
    assert a.y == 7.0
    assert a.z == 9.0
    
    assert b.x == 4.0
    assert b.y == 5.0
    assert b.z == 6.0
    
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

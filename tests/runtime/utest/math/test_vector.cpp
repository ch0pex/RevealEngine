/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_math.hpp
 * @version 1.0
 * @date 05/03/2025
 * @brief Math testing
 *
 * Math testing file with doctest
 *
 */

#include "math/math.hpp"

using namespace rflect3d;


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

DOCTEST_TEST_SUITE_BEGIN("Math");

DOCTEST_TEST_CASE_TEMPLATE("Vectors operators", T, f32, f64) {
  math::Vec2<T> vec2_1 {1.0, 2.0};
  math::Vec2<T> vec2_2 {2.0, 3.0};
  math::Vec3<T> vec3_1 {1.5, 2.0, 3.0};
  math::Vec3<T> vec3_2 {5.0, 4.0, 3.0};
  math::Vec4<T> vec4_1 {1.0, 2.0, 3.0, 4.0};
  math::Vec4<T> vec4_2 {4.0, 3.0, 2.0, 1.0};

  DOCTEST_SUBCASE("Add") {
    DOCTEST_CHECK(vec2_1 + vec2_2 == math::Vec2<T> {3.0, 5.0});
    DOCTEST_CHECK(vec3_1 + vec3_2 == math::Vec3<T> {6.5, 6.0, 6.0});
    DOCTEST_CHECK(vec4_1 + vec4_2 == math::Vec4<T> {5.0, 5.0, 5.0, 5.0});
  }

  DOCTEST_SUBCASE("Add Assignment") {
    math::Vec2<T> v2 = vec2_1;
    v2 += vec2_2;
    DOCTEST_CHECK(v2 == math::Vec2<T> {3.0, 5.0});

    math::Vec3<T> v3 = vec3_1;
    v3 += vec3_2;
    DOCTEST_CHECK(v3 == math::Vec3<T> {6.5, 6.0, 6.0});

    math::Vec4<T> v4 = vec4_1;
    v4 += vec4_2;
    DOCTEST_CHECK(v4 == math::Vec4<T> {5.0, 5.0, 5.0, 5.0});
  }

  DOCTEST_SUBCASE("Subtract") {
    DOCTEST_CHECK(vec2_1 - vec2_2 == math::Vec2<T> {-1.0, -1.0});
    DOCTEST_CHECK(vec3_1 - vec3_2 == math::Vec3<T> {-3.5, -2.0, 0.0});
    DOCTEST_CHECK(vec4_1 - vec4_2 == math::Vec4<T> {-3.0, -1.0, 1.0, 3.0});
  }

  DOCTEST_SUBCASE("Subtract Assignment") {
    math::Vec2<T> v2 = vec2_1;
    v2 -= vec2_2;
    DOCTEST_CHECK(v2 == math::Vec2<T> {-1.0, -1.0});

    math::Vec3<T> v3 = vec3_1;
    v3 -= vec3_2;
    DOCTEST_CHECK(v3 == math::Vec3<T> {-3.5, -2.0, 0.0});

    math::Vec4<T> v4 = vec4_1;
    v4 -= vec4_2;
    DOCTEST_CHECK(v4 == math::Vec4<T> {-3.0, -1.0, 1.0, 3.0});
  }

  DOCTEST_SUBCASE("Multiply (Scalar)") {
    DOCTEST_CHECK(vec2_1 * static_cast<T>(2) == math::Vec2<T> {2.0, 4.0});
    DOCTEST_CHECK(vec3_1 * static_cast<T>(2) == math::Vec3<T> {3.0, 4.0, 6.0});
    DOCTEST_CHECK(vec4_1 * static_cast<T>(2) == math::Vec4<T> {2.0, 4.0, 6.0, 8.0});
  }

  DOCTEST_SUBCASE("Multiply Assignment (Scalar)") {
    math::Vec2<T> v2 = vec2_1;
    v2 *= static_cast<T>(2);
    DOCTEST_CHECK(v2 == math::Vec2<T> {2.0, 4.0});

    math::Vec3<T> v3 = vec3_1;
    v3 *= static_cast<T>(2);
    DOCTEST_CHECK(v3 == math::Vec3<T> {3.0, 4.0, 6.0});

    math::Vec4<T> v4 = vec4_1;
    v4 *= static_cast<T>(2);
    DOCTEST_CHECK(v4 == math::Vec4<T> {2.0, 4.0, 6.0, 8.0});
  }
}


DOCTEST_TEST_SUITE_END();

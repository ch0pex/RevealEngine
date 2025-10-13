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

DOCTEST_TEST_CASE_TEMPLATE("Matrices operators", T, f32, f64) {
  math::Mat3x3<T> mat3_1 {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
  math::Mat3x3<T> mat3_2 {{9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0}};
  math::Mat4x4<T> mat4_1 {{1.0, 0.0, 0.0, 0.0}, {0.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}};
  math::Mat4x4<T> mat4_2 {{0.0, 1.0, 0.0, 0.0}, {1.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}};

  DOCTEST_SUBCASE("Add") {
    DOCTEST_CHECK(mat3_1 + mat3_2 == math::Mat3x3<T> {{10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}});
    DOCTEST_CHECK(
        mat4_1 + mat4_2 ==
        math::Mat4x4<T> {{1.0, 1.0, 0.0, 0.0}, {1.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 2.0, 0.0}, {0.0, 0.0, 0.0, 2.0}}
    );
  }

  DOCTEST_SUBCASE("Add Assignment") {
    math::Mat3x3<T> m3 = mat3_1;
    m3 += mat3_2;
    DOCTEST_CHECK(m3 == math::Mat3x3<T> {{10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}, {10.0, 10.0, 10.0}});

    math::Mat4x4<T> m4 = mat4_1;
    m4 += mat4_2;
    DOCTEST_CHECK(
        m4 == math::Mat4x4<T> {{1.0, 1.0, 0.0, 0.0}, {1.0, 1.0, 0.0, 0.0}, {0.0, 0.0, 2.0, 0.0}, {0.0, 0.0, 0.0, 2.0}}
    );
  }

  DOCTEST_SUBCASE("Multiply") {
    math::Mat3x3<T> m1 = {{2, 0, 1}, {3, 0, 0}, {5, 1, 1}};

    math::Mat3x3<T> m2 = {{1, 0, 1}, {1, 2, 1}, {1, 1, 0}};

    math::Mat3x3<T> result = {{3, 1, 2}, {3, 0, 3}, {7, 3, 6}};

    math::Mat3x3<T> m3 = m1 * m2;

    math::Mat3x3<T> m4 = transpose(m2) * transpose(m1);

    DOCTEST_CHECK(m3 == result);
    DOCTEST_CHECK(m4 == transpose(result));
  }

  DOCTEST_SUBCASE("Multiply by Scalar") {
    DOCTEST_CHECK(
        mat3_1 * static_cast<T>(2) == math::Mat3x3<T> {{2.0, 4.0, 6.0}, {8.0, 10.0, 12.0}, {14.0, 16.0, 18.0}}
    );

    DOCTEST_CHECK(
        mat4_1 * static_cast<T>(2) ==
        math::Mat4x4<T> {{2.0, 0.0, 0.0, 0.0}, {0.0, 2.0, 0.0, 0.0}, {0.0, 0.0, 2.0, 0.0}, {0.0, 0.0, 0.0, 2.0}}
    );

    math::Mat3x3<T> m3 = mat3_1;
    m3 *= static_cast<T>(2);
    DOCTEST_CHECK(m3 == math::Mat3x3<T> {{2.0, 4.0, 6.0}, {8.0, 10.0, 12.0}, {14.0, 16.0, 18.0}});
  }

  DOCTEST_SUBCASE("Multiply by Vector") {
    math::Vec3<T> vec {1, 2, 3};
    DOCTEST_CHECK(mat3_1 * vec == math::Vec3<T> {14, 32, 50});
  }

  // DOCTEST_SUBCASE("Divide (Matrix)") {
  //   math::Mat3x3<T> m3 = mat3_1;
  //   m3 /= mat3_2;
  //   DOCTEST_CHECK(m3 * mat3_2 == mat3_1);
  //
  //   math::Mat4x4<T> m4 = mat4_1;
  //   m4 /= mat4_2;
  //   DOCTEST_CHECK(m4 * mat4_2 == mat4_1);
  // }
  //
  // DOCTEST_SUBCASE("Divide Assignment (Matrix)") {
  //   math::Mat3x3<T> m3 = mat3_1;
  //   m3 /= mat3_2;
  //   DOCTEST_CHECK(m3 * mat3_2 == mat3_1);
  //
  //   math::Mat4x4<T> m4 = mat4_1;
  //   m4 /= mat4_2;
  //   DOCTEST_CHECK(m4 * mat4_2 == mat4_1);
  // }
}

DOCTEST_TEST_CASE("Determinant (Mat3x3)") {
  constexpr math::Mat3x3<f32> mat {{3, 2, 1}, {0, 2, -5}, {-2, 1, 4}};
  constexpr math::Mat4x4<f32> mat2 {{-2, 3, 1, 0}, {4, 1, -3, 2}, {0, -1, 2, 5}, {3, 2, 0, -4}};

  DOCTEST_CHECK(determinant(mat) == 63);

  DOCTEST_CHECK(determinant(mat2) == 332);
}

DOCTEST_TEST_CASE("Adjugate (Mat3x3)") {
  constexpr math::Mat3x3<f32> mat {{0, 1, 1}, {1, 0, 1}, {1, 1, 0}};

  constexpr math::Mat3x3<f32> adj = adjugate(mat);
  constexpr math::Mat3x3<f32> result {
    {-1, 1, 1},
    {1, -1, 1},
    {1, 1, -1},
  };

  DOCTEST_CHECK(adj == result);
}

DOCTEST_TEST_CASE("Inverse Matrix ") {
  constexpr math::Mat3x3<f32> m1 {
    {2, 0, 1},
    {3, 0, 0},
    {5, 1, 1},
  };

  constexpr math::Mat3x3<f32> expected = {
    {0, 1.0f / 3.0f, 0},
    {-1, -1, 1},
    {1, -2.0f / 3.0f, 0},
  };

  constexpr math::Mat3x3<f32> result = inverse(m1);

  DOCTEST_CHECK(expected == result);
}

DOCTEST_TEST_CASE("Vector length") {
  constexpr math::Vec3 vec {3.0f, 4.0f, 12.0f};
  DOCTEST_CHECK(length(vec) == doctest::Approx(13.0f).epsilon(0.001f));
}

DOCTEST_TEST_CASE("Dot product") {
  constexpr math::Vec3 vec1 {1.0f, 2.0f, 3.0f};
  constexpr math::Vec3 vec2 {4.0f, 5.0f, 6.0f};

  DOCTEST_CHECK(dot(vec1, vec2) == doctest::Approx(32.0f).epsilon(0.001f));
}

DOCTEST_TEST_CASE("Cross product") {
  constexpr math::Vec3 vec1 {1.0f, 2.0f, 3.0f};
  constexpr math::Vec3 vec2 {4.0f, 5.0f, 6.0f};

  constexpr math::Vec3<f32> result = cross(vec1, vec2);

  DOCTEST_CHECK(result.x == doctest::Approx(-3.0f).epsilon(0.001f));
  DOCTEST_CHECK(result.y == doctest::Approx(6.0f).epsilon(0.001f));
  DOCTEST_CHECK(result.z == doctest::Approx(-3.0f).epsilon(0.001f));
}

DOCTEST_TEST_CASE("Normalize") {
  constexpr math::Vec3 v3             = {3.0f, 4.0f, 0.0f};
  math::Vec3<f32> const normalized_v3 = normalize(v3);

  DOCTEST_CHECK(length(normalized_v3) == doctest::Approx(1.0f).epsilon(0.001));

  DOCTEST_CHECK(normalized_v3.x == doctest::Approx(0.6f).epsilon(0.001));
  DOCTEST_CHECK(normalized_v3.y == doctest::Approx(0.8f).epsilon(0.001));
}


DOCTEST_TEST_SUITE_END();

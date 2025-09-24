/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_ecs.cpp
 * @version 1.0
 * @date 09/09/2025
 * @brief Short description
 *
 * Longer description
 *
 */


#include <initializer_list>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <ranges>


#include "core/containers/views/filter_indices.hpp"


DOCTEST_TEST_SUITE_BEGIN("Views");

DOCTEST_TEST_CASE("FilterIndices") {

  std::vector dirty_indices {1, 2, 3, 5, 10};
  std::vector vector = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  DOCTEST_SUBCASE("No indices") {
    auto result = vector | rflect3d::core::filter_indices(std::vector<int> {}) | std::ranges::to<std::vector>();
    DOCTEST_CHECK(result.size() == 0);
  }


  DOCTEST_SUBCASE("Simple composition") {
    auto result = vector | rflect3d::core::filter_indices(dirty_indices);

    for (std::size_t i = 0; auto const& element: result) {
      DOCTEST_CHECK(element == dirty_indices[i++]);
    }
  }

  DOCTEST_SUBCASE("Composition + to vector") {
    std::vector result = vector | rflect3d::core::filter_indices(dirty_indices) | std::ranges::to<std::vector>();

    DOCTEST_CHECK(result.size() == 5);
    DOCTEST_CHECK(result[0] == 1);
    DOCTEST_CHECK(result[1] == 2);
    DOCTEST_CHECK(result[2] == 3);
    DOCTEST_CHECK(result[3] == 5);
    DOCTEST_CHECK(result[4] == 10);
  }


  DOCTEST_SUBCASE("Out of range indices") {
    auto func = [&]() {
      return vector | rflect3d::core::filter_indices(std::initializer_list {274, 27}) | std::ranges::to<std::vector>();
    };
    DOCTEST_CHECK_THROWS(func());
  }
}
DOCTEST_TEST_SUITE_END();

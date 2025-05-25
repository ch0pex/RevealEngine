/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_string_literals.cpp
 * @version 1.0
 * @date 14/12/2024
 * @brief Short description
 *
 * Longer description
 */

#include "common/string_literals.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"


DOCTEST_TEST_SUITE_BEGIN("String literals");

DOCTEST_TEST_CASE("Relative path") {
  DOCTEST_CHECK_EQ(
      std::filesystem::path(reveal3d::absolute("../assets/models/car_2millions.obj")).filename(),
      (std::filesystem::path(std::source_location::current().file_name()).parent_path() /
       "../assets/models/car_2millions.obj")
          .filename()
  );

  DOCTEST_CHECK_EQ(
      std::filesystem::path(reveal3d::absolute("../assets/models/car.obj")).filename(),
      (std::filesystem::path(std::source_location::current().file_name()).parent_path() / "../assets/models/car.obj")
          .filename()
  );
}

DOCTEST_TEST_CASE("Relative path as string literal") {
  using namespace reveal3d::literals;
  DOCTEST_CHECK_EQ(reveal3d::absolute(""), ""_abs);
  DOCTEST_CHECK_EQ(reveal3d::absolute("../assets/models/car_2millions.obj"), "../assets/models/car_2millions.obj"_abs);
}

DOCTEST_TEST_SUITE_END();

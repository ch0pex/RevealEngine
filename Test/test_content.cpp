/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_content.cpp
 * @version 1.0
 * @date 09/11/2024
 * @brief Short description
 *
 * Longer description
 */


#include "content/content.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

DOCTEST_TEST_SUITE_BEGIN("Content");

DOCTEST_TEST_CASE("Import obj") {
  using namespace reveal3d::literals;
  auto const mesh = reveal3d::content::import_obj("../../Assets/models/car_2millions.obj"_abs);
  DOCTEST_CHECK(mesh.has_value());
}

DOCTEST_TEST_SUITE_END();

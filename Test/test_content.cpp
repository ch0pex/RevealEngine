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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "content/content.hpp"

TEST_SUITE_BEGIN("Content");

TEST_CASE("Import obj") {
  auto const mesh = reveal3d::content::import_obj(reveal3d::relative("../../Assets/models/car_2millions.obj"));
  DOCTEST_CHECK(mesh.has_value());
}

TEST_SUITE_END();

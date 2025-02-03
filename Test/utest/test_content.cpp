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
#include "doctest/doctest.h"

DOCTEST_TEST_SUITE_BEGIN("Content");

DOCTEST_TEST_CASE("Import with _abs operator") {
  using namespace reveal3d::literals;
  auto const mesh = reveal3d::content::import_obj("../../Assets/models/human.obj"_abs);
  DOCTEST_CHECK(mesh.has_value());
}

DOCTEST_TEST_CASE("Import cube") {
  using namespace reveal3d::literals;
  auto const mesh = reveal3d::content::import_obj(reveal3d::absolute("../../Assets/models/cube.obj"));
  DOCTEST_REQUIRE(mesh.has_value());

  DOCTEST_CHECK(mesh.value().vertex_count == 8);
  DOCTEST_CHECK(mesh.value().triangle_count == 12);
  DOCTEST_CHECK(mesh.value().indices.size() == 36);
}

DOCTEST_TEST_CASE("Import car2million") {
  using namespace reveal3d::literals;
  auto const mesh = reveal3d::content::import_obj(reveal3d::absolute("../../Assets/models/cube.obj"));
  DOCTEST_REQUIRE(mesh.has_value());

  DOCTEST_CHECK(mesh.value().vertex_count == 8);
  DOCTEST_CHECK(mesh.value().triangle_count == 12);
  DOCTEST_CHECK(mesh.value().indices.size() == 36);
}

DOCTEST_TEST_SUITE_END();

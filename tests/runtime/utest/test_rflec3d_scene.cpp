/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_rflec3d_scene.hpp
 * @version 1.0
 * @date 6/13/2025
 * @brief Rflect3d scene
 *
 * Rflect3d scene tests
 */

#include "rflect/containers/dual_vector.hpp"
#include "rflect/converters/soa_to_zip.hpp"
#include "scene/systems/metadata/metadata_system.hpp"
#include "scene/systems/transform/transform_data.hpp"
#include "scene/systems/transform/transform_system.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <iostream>
#include <rflect/converters.hpp>
#include "scene/scene.hpp"

using namespace rflect3d;

struct SoAContainer {
  std::array<int, 5> numbers;
  std::array<double, 5> data;
};


DOCTEST_TEST_SUITE_BEGIN("Scene");

DOCTEST_TEST_CASE("Create Entity") {


  using zip_view = rflect::as_zip<SoAContainer>;

  SoAContainer container;

  zip_view view = container | rflect::soa_to_zip;
  std::cout << std::meta::display_string_of(type_of(^^view));
}

DOCTEST_TEST_SUITE_END();

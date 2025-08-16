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

#include "scene/components/transform.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "scene/scene.hpp"

using namespace rflect3d;


DOCTEST_TEST_SUITE_BEGIN("Scene");

DOCTEST_TEST_CASE("Create Entity") {
  Scene scene;

  ecs::Transform const transform {scene.system<ecs::Transform>(), index_t {0}};
  auto entity = scene.newEntity();
}

DOCTEST_TEST_SUITE_END();

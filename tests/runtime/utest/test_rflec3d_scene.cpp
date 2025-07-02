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

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "engine/scene/components/transform/transform_proxy.hpp"
#include "engine/scene/entity.hpp"

using namespace rflect3d;

DOCTEST_TEST_SUITE_BEGIN("Scene");

DOCTEST_TEST_CASE("Create Entity") {
  Ecs<ecs::Entity> ecs;
  ecs::Transform const transform {ecs, index_t {0}};
  ecs::Entity entity = transform.entity();


  ecs::System<ecs::data::Transform> transforms;
}

DOCTEST_TEST_SUITE_END();

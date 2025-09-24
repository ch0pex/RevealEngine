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
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "engine/scene/entity.hpp"
#include "engine/scene/scene.hpp"

DOCTEST_TEST_SUITE_BEGIN("Transform");
using namespace rflect3d;

DOCTEST_TEST_CASE("System") { }


DOCTEST_TEST_CASE("Component") {
  Scene scene;
  ecs::Entity const e = scene.newEntity();
  ecs::Entity const t = scene.newEntity();

  ecs::Entity const child = e.newChild();
  auto const transform1   = e.component<ecs::Transform>();
  auto const transform2   = t.component<ecs::Transform>();
  DOCTEST_SUBCASE("Set Position") {
    transform1.local().position = {1.0F, 0.0F, 0.0F};
    // transform2.worldPosition({1.0F, 0.0F, 0.0F});
    // child.component<Transform>().update();
    // DOCTEST_CHECK(transform1.position() == transform2.position());
    // DOCTEST_CHECK(transform1.position() == child.component<Transform>().worldPosition());
  }

  // DOCTEST_SUBCASE("Set Rotation") {
  //   transform1.rotation({1.0F, 0.0F, 0.0F});
  //   transform2.worldRotation({1.0F, 0.0F, 0.0F});
  //   child.component<Transform>().update();
  //   DOCTEST_CHECK(transform1.rotation() == transform2.rotation());
  //   DOCTEST_CHECK(transform1.rotation() == child.component<Transform>().worldRotation());
  // }
  //
  // DOCTEST_SUBCASE("Set Scale") {
  //   transform1.scale({1.0F, 0.0F, 0.0F});
  //   transform2.worldScale({1.0F, 0.0F, 0.0F});
  //   child.component<Transform>().update();
  //   DOCTEST_CHECK(transform1.scale() == transform2.worldScale());
  //   DOCTEST_CHECK(transform1.scale() == child.component<Transform>().worldScale());
  // }
}

DOCTEST_TEST_SUITE_END();

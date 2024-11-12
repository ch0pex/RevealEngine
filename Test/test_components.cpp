/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file vector.hpp
 * @version 1.0
 * @date 02/10/2024
 * @brief Scene testing
 *
 * Scene testing file with doctest
 *
 */


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "core/components/transform.hpp"


using namespace reveal3d;
using namespace reveal3d::core;

TEST_SUITE_BEGIN("Components");

TEST_CASE("Transform") {
  Entity const e        = scene.newEntity();
  Entity const t        = scene.newEntity();
  Entity const child    = e.addChild();
  auto const transform1 = e.component<Transform>();
  auto const transform2 = t.component<Transform>();
  DOCTEST_SUBCASE("Set Position") {
    transform1.position({1.0F, 0.0F, 0.0F});
    transform2.worldPosition({1.0F, 0.0F, 0.0F});
    child.component<Transform>().update();
    DOCTEST_CHECK(transform1.position() == transform2.position());
    DOCTEST_CHECK(transform1.position() == child.component<Transform>().worldPosition());
  }

  DOCTEST_SUBCASE("Set Rotation") {
    transform1.rotation({1.0F, 0.0F, 0.0F});
    transform2.worldRotation({1.0F, 0.0F, 0.0F});
    child.component<Transform>().update();
    DOCTEST_CHECK(transform1.rotation() == transform2.rotation());
    DOCTEST_CHECK(transform1.rotation() == child.component<Transform>().worldRotation());
  }

  DOCTEST_SUBCASE("Set Scale") {
    transform1.scale({1.0F, 0.0F, 0.0F});
    transform2.worldScale({1.0F, 0.0F, 0.0F});
    child.component<Transform>().update();
    DOCTEST_CHECK(transform1.scale() == transform2.worldScale());
    DOCTEST_CHECK(transform1.scale() == child.component<Transform>().worldScale());
  }
}

TEST_CASE("Geometry") { }

TEST_CASE("Script") { }

TEST_CASE("RigidBody") { }

TEST_SUITE_END();

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
#include "core/entity.hpp"
#include "doctest/doctest.h"

#include "core/components/transform.hpp"
#include "core/scene.hpp"


using namespace reveal3d;
using namespace reveal3d::core;

DOCTEST_TEST_SUITE_BEGIN("Scene");

DOCTEST_TEST_CASE("Create Entity") {
  DOCTEST_SUBCASE("First entity") {
    Entity entity = scene.newEntity();
    DOCTEST_CHECK(entity.isAlive());
    DOCTEST_CHECK(entity.id() == 0);
  }

  DOCTEST_SUBCASE("Second entity") {
    Entity entity = scene.newEntity();
    DOCTEST_CHECK(entity.isAlive());
    DOCTEST_CHECK(entity.id() == 1);
  }

  DOCTEST_SUBCASE("Remove first entity") {

    DOCTEST_CHECK_NOTHROW(scene.removeEntity(0));
    DOCTEST_CHECK(scene.graph().at(0).entity == id::invalid);
    DOCTEST_CHECK(scene.graph().at(1).prev == id::invalid);
  }

  DOCTEST_SUBCASE("Third entity") {
    Entity entity = scene.newEntity();
    DOCTEST_CHECK(entity.isAlive());
    DOCTEST_CHECK(entity.id() == 2);
    DOCTEST_CHECK(scene.count() == 2);
  }

  DOCTEST_SUBCASE("removeId all entities") {
    DOCTEST_CHECK_NOTHROW(scene.removeEntity(1));
    DOCTEST_CHECK_NOTHROW(scene.removeEntity(2));
    DOCTEST_CHECK(scene.count() == 0);
    for (auto& node: scene.graph()) {
      DOCTEST_CHECK(node.entity == id::invalid);
    }
  }

  DOCTEST_SUBCASE("Adding fist entity again") {
    Entity entity;
    DOCTEST_CHECK_NOTHROW(entity = scene.newEntity());
    DOCTEST_CHECK(scene.count() == 1);
    DOCTEST_CHECK(scene.root().entity == 3);
    scene.removeEntity(entity);
  }
}

DOCTEST_TEST_CASE("Create Child Entities") {
  auto& scene = core::scene;
  DOCTEST_CHECK(scene.count() == 0);
  Entity const entity = scene.newEntity();
  for (i32 i = 0; i < 10; i++) {
    entity.addChild();
  }

  auto const children = entity.children();

  DOCTEST_CHECK_NOTHROW(scene.removeEntity(entity));
  DOCTEST_CHECK(scene.pool<Transform>().dirtyElements().size() == 0);

  for (Entity child: children) {
    DOCTEST_CHECK_FALSE(child.isAlive());
  }
}

DOCTEST_TEST_SUITE_END();

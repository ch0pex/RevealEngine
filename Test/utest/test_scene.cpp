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
  Scene scene;
  {
    Entity entity = core::new_entity(scene);
    DOCTEST_CHECK(entity.isAlive());
    DOCTEST_CHECK(entity.id() == 0);
  }

  {
    Entity entity = core::new_entity(scene);
    DOCTEST_CHECK(entity.isAlive());
    DOCTEST_CHECK(entity.id() == 1);
  }

  {

    DOCTEST_CHECK_NOTHROW(scene.removeEntity(0));
    DOCTEST_CHECK(scene.node(0).entity == id::invalid);
    DOCTEST_CHECK(scene.node(1).prev == id::invalid);
  }

  {
    Entity entity = core::new_entity(scene);
    DOCTEST_CHECK(entity.isAlive());
    DOCTEST_CHECK(entity.id() == 2);
    DOCTEST_CHECK(scene.count() == 2);
  }

  {
    DOCTEST_CHECK_NOTHROW(scene.removeEntity(1));
    DOCTEST_CHECK_NOTHROW(scene.removeEntity(2));
    DOCTEST_CHECK(scene.count() == 0);
    for (auto const& node: scene.graph()) {
      DOCTEST_CHECK(node.entity == id::invalid);
    }
  }

  {
    Entity entity;
    DOCTEST_CHECK_NOTHROW(entity = core::new_entity(scene));
    DOCTEST_CHECK(scene.count() == 1);
    scene.removeEntity(entity);
  }
}

DOCTEST_TEST_CASE("Create Child Entities") {
  Scene scene;
  DOCTEST_CHECK(scene.count() == 0);
  Entity const entity = new_entity(scene);
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

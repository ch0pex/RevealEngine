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

#include "ecs/components/transform.hpp"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "ecs/components/geometry.hpp"
#include "ecs/components/light.hpp"
#include "ecs/components/metadata.hpp"
#include "ecs/components/rigidbody.hpp"
#include "ecs/components/script.hpp"


using namespace rflect3d;
using namespace rflect3d::core;

DOCTEST_TEST_SUITE_BEGIN("Components");

DOCTEST_TEST_CASE_TEMPLATE("GenericPooling", T, Transform, Geometry, Metadata, Light /*, Script, Rigidbody,*/) {
  GenericPool<typename T::pool_type> pool;

  DOCTEST_SUBCASE("Adding and removing one element") {
    id_t const component_id = pool.addComponent(0);

    DOCTEST_CHECK(pool.count() == 1);
    DOCTEST_CHECK_EQ(component_id, 0);

    pool.removeComponent(component_id);
    DOCTEST_CHECK(pool.count() == 0);
  }

  DOCTEST_SUBCASE("Removing un-existent component") {
    DOCTEST_REQUIRE_THROWS(pool.removeComponent(0));
    DOCTEST_REQUIRE_THROWS(pool.removeComponent(322));
  }

  DOCTEST_SUBCASE("Adding empty components") {
    for (i32 i = 0; i < 20000; ++i) {
      pool.addComponent();
    }
    DOCTEST_CHECK(pool.count() == 0);
  }

  DOCTEST_SUBCASE("Multiple components") {
    for (i32 i = 0; i < 20000; ++i) {
      pool.addComponent(i);
    }
    DOCTEST_CHECK(pool.count() == 20000);

    DOCTEST_SUBCASE("Removing all components") {
      for (i32 i = 0; i < 20000; ++i) {
        pool.removeComponent(i);
      }
      DOCTEST_CHECK(pool.count() == 0);
    }

    DOCTEST_SUBCASE("Removing all components") {
      for (i32 i = 0; i < 5; ++i) {
        pool.removeComponent(i);
      }

      DOCTEST_CHECK(pool.count() == 20000 - 5);

      for (i32 i = 0; i < 5; ++i) {
        DOCTEST_CHECK(pool.at(20000 - i - 1) == i);
        DOCTEST_CHECK(pool.at(i) == id::invalid);
      }
    }

    DOCTEST_SUBCASE("Checking ranges") {
      for (auto [index, component]: std::views::enumerate(pool)) {
        DOCTEST_CHECK(component == index);
        DOCTEST_CHECK(pool.getMappedId(component) == index);
      }
    }
  }
}

DOCTEST_TEST_SUITE_END();

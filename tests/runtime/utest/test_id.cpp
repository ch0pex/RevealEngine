/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file id.cpp
 * @version 1.0
 * @date 23/12/2024
 * @brief rflect3d Ids testing
 *
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "core/core.hpp"

#include <ranges>

DOCTEST_TEST_SUITE_BEGIN("rflect3d Ids");

DOCTEST_TEST_CASE("rflect3d id valid") {
  rflect3d::id_t id_valid {0};

  DOCTEST_CHECK(rflect3d::id::is_valid(id_valid));
  DOCTEST_CHECK_FALSE(rflect3d::id::is_valid(rflect3d::id::invalid));
}

DOCTEST_TEST_CASE("rflect3d masks") {
  rflect3d::id_t index {1};
  rflect3d::id_t id {0x01000001};
  rflect3d::id_t new_gen = rflect3d::id::new_generation(index);

  DOCTEST_SUBCASE("rflect3d index mask") {
    DOCTEST_CHECK(rflect3d::id::index(index) == rflect3d::id::index(id));
    DOCTEST_CHECK(rflect3d::id::index(new_gen) == rflect3d::id::index(id));
  }

  DOCTEST_SUBCASE("rflect3d generation mask") {
    DOCTEST_CHECK(rflect3d::id::generation(index) != rflect3d::id::generation(id));
    DOCTEST_CHECK_EQ(rflect3d::id::generation(new_gen), rflect3d::id::generation(id));
    DOCTEST_CHECK(new_gen == id);
  }
}

DOCTEST_TEST_CASE("Id factory") {
  rflect3d::id::Factory<rflect3d::id_t, rflect3d::u32> factory;


  DOCTEST_SUBCASE("Create and remove ids") {
    auto id = factory.create();

    DOCTEST_CHECK(id == rflect3d::id_t {0});

    // Until no free limit is reached still using growing ids
    factory.remove(id);
    id = factory.create();
    DOCTEST_CHECK(id == rflect3d::id_t {1});
  }

  DOCTEST_SUBCASE("Using free ids with new generations") {
    for (rflect3d::u32 i = 0; i < 2000; ++i) {
      factory.create();
    }

    for (rflect3d::u32 i = 500; i < 500 + 1025; ++i) {
      factory.remove(rflect3d::id_t {i});
    }

    rflect3d::id_t id = factory.create();
    DOCTEST_CHECK(id == rflect3d::id::new_generation(rflect3d::id_t {500}));

    factory.remove(id);
    id = factory.create();
    DOCTEST_CHECK(id == rflect3d::id::new_generation(rflect3d::id_t {501}));
  }
}

DOCTEST_TEST_SUITE_END();

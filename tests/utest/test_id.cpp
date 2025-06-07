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

#include "common/common.hpp"

using namespace rflect3d;

DOCTEST_TEST_SUITE_BEGIN("rflect3d Ids");

DOCTEST_TEST_CASE("rflect3d id valid") {
  id_t id_valid = 0;


  DOCTEST_CHECK_FALSE(id::is_valid(id::invalid));
  DOCTEST_CHECK(id::is_valid(id_valid));
}

DOCTEST_TEST_CASE("rflect3d masks") {
  id_t index   = 1;
  id_t id      = 0x01000001;
  id_t new_gen = id::new_generation(index);

  DOCTEST_SUBCASE("rflect3d index mask") {
    DOCTEST_CHECK(id::index(index) == id::index(id));
    DOCTEST_CHECK(id::index(new_gen) == id::index(id));
  }

  DOCTEST_SUBCASE("rflect3d generation mask") {
    DOCTEST_CHECK(id::generation(index) != id::generation(id));
    DOCTEST_CHECK_EQ(id::generation(new_gen), id::generation(id));
    DOCTEST_CHECK(new_gen == id);
  }
}

DOCTEST_TEST_CASE("Id factory") {
  id::Factory id_factory;


  DOCTEST_SUBCASE("Add and remove id") {
    DOCTEST_CHECK_FALSE(id_factory.useFree());

    id_t first = id_factory.newId(0);
    DOCTEST_CHECK_EQ(first, 0);
    DOCTEST_CHECK_EQ(id_factory.freeCount(), 0);

    id_factory.remove(first);
    DOCTEST_CHECK_EQ(id_factory.freeCount(), 1);
  }

  DOCTEST_SUBCASE("Using free") {
    for (auto num: std::views::iota(0, 2000)) {
      id_factory.newId(num);
    }
    for (auto num: std::views::iota(0, 2000)) {
      id_factory.remove(num);
    }

    DOCTEST_CHECK(id_factory.useFree());
    DOCTEST_CHECK(id::index(id_factory.newId(25)) == 0);
    DOCTEST_CHECK(id_factory.freeCount() == (2000 - 1));

    DOCTEST_CHECK_FALSE(id_factory.isAlive(0));
    DOCTEST_CHECK(id_factory.isAlive(id::new_generation(0)));
  }
}

DOCTEST_TEST_SUITE_END();

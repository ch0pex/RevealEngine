/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file id.cpp
 * @version 1.0
 * @date 25/09/2025
 * @brief rflect3d bi_map testing
 *
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "core/containers/bi_map.hpp"


using namespace rflect3d::core;

// ==== Strong types de ejemplo ====
struct id_type {
  int value {};
  auto operator<=>(id_type const&) const = default;
};

struct index_t {
  int value {};
  auto operator<=>(index_t const&) const = default;
};

// ==== Tests ====
TEST_CASE("BiMap<int, std::string> basic insert/at") {

  BiMap<int, std::string> bmap;

  bmap.insert(1, "uno");
  bmap.insert(2, "dos");

  CHECK(bmap.at(1) == "uno");
  CHECK(bmap.at(2) == "dos");

  CHECK(bmap.at(std::string {"uno"}) == 1);
  CHECK(bmap.at(std::string {"dos"}) == 2);
}


TEST_CASE("BiMap<std::string, int> reverse mapping") {

  BiMap<std::string, int> bmap;

  bmap.insert("apple", 100);
  bmap.insert("banana", 200);


  CHECK(bmap.at("apple") == 100);
  CHECK(bmap.at("banana") == 200);

  CHECK(bmap.at(100) == "apple");
  CHECK(bmap.at(200) == "banana");
}

TEST_CASE("BiMap<id_type, index_t> with strong types") {

  BiMap<id_type, index_t> bmap;

  bmap.insert(id_type {1}, index_t {10});
  bmap.insert(id_type {2}, index_t {20});

  CHECK(bmap.at(id_type {1}) == index_t {10});
  CHECK(bmap.at(id_type {2}) == index_t {20});

  CHECK(bmap.at(index_t {10}) == id_type {1});
  CHECK(bmap.at(index_t {20}) == id_type {2});
}

TEST_CASE("BiMap: erase by key") {
  BiMap<int, std::string> bmap;

  bmap.insert(1, "a");

  bmap.insert(2, "b");
  CHECK(bmap.at(1) == "a");

  bmap.erase(1);
  CHECK_THROWS(bmap.at(1));
  CHECK_THROWS(bmap.at(std::string {"a"}));
}

TEST_CASE("BiMap: erase by value") {
  BiMap<int, std::string> bmap;

  bmap.insert(1, "x");
  bmap.insert(2, "y");
  CHECK(bmap.at("x") == 1);

  bmap.erase(std::string {"x"});
  CHECK_THROWS(bmap.at("x"));
  CHECK_THROWS(bmap.at(1));
}

/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_systems.hpp
 * @version 1.0
 * @date 9/13/2025
 * @brief Short description
 *
 * Longer description
 */


#include "scene/components/component.hpp"
#include "scene/systems/system.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "engine/scene/components.hpp"


using namespace rflect3d;
using namespace rflect3d::ecs;

TEST_SUITE_BEGIN("Ecs - Systems");

using namespace rflect3d::ecs;

// ==== Componente de prueba ====
struct Position {
  DEFINE_COMPONENT_PROXY(x, y, z);
  float x {0}, y {0}, z {0};
};


// ==== Sistema bajo prueba ====
using TestSystem = System<Position>;

TEST_CASE("System: add and size") {
  TestSystem sys;
  CHECK(sys.size() == 0);

  sys.add(rflect3d::id_t {1}, Position {.x = 1, .y = 2, .z = 3});
  sys.add(rflect3d::id_t {2}, Position {.x = 4, .y = 5, .z = 6});

  CHECK(sys.size() == 2);
  CHECK(sys.at(rflect3d::id_t {1}).x() == doctest::Approx(1));
  CHECK(sys.at(rflect3d::id_t {2}).y() == doctest::Approx(5));
}

TEST_CASE("System: entityId and entityIndex") {
  TestSystem sys;
  sys.add(rflect3d::id_t {42}, Position {.x = 7, .y = 8, .z = 9});

  auto idx = sys.entityIndex(rflect3d::id_t {42});
  CHECK(idx == index_t {0});

  auto id = sys.entityId(idx);
  CHECK(id == rflect3d::id_t {42});
}

TEST_CASE("System: remove entity") {

  TestSystem sys;

  sys.add(rflect3d::id_t {1}, Position {.x = 1, .y = 0, .z = 0});
  sys.add(rflect3d::id_t {2}, Position {.x = 2, .y = 0, .z = 0});
  sys.add(rflect3d::id_t {3}, Position {.x = 3, .y = 0, .z = 0});

  CHECK(sys.size() == 3);

  sys.remove(rflect3d::id_t {2});
  CHECK(sys.size() == 2);


  // Ya no debería existir el id 2

  auto throwing_func = [&]() { auto _ = sys.entityIndex(rflect3d::id_t {2}); };

  CHECK_THROWS(throwing_func());

  // Los otros siguen presentes
  CHECK(sys.at(rflect3d::id_t {1}).x() == 1);
  CHECK(sys.at(rflect3d::id_t {3}).x() == 3);
}

TEST_CASE("System: access by index") {
  TestSystem sys;
  sys.add(rflect3d::id_t {10}, Position {.x = 10, .y = 20, .z = 30});

  auto pos = sys.at(index_t {0});
  CHECK(pos.x() == 10);
  CHECK(pos.y() == 20);
}

TEST_CASE("System: iterators") {
  TestSystem sys;
  sys.add(rflect3d::id_t {1}, Position {.x = 1, .y = 2, .z = 3});
  sys.add(rflect3d::id_t {2}, Position {.x = 4, .y = 5, .z = 6});

  int sumX = 0;
  for (auto p: sys) {
    sumX += static_cast<int>(p.x());
  }
  CHECK(sumX == 5);
}


TEST_SUITE_END();

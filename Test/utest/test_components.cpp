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

#include "core/components/transform.hpp"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include "content/formats/obj/obj_parser.hpp"
#include "core/components/geometry.hpp"


using namespace reveal3d;
using namespace reveal3d::core;

DOCTEST_TEST_SUITE_BEGIN("Components");

DOCTEST_TEST_CASE("Transform") {
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

DOCTEST_TEST_CASE("Geometry") {
  Entity e           = scene.newEntity();
  Entity t           = scene.newEntity();
  Entity p           = scene.newEntity();
  Entity const child = e.addChild();

  DOCTEST_SUBCASE("Not geometry in entity") {
    auto const geometry  = e.component<Geometry>();
    auto const geometry2 = t.component<Geometry>();
    DOCTEST_CHECK_EQ(geometry.id(), id::invalid);
    DOCTEST_CHECK_EQ(geometry2.id(), id::invalid);
  }

  DOCTEST_SUBCASE("Entity with geometry") {
    using namespace reveal3d::literals;
    render::Mesh mesh;
    auto const human = content::import_obj("../../Assets/models/human.obj"_abs);
    auto const cube  = content::import_obj("../../Assets/models/cube.obj"_abs);

    DOCTEST_REQUIRE(human.has_value());

    DOCTEST_CHECK_EQ(e.component<Geometry>().id(), id::invalid);
    DOCTEST_CHECK_EQ(t.component<Geometry>().id(), id::invalid);
    DOCTEST_CHECK_EQ(p.component<Geometry>().id(), id::invalid);

    e.addComponent<Geometry>(std::move(mesh));
    t.addComponent<Geometry>(human.value());
    p.addComponent<Geometry>(cube.value());

    auto const geometry  = e.component<Geometry>();
    auto const geometry2 = t.component<Geometry>();
    auto const geometry3 = p.component<Geometry>();

    DOCTEST_CHECK_NE(geometry.id(), id::invalid);
    DOCTEST_CHECK_NE(geometry2.id(), id::invalid);
    DOCTEST_CHECK_NE(geometry3.id(), id::invalid);

    DOCTEST_CHECK(geometry.vertexCount() == 0);
    DOCTEST_CHECK(geometry.indexCount() == 0);

    DOCTEST_CHECK(geometry2.vertexCount() == 7418);
    DOCTEST_CHECK(geometry2.triangles() == 14758);
    DOCTEST_CHECK(geometry2.indexCount() == 14758 * 3);

    DOCTEST_CHECK(geometry3.vertexCount() == 8);
    DOCTEST_CHECK(geometry3.triangles() == 12);
    DOCTEST_CHECK(geometry3.indexCount() == 36);
  }
}

DOCTEST_TEST_CASE("Script") { }

DOCTEST_TEST_CASE("RigidBody") { }

DOCTEST_TEST_SUITE_END();

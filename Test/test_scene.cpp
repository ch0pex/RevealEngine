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

#include "core/scene.hpp"


using namespace reveal3d;
using namespace reveal3d::core;

LogLevel loglevel = logDEBUG;

TEST_SUITE_BEGIN("Scene");

TEST_CASE("create Entity") {
    SUBCASE("First entity") {
        Entity entity = scene.newEntity();
        DOCTEST_CHECK(entity.isAlive());
        DOCTEST_CHECK(entity.id() == 0);
    }

    SUBCASE("Second entity") {
        Entity entity = scene.newEntity();
        DOCTEST_CHECK(entity.isAlive());
        DOCTEST_CHECK(entity.id() == 1);
    }

    SUBCASE("remove first entity") {

        DOCTEST_CHECK_THROWS(scene.removeEntity(0));
        DOCTEST_CHECK(scene.Graph().at(0).entity.id() == id::invalid);
        DOCTEST_CHECK(scene.Graph().at(1).prev.id() == id::invalid);
    }

    SUBCASE("Third entity") {
        Entity entity = scene.newEntity();
        DOCTEST_CHECK(entity.isAlive());
        DOCTEST_CHECK(entity.id() == 2);
        DOCTEST_CHECK(scene.count() == 2);
    }

    SUBCASE("remove all entities") {
        DOCTEST_CHECK_THROWS(scene.removeEntity(1));
        DOCTEST_CHECK_THROWS(scene.removeEntity(2));
        DOCTEST_CHECK(scene.count() == 0);
        for(auto& node : scene.Graph()) {
            DOCTEST_CHECK(node.entity.id() == id::invalid);
        }
    }

    SUBCASE("Adding fist entity again") {
        DOCTEST_CHECK_THROWS(scene.newEntity());
        DOCTEST_CHECK(scene.count() == 1);
        DOCTEST_CHECK(scene.root().entity.id() == 3);
    }
}

TEST_SUITE_END();

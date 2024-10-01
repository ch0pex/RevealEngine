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

TEST_CASE("Create Entity") {
    SUBCASE("First entity") {
        Entity entity = scene.NewEntity();
        DOCTEST_CHECK(entity.IsAlive());
        DOCTEST_CHECK(entity.Id() == 0);
    }

    SUBCASE("Second entity") {
        Entity entity = scene.NewEntity();
        DOCTEST_CHECK(entity.IsAlive());
        DOCTEST_CHECK(entity.Id() == 1);
    }

    SUBCASE("Remove first entity") {
        scene.RemoveEntity(0);
        DOCTEST_CHECK(scene.Graph().at(0).entity.Id() == id::invalid);
        DOCTEST_CHECK(scene.Graph().at(1).prev.Id() == id::invalid);
    }

    SUBCASE("Third entity") {
        Entity entity = scene.NewEntity();
        DOCTEST_CHECK(entity.IsAlive());
        DOCTEST_CHECK(entity.Id() == 2);
        DOCTEST_CHECK(scene.Count() == 2);
    }

    SUBCASE("Remove all entities") {
        scene.RemoveEntity(1);
        scene.RemoveEntity(2);
        DOCTEST_CHECK(scene.Count() == 0);
        for(auto& node : scene.Graph()) {
            DOCTEST_CHECK(node.entity.Id() == id::invalid);
        }
    }

    SUBCASE("Adding fist entity again") {
        scene.NewEntity();
        DOCTEST_CHECK(scene.Count() == 1);
        DOCTEST_CHECK(scene.Root().entity.Id() == 3);
    }


}

TEST_SUITE_END();

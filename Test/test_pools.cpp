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
#include <doctest/doctest.h>


using namespace reveal3d;
using namespace reveal3d::core;

DOCTEST_TEST_SUITE_BEGIN("Components");

DOCTEST_TEST_CASE("Transform pool") { GenericPool<transform::Pool> transform_pool; }

DOCTEST_TEST_CASE("Geometry pool") { }

DOCTEST_TEST_CASE("Script pool") { }

DOCTEST_TEST_CASE("Light pool") { }

DOCTEST_TEST_CASE("RigidBody pool") { }

DOCTEST_TEST_SUITE_END();

/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file test_ecs.cpp
 * @version 1.0
 * @date 09/09/2025
 * @brief Short description
 *
 * Longer description
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "engine/scene/scene.hpp"


DOCTEST_TEST_SUITE_BEGIN("Ecs");

DOCTEST_TEST_CASE("Constructor") { rflect3d::Scene {}; }

DOCTEST_TEST_SUITE_END();

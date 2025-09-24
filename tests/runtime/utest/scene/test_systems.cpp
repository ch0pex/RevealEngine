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


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "engine/scene/components.hpp"


DOCTEST_TEST_SUITE_BEGIN("Ecs - Systems");

DOCTEST_TEST_CASE_TEMPLATE("Systems", T, ecs::data::Metadata) { }


DOCTEST_TEST_CASE_TEMPLATE("GPU Systems", T, ecs::data::Transform) {
  ecs::GPUSystem<T> system {};
  id::Factory<rflect3d::id_t, u32> factory {};

  system.add(factory.create());
}


DOCTEST_TEST_SUITE_END();

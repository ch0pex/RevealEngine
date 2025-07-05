/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file scene.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief ECS
 *
 */

#pragma once

#include "components.hpp"
#include "entity.hpp"
#include "systems.hpp"

namespace rflect3d {

// clang-format off
using Scene = Ecs<ecs::Entity>; // clang-format on

} // namespace rflect3d

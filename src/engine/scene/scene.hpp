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

// #include "components.hpp"
// #include "systems.hpp"

#include "engine/scene/ecs.hpp"
#include "engine/scene/entity.hpp"

namespace rflect3d {

using Scene = Ecs<ecs::Entity>;

} // namespace rflect3d

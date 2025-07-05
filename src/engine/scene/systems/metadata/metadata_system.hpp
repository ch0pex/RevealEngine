/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file metadata_system.hpp
 * @version 1.0
 * @date 01/07/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "metadata_data.hpp"
#include "scene/systems/system.hpp"

namespace rflect3d::ecs::systems {

struct Metadata : ecs::System<data::Metadata> { };

} // namespace rflect3d::ecs::systems

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file transform_system.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/scene/components/system.hpp"
#include "engine/scene/components/transform/transform_data.hpp"

namespace rflect3d::ecs {

class TransformSystem : public System<data::Transform> { };

} // namespace rflect3d::ecs

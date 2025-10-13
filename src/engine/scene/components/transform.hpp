/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file transform_proxy.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/math/matrix.hpp"
#include "engine/math/vector.hpp"

#include "engine/scene/components/component.hpp"
#include "engine/scene/systems/core/gpu_system.hpp"

namespace rflect3d::ecs {

namespace data {

/**
 * Local transform data structure
 */
struct LocalTransform {
  math::vec3 position;
  math::vec3 rotation;
  math::vec3 scale;
};

/**
 * Transform data structure compatible with
 * rflect containers, this allows storing easily this data as SoA
 */
struct Transform {
  DEFINE_COMPONENT_PROXY(local, world_matrix, inverse_matrix);
  LocalTransform local;
  math::mat4 world_matrix;
  math::mat4 inverse_matrix;
};

} // namespace data

using Transform = core_component<data::Transform, GPUSystem>;

} // namespace rflect3d::ecs

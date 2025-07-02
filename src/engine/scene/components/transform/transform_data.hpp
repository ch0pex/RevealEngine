/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file transform_data.hpp
 * @version 1.0
 * @date 01/07/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once


#include "engine/math/math.hpp"

#include <rflect/containers/proxy.hpp>

namespace rflect3d::ecs::data {

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
  DEFINE_PROXY(local, world_matrix, inverse_matrix);

  LocalTransform local;
  math::mat4 world_matrix;
  math::mat4 inverse_matrix;
};

} // namespace rflect3d::ecs::data

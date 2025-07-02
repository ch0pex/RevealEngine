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

#include "engine/scene/components/component.hpp"
#include "transform_data.hpp"

namespace rflect3d::ecs {

/**
 * Transform Component User API
 */
struct Transform : Component<data::Transform> {
  using Component::Component;

  void position(math::vec3 const position) const { data().local().position = position; }

  math::vec3 position() const { return data().local().position; }

  void rotation(math::vec3 const rotation) const { data().local().rotation = rotation; }

  math::vec3 rotation() const { return data().local().rotation; }

  void scale(math::vec3 const scale) const { data().local().rotation = scale; }

  math::vec3 scale() const { return data().local().rotation; }

  math::mat4 const& world() const { return data().world_matrix(); }

  math::mat4 const& inverseWorld() const { return data().inverse_matrix(); }
};

} // namespace rflect3d::ecs

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file material.hpp
 * @version 1.0
 * @date 11/03/2024
 * @brief Material component
 *
 * Material component
 */

#include "component.hpp"

#include <set>
#include <span>

#include <ranges>

namespace rflect3d::core {

struct Material : Component<Material> {

  // *** Type Traits ***
  // using pool_type = material::Pool;
  // using init_info = pool_type::init_info;

  using Component::Component;

  void diffuseColor(math::vec4 const color) const {
    pool().material(id_).base_color = color;
    setDirty();
  }

  void fresnel(math::vec3 const fresnel) const {
    pool().material(id_).fresnel = fresnel;
    setDirty();
  }

  void materialTransform(math::mat4 const& transform) const {
    pool().material(id_).transform = transform;
    setDirty();
  }

  void roughness(f32 const roughness) const {
    pool().material(id_).roughness = roughness;
    setDirty();
  }
};

// template<>
// inline void GenericPool<Material::pool_type>::update(Scene& scene) {
//   for (auto it = this->dirty_ids_.begin(); it != this->dirty_ids_.end();) {
//     if (this->dirties_.at(id::index(*it)) == 0) {
//       it = this->dirty_ids_.erase(it);
//     }
//     else {
//       ++it;
//     }
//   }
// }

} // namespace rflect3d::core

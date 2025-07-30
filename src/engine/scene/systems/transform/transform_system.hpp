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

#include "engine/scene/systems/system.hpp"
#include "transform_data.hpp"

namespace rflect3d::ecs::systems {

using Transform = GpuComponentContainer<data::Transform>;

// class Transform {
//
//   void add(id_t const entity_id, data_type const& component = {}) { }
//
//   void remove(id_t const entity_id) { }
//
//   [[nodiscard]] id_t entity_id(index_t const index) const { return transform_data.at(index); }
//
//   [[nodiscard]] u32 count() const { return transform_data.count(); }
//
//   auto at(id_t const entity_id) { return transform_data.at(entity_id); }
//
//   auto at(index_t const index) { return transform_data.at(index); }
//
//   template<typename Self>
//   auto begin(this Self&& self) {
//     return std::forward<Self>(self).transform_data.begin();
//   }
//
//   template<typename Self>
//   auto end(this Self&& self) {
//     return std::forward<Self>(self).transform_data.end();
//   }
//
// private:
//   System<data::Transform> transform_data;
// }

} // namespace rflect3d::ecs::systems

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file component.hpp
 * @version 1.0
 * @date 15/12/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/scene/entity.hpp"
#include "engine/scene/systems/data_types.hpp"

namespace rflect3d::ecs {

/**
 * Base Component template class
 *
 * @note benchmark to store the proxy_type instead of index,
 * having a bigger class but less indirection maybe is better
 */
template<typename System>
class Component {
public:
  // *** Type traits ***
  using system_type = System;
  using data_type   = system_type::data_type;
  using proxy_type  = proxy_component<data_type>;

  // *** Constructors ***

  Component(Ecs<Entity>& ecs, index_t const index) : index_(index), ecs_(&ecs) { }

  // *** Member functions ***
  [[nodiscard]] Entity entity() const {
    auto entity_id = system().entity_id(index_);
    return {*ecs_, entity_id};
  }

protected:
  [[nodiscard]] proxy_type data() const { return system().at(index_); }

  [[nodiscard]] system_type& system() const { return ecs_->system<Component>(); }

private:
  index_t index_;
  Ecs<Entity>* ecs_;
};

} // namespace rflect3d::ecs

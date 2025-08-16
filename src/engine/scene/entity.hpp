/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file entity.hpp
 * @version 1.0
 * @date 06/02/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "engine/core/data_types/id.hpp"
#include "engine/scene/ecs.hpp"

namespace rflect3d::ecs {

class Entity {
public:
  // TODO constructor key idiom
  Entity(Ecs<Entity>& ecs, id_t const id) : identifier(id), ecs(std::addressof(ecs)) { }

  template<typename Component>
  auto component() {
    return ecs->system<Component>().at(identifier);
  }

  template<typename ComponentType>
  ComponentType addComponent() {
    return addComponent<ComponentType>(identifier);
  }

  template<typename Component>
  Component addComponent(typename Component::value_type const& value) {
    return ecs->system<Component>().add(value);
  }

  template<typename Component>
  void removeComponent() {
    return ecs->system<Component>().remove(identifier);
  }

  [[nodiscard]] auto id() const -> id_t { return identifier; }

  Entity parent() { }

  std::span<Entity> children() { }

private:
  id_t identifier;
  Ecs<Entity>* ecs;
};

} // namespace rflect3d::ecs

/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file draw_component.hpp
 * @version 1.0
 * @date 19/01/2025
 * @brief Draw and component UI generic template functions
 *
 */

#pragma once

#include "ecs/components/geometry.hpp"
#include "ecs/components/light.hpp"
#include "ecs/components/metadata.hpp"
#include "ecs/components/script.hpp"

namespace rflect3d::ui::entity_properties {

template<class T>
void addComponent(core::Entity entity, char const* name) {
  if (!entity.component<T>().isAlive() && ImGui::Selectable(name)) {
    entity.addComponent<T>();
  }
}

template<core::component T>
void drawComponent(core::Entity entity) {
  static u8 count = 0;
  if (count == 0) {
    logger(LogError) << "Unhandled component type in editor: " << typeid(T).name();
    ++count;
  }
}

} // namespace rflect3d::ui::entity_properties

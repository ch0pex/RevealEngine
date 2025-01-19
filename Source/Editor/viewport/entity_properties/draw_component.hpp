/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file draw_component.hpp
 * @version 1.0
 * @date 19/01/2025
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "core/components/geometry.hpp"
#include "core/components/light.hpp"
#include "core/components/metadata.hpp"
#include "core/components/script.hpp"

namespace reveal3d::ui::entity_properties {
template<class T>
void addComponent(core::Entity entity, char const* name) {
  if (!entity.component<T>().isAlive() && ImGui::Selectable(name)) {
    entity.addComponent<T>();
  }
}

template<>
inline void addComponent<core::Geometry>(core::Entity entity, char const* name) {
  if (!entity.component<core::Geometry>().isAlive() && ImGui::Selectable(name)) {
    if (auto const file {utl::open_file_dialog()}; file.has_value()) {
      if (auto mesh = content::import_obj(file.value()); mesh.has_value())
        entity.addComponent<core::Geometry>(std::move(mesh.value()));
    }
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

} // namespace reveal3d::ui::entity_properties

/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file draw_transform_component.hpp
 * @version 1.0
 * @date 19/01/2025
 * @brief Draw Transform Component UI
 *
 * Longer description
 */

#pragma once

#include "draw_component.hpp"

namespace reveal3d::ui::entity_properties {
template<>
inline void drawComponent<core::Transform>(core::Entity const entity) {
  if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent(10.0F);
    if (ImGui::CollapsingHeader("Local", ImGuiTreeNodeFlags_DefaultOpen)) {
      utl::draw_transform(entity.component<core::Transform>());
    }
    if (ImGui::CollapsingHeader("world")) {
      utl::draw_transform(entity.component<core::Transform>(), true);
    }
    ImGui::Unindent(10.0F);
  }
}
} // namespace reveal3d::ui::entity_properties

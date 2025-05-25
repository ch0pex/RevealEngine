/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file draw_light_component.hpp
 * @version 1.0
 * @date 10/02/2025
 * @brief Draw Light Component UI
 *
 */

#pragma once

#include "Editor/utils/components.hpp"
#include "draw_component.hpp"

namespace reveal3d::ui::entity_properties {

template<>
inline void drawComponent<core::Light>(core::Entity const entity) {
  auto const light = entity.component<core::Light>();
  if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent();
    if (ImGui::BeginTable("#light_properties", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("property", 0, 0.23F);
      ImGui::TableSetupColumn("set", 0, 0.77F);

      auto const& light_properties = light.properties();

      utl::table::color_edit4("Color", light_properties.color, [light](math::vec4 const val) { ligth.color(val); });

      ImGui::EndTable();
    }
    ImGui::Unindent();
  }
}


} // namespace reveal3d::ui::entity_properties

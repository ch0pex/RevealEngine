/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file draw_geometry_component.hpp
 * @version 1.0
 * @date 19/01/2025
 * @brief Geometry Component UI drawing logic
 *
 */

#pragma once

#include "draw_component.hpp"

namespace reveal3d::ui::entity_properties {

template<>
inline void drawComponent<core::Geometry>(core::Entity entity) {
  auto const geometry = entity.component<core::Geometry>();

  if (not entity.component<core::Geometry>().isAlive()) {
    return;
  }

  if (ImGui::CollapsingHeader("Geometry", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::PushItemWidth(-5);
    ImGui::Indent();
    if (ImGui::Button("Remove")) {
      entity.removeComponent<core::Geometry>();
    }

    if (ImGui::CollapsingHeader("Surface", ImGuiTreeNodeFlags_DefaultOpen)) {
      if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("property", 0, 0.23f);
        ImGui::TableSetupColumn("set", 0, 0.77f);

        auto const& [base_color, fresnel, roughness, transform] = geometry.material();

        utl::table::color_edit4("Base color", base_color, [geometry](math::vec4 const val) {
          geometry.diffuseColor(val);
        });
        utl::table::drag_float("Roughness", roughness, [geometry](f32 const val) { geometry.roughness(val); });
        utl::table::drag_float3("Fresnel", fresnel, [geometry](math::vec3 const val) { geometry.fresnel(val); });
        ImGui::EndTable();
      }
    }

    if (ImGui::CollapsingHeader("Visibility", ImGuiTreeNodeFlags_DefaultOpen)) {
      if (ImGui::BeginTable("#transform", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("property", 0, 0.23f);
        ImGui::TableSetupColumn("set", 0, 0.77f);
        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Is visible: ");
          ImGui::TableNextColumn();
          if (ImGui::Checkbox("##visibility", &geometry.subMeshes()[0].visible)) {
            entity.component<core::Geometry>().visibility(geometry.subMeshes()[0].visible);
          }
          ImGui::TableNextColumn();
        }
        ImGui::EndTable();
      }
    }
    ImGui::Unindent();
  }
}
} // namespace reveal3d::ui::entity_properties

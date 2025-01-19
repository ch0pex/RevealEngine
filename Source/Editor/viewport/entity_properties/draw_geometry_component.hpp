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

        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Base color");
          ImGui::TableNextColumn();
          if (ImGui::ColorEdit4("##basecolor", std::bit_cast<f32*>(&geometry.material().base_color))) {
            entity.component<core::Geometry>().diffuseColor(geometry.material().base_color);
          }
        }
        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Roughness");
          ImGui::TableNextColumn();
          if (ImGui::DragFloat("##roughness", std::bit_cast<f32*>(&geometry.material().roughness), 0.01f, 0.0f, 1.0f)) {
            entity.component<core::Geometry>().roughness(geometry.material().roughness);
          }
        }
        ImGui::TableNextColumn();
        {
          ImGui::AlignTextToFramePadding();
          ImGui::Text("Fresnel");
          ImGui::TableNextColumn();
          if (ImGui::DragFloat3("##fresnel", std::bit_cast<f32*>(&geometry.material().fresnel), 0.01f, 0.0f, 1.0f)) {
            entity.component<core::Geometry>().fresnel(geometry.material().fresnel);
          }
        }
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

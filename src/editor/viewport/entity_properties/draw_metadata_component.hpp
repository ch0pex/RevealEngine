/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file draw_metadata_component.hpp
 * @version 1.0
 * @date 19/01/2025
 * @brief Draw Metadata component UI
 *
 */

#pragma once

#include "draw_component.hpp"

#include <fmt/printf.h>


namespace reveal3d::ui::entity_properties {
template<>
inline void drawComponent<core::Metadata>(core::Entity const entity) {
  auto const metadata = entity.component<core::Metadata>();

  if (ImGui::CollapsingHeader("Metadata", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent(10.0F);
    if (ImGui::BeginTable("#metadata", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("name", 0, 0.23F);
      ImGui::TableSetupColumn("set", 0, 0.77F);

      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Name:");
        ImGui::TableNextColumn();
        ImGui::InputText("##name", metadata.name().data(), 15);
      }

      ImGui::EndTable();
    }

    if (ImGui::CollapsingHeader("More info")) {
      ImGui::TableNextColumn();
      {
        std::string const id = fmt::sprintf("0x%08X", entity.id());
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Entity ID: ");
        ImGui::SameLine();
        ImGui::Text("%s", id.c_str());
      }
      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Date:");
        ImGui::SameLine();
        ImGui::InputText("##date", metadata.date().data(), 15);
      }

      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Comment:");
        ImGui::TableNextColumn();
        ImGui::InputTextMultiline("##comment", metadata.comment().data(), 1024);
        ImGui::TableNextColumn();
      }
    }
    ImGui::Unindent(10.0F);
  }
}

} // namespace reveal3d::ui::entity_properties

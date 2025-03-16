/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file components.hpp
 * @version 1.0
 * @date 17/12/2024
 * @brief Imgui components
 *
 * Imgui simple components helper functions
 */

#pragma once

#include "imgui.hpp"
#include "table_components.hpp"

namespace reveal3d::ui::utl {


auto open_file_dialog() -> std::optional<std::string>;

inline void draw_transform(core::Transform transform, bool world = false) {
  math::vec3 pos;
  math::vec3 scale;
  math::vec3 rot;

  std::function<void(math::vec3)> setPos;
  std::function<void(math::vec3)> setRot;
  std::function<void(math::vec3)> setScale;

  if (world) {
    pos      = transform.worldPosition();
    scale    = transform.worldScale();
    rot      = transform.worldRotation();
    setPos   = [&transform](math::vec3 const pos) { transform.worldPosition(pos); };
    setRot   = [&transform](math::vec3 const rot) { transform.worldRotation(rot); };
    setScale = [&transform](math::vec3 const scale) { transform.worldScale(scale); };
  }
  else {
    pos      = transform.position();
    scale    = transform.scale();
    rot      = transform.rotation();
    setPos   = [&transform](math::vec3 const pos) { transform.position(pos); };
    setRot   = [&transform](math::vec3 const rot) { transform.rotation(rot); };
    setScale = [&transform](math::vec3 const scale) { transform.scale(scale); };
  }

  ImGui::Indent();
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.F, 0.F));
  if (ImGui::BeginTable("#entity_transform", 2, ImGuiTableFlags_SizingStretchProp)) {
    ImGui::TableSetupColumn("name", 0, 0.25F);
    ImGui::TableSetupColumn("set", 0, 0.65F);

    // Transform components
    table::draw_vec3("Translation", pos, setPos);
    table::draw_vec3("Rotation", rot, setRot);
    table::draw_vec3("Scale", scale, setScale);

    ImGui::EndTable();
  }
  ImGui::PopStyleVar();
  ImGui::Unindent();
}

} // namespace reveal3d::ui::utl

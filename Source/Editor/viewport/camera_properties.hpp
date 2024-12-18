/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file camera_properties.hpp
 * @version 1.0
 * @date 17/12/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

namespace reveal3d::ui::camera_properties {

void drawDragFloat(char const* name, auto getter, auto setter, f32 step = 1.f, f32 min = 0, f32 max = 0) {
  ImGui::TableNextColumn();
  {
    auto val = getter();
    ImGui::AlignTextToFramePadding();
    ImGui::Text(name);
    ImGui::TableNextColumn();
    if (ImGui::DragFloat(fmt::format("##{}", name).c_str(), &val, step, min, max)) {
      setter(val);
    }
  }
}


inline void draw(render::Camera& cam) {
  ImGui::Begin("Camera");
  if (ImGui::CollapsingHeader("View", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent();
    if (ImGui::BeginTable("#cam_view", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("property", 0, 0.23f);
      ImGui::TableSetupColumn("set", 0, 0.77f);

      drawDragFloat(
          "Fov", // Name
          [&c = cam]() { return c.fov(); }, // Getter
          [&c = cam](f32 const val) { c.fov(val); }, // Setter
          0.1, 45.0f, 120.0f // Step, min and max
      );
      drawDragFloat(
          "Near Plane", // Name
          [&c = cam]() { return c.nearPlane(); }, // Getter
          [&c = cam](f32 const val) { c.nearPlane(val); }, // Setter
          0.1f, 0.001f // Step and min
      );
      drawDragFloat(
          "Far Plane", // Name
          [&c = cam]() { return c.farPlane(); }, // Getter
          [&c = cam](f32 const val) { c.farPlane(val); }, // Setter
          0.1f, 0.001f // Step and min
      );

      ImGui::EndTable();
    }
    ImGui::Unindent();
  }

  if (ImGui::CollapsingHeader("Movement", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent();
    if (ImGui::BeginTable("#cam_movement", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("property", 0, 0.23f);
      ImGui::TableSetupColumn("set", 0, 0.77f);

      drawDragFloat(
          "Move Speed", // Name
          [&c = cam]() { return c.moveSpeed(); }, // Getter
          [&c = cam](f32 const val) { c.moveSpeed(val); }, // Setter
          0.2f, 0.05f, 100.0f // Step, min and max
      );

      drawDragFloat(
          "Sensitivity", // Name
          [&c = cam]() { return c.sensitivity(); }, // Getter
          [&c = cam](f32 const val) { c.sensitivity(val); }, // Setter
          0.01f, 0.01f, 5.f // Step, min and max
      );

      ImGui::EndTable();
    }
    ImGui::Unindent();
  }
  ImGui::End();
}

} // namespace reveal3d::ui::camera_properties

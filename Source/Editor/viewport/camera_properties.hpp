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

#include "Editor/utils/components.hpp"

namespace reveal3d::ui::camera_properties {

inline void draw(render::Camera& cam) {
  ImGui::Begin("Camera");
  if (ImGui::CollapsingHeader("View", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent();
    if (ImGui::BeginTable("#cam_view", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("property", 0, 0.23F);
      ImGui::TableSetupColumn("set", 0, 0.77F);

      utl::table::drag_float("Fov", cam.fov(), [&c = cam](f32 const val) { c.fov(val); }, {0.1, 45.0F, 120.0F});
      utl::table::drag_float(
          "Near Plane", cam.nearPlane(),
          [&c = cam](f32 const val) {
            if (val < c.farPlane() and val > 0) {
              c.nearPlane(val);
            }
          },
          {0.1F, 0.05F, cam.farPlane()}
      );
      utl::table::drag_float(
          "Far Plane", cam.farPlane(),
          [&c = cam](f32 const val) {
            if (val > c.nearPlane() and val > 0) {
              c.farPlane(val);
            }
          },
          {0.1F, cam.nearPlane()}
      );

      ImGui::EndTable();
    }
    ImGui::Unindent();
  }

  if (ImGui::CollapsingHeader("Movement", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::Indent();
    if (ImGui::BeginTable("#cam_movement", 2, ImGuiTableFlags_SizingStretchProp)) {
      ImGui::TableSetupColumn("property", 0, 0.23F);
      ImGui::TableSetupColumn("set", 0, 0.77F);

      utl::table::drag_float(
          "Move Speed", cam.moveSpeed(), [&c = cam](f32 const val) { c.moveSpeed(val); }, {0.2F, 0.05F, 100.0F}
      );

      utl::table::drag_float(
          "Sensitivity", cam.sensitivity(), [&c = cam](f32 const val) { c.sensitivity(val); }, {0.01F, 0.01F, 5.F}
      );

      ImGui::EndTable();
    }
    ImGui::Unindent();
  }
  ImGui::End();
}

} // namespace reveal3d::ui::camera_properties

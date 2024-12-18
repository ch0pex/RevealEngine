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

#include "core/components/transform.hpp"
#include "math/math.hpp"

namespace reveal3d::ui::utl {

inline auto open_file_dialog() -> std::optional<std::string> {
  OPENFILENAME ofn;
  std::array<char, 260> sz_file;
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize     = sizeof(ofn);
  ofn.hwndOwner       = nullptr; // Si tienes un handle a la ventana de tu aplicación, úsalo aquí
  ofn.lpstrFile       = sz_file.data();
  ofn.lpstrFile[0]    = '\0';
  ofn.nMaxFile        = sizeof(sz_file) / sizeof(char);
  ofn.lpstrFilter     = "All\0*.*\0Text\0*.TXT\0";
  ofn.nFilterIndex    = 1;
  ofn.lpstrFileTitle  = nullptr;
  ofn.nMaxFileTitle   = 0;
  ofn.lpstrInitialDir = nullptr;
  ofn.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  // Abre el diálogo de archivo
  if (GetOpenFileName(&ofn) != TRUE) {
    logger(LogError) << "Error opening file: " << ofn.lpstrFile;
    return std::nullopt;
  }

  logger(LogInfo) << "Selected file: " << ofn.lpstrFile;
  return ofn.lpstrFile;
}


inline bool draw_vec3(
    std::string_view const label, math::xvec3& values, f32 const reset_value = 0.0F, f32 const column_width = 100.0,
    f32 const rate = 0.1F, f32 const min = 0.0F
) {
  bool changes   = false;
  std::span vals = {reinterpret_cast<f32*>(&values), 3};
  ImGui::PushID(label.data());

  f32 const avail_width = (ImGui::GetContentRegionAvail().x / 3.0F) - 9.0f;
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 {0, 0});

  //    f32 lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
  constexpr ImVec2 button_size = {5.0F, 15.0F};

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.8F, 0.1F, 0.15F, 1.0F});
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.9F, 0.2F, 0.2F, 1.0F});
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.8F, 0.1F, 0.15F, 1.0F});
  //    ImGui::PushFont(boldFont);
  if (ImGui::Button("###X", button_size)) {
    vals[0] = reset_value;
    changes |= true;
  }
  //    ImGui::PopFont();
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  ImGui::PushItemWidth(avail_width);
  changes |= ImGui::DragFloat("##X", &vals[0], rate, min, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.2f, 0.7f, 0.2f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.3f, 0.8f, 0.3f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.2f, 0.7f, 0.2f, 1.0f});
  //    ImGui::PushFont(boldFont);
  if (ImGui::Button("Y", button_size)) {
    vals[1] = reset_value;
    changes |= true;
  }
  //    ImGui::PopFont();
  ImGui::PopStyleColor(3);
  ImGui::SameLine();
  ImGui::PushItemWidth(avail_width);
  changes |= ImGui::DragFloat("##Y", &vals[1], rate, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 {0.1f, 0.25f, 0.8f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 {0.2f, 0.35f, 0.9f, 1.0f});
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 {0.1f, 0.25f, 0.8f, 1.0f});
  //    ImGui::PushFont(boldFont);
  if (ImGui::Button("Z", button_size)) {
    vals[2] = reset_value;
    changes |= true;
  }
  //    ImGui::PopFont();
  ImGui::PopStyleColor(3);
  ImGui::SameLine();

  ImGui::PushItemWidth(avail_width);
  changes |= ImGui::DragFloat("##Z", &vals[2], rate, 0.0f, 0.0f, "%.2f");
  ImGui::PopItemWidth();

  ImGui::PopStyleVar();

  ImGui::PopID();
  return changes;
}

inline void draw_transform(core::Transform transform, bool world = false) {
  math::xvec3 pos;
  math::xvec3 scale;
  math::xvec3 rot;

  std::function<void(math::xvec3)> setPos;
  std::function<void(math::xvec3)> setRot;
  std::function<void(math::xvec3)> setScale;

  if (world) {
    pos      = transform.worldPosition();
    scale    = transform.worldScale();
    rot      = transform.worldRotation();
    setPos   = [&transform](math::xvec3 const pos) { transform.worldPosition(pos); };
    setRot   = [&transform](math::xvec3 const rot) { transform.worldRotation(rot); };
    setScale = [&transform](math::xvec3 const scale) { transform.worldScale(scale); };
  }
  else {
    pos      = transform.position();
    scale    = transform.scale();
    rot      = transform.rotation();
    setPos   = [&transform](math::xvec3 const pos) { transform.position(pos); };
    setRot   = [&transform](math::xvec3 const rot) { transform.rotation(rot); };
    setScale = [&transform](math::xvec3 const scale) { transform.scale(scale); };
  }

  ImGui::Indent();
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.f, 0.f));
  if (ImGui::BeginTable("#transform", 3, ImGuiTableFlags_SizingStretchProp)) {
    ImGui::TableSetupColumn("name", 0, 0.25f);
    ImGui::TableSetupColumn("set", 0, 0.65f);
    ImGui::TableSetupColumn("reset", 0, 0.1f);

    ImGui::TableNextColumn();
    {
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Translation:");
        ImGui::TableNextColumn();

        if (draw_vec3("translation", pos))
          setPos(pos);

        ImGui::TableNextColumn();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
        //                std::string resetLabel = std::string(ICON_FA_UNDO) + "##ResetTranslation";
        if (ImGui::Button("reset##Pos"))
          setPos({0.0, 0.0f, 0.0f});

        ImGui::PopStyleColor();
      }
      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Rotation:");
        ImGui::TableNextColumn();

        if (draw_vec3("rotation", rot))
          setRot(rot);

        ImGui::TableNextColumn();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
        //                std::string resetLabel = std::string(ICON_FA_UNDO) + "##ResetRotation";
        if (ImGui::Button("reset##Rot"))
          setRot({0.0, 0.0f, 0.0f});
        ImGui::PopStyleColor();
      }
      ImGui::TableNextColumn();
      {
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Scale:");
        ImGui::TableNextColumn();

        if (draw_vec3("scale", scale, 1.0f))
          setScale(scale);

        ImGui::TableNextColumn();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0));
        //                std::string resetLabel = std::string(ICON_FA_UNDO) + "##ResetScale";
        if (ImGui::Button("reset##scale"))
          setScale({1.0, 1.0f, 1.0f});

        ImGui::PopStyleColor();
      }
    }
    ImGui::EndTable();
  }
  ImGui::PopStyleVar();
  ImGui::Unindent();
}

} // namespace reveal3d::ui::utl

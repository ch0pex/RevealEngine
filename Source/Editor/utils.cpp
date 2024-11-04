/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file utils.cpp
 * @version 1.0
 * @date 06/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "utils.hpp"
#include <functional>
#include <print>
#include "imgui.h"

namespace reveal3d::ui::utl {

bool draw_vec3(
    const std::string_view label, math::xvec3& values, const f32 reset_value, f32 column_width, const f32 rate,
    const f32 min
) {
  bool changes     = false;
  auto* const vals = reinterpret_cast<f32*>(&values);
  ImGui::PushID(label.data());

  const f32 avail_width = (ImGui::GetContentRegionAvail().x / 3.0F) - 9.0f;
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

void draw_transform(core::Transform transform, bool world) {
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
    setPos   = [&transform](const math::xvec3 pos) { transform.worldPosition(pos); };
    setRot   = [&transform](const math::xvec3 rot) { transform.worldRotation(rot); };
    setScale = [&transform](const math::xvec3 scale) { transform.worldScale(scale); };
  }
  else {
    pos      = transform.position();
    scale    = transform.scale();
    rot      = transform.rotation();
    setPos   = [&transform](const math::xvec3 pos) { transform.position(pos); };
    setRot   = [&transform](const math::xvec3 rot) { transform.rotation(rot); };
    setScale = [&transform](const math::xvec3 scale) { transform.scale(scale); };
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

void set_style() {
  ImVec4* colors                         = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text]                  = ImVec4(1.00F, 1.00F, 1.00F, 1.00F);
  colors[ImGuiCol_TextDisabled]          = ImVec4(0.50F, 0.50F, 0.50F, 1.00F);
  colors[ImGuiCol_WindowBg]              = ImVec4(0.10F, 0.10F, 0.10F, 1.00F);
  colors[ImGuiCol_ChildBg]               = ImVec4(0.00F, 0.00F, 0.00F, 0.00F);
  colors[ImGuiCol_PopupBg]               = ImVec4(0.19F, 0.19F, 0.19F, 0.92F);
  colors[ImGuiCol_Border]                = ImVec4(0.19F, 0.19F, 0.19F, 0.29F);
  colors[ImGuiCol_BorderShadow]          = ImVec4(0.00F, 0.00F, 0.00F, 0.24F);
  colors[ImGuiCol_FrameBg]               = ImVec4(0.05F, 0.05F, 0.05F, 0.54F);
  colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.19F, 0.19F, 0.19F, 0.54F);
  colors[ImGuiCol_FrameBgActive]         = ImVec4(0.20F, 0.22F, 0.23F, 1.00F);
  colors[ImGuiCol_TitleBg]               = ImVec4(0.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_TitleBgActive]         = ImVec4(0.06F, 0.06F, 0.06F, 1.00F);
  colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_MenuBarBg]             = ImVec4(0.14F, 0.14F, 0.14F, 1.00F);
  colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.05F, 0.05F, 0.05F, 0.54F);
  colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.34F, 0.34F, 0.34F, 0.54F);
  colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.40F, 0.40F, 0.40F, 0.54F);
  colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.56F, 0.56F, 0.56F, 0.54F);
  colors[ImGuiCol_CheckMark]             = ImVec4(0.33F, 0.67F, 0.86F, 1.00F);
  colors[ImGuiCol_SliderGrab]            = ImVec4(0.34F, 0.34F, 0.34F, 0.54F);
  colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.56F, 0.56F, 0.56F, 0.54F);
  colors[ImGuiCol_Button]                = ImVec4(0.05F, 0.05F, 0.05F, 0.54F);
  colors[ImGuiCol_ButtonHovered]         = ImVec4(0.19F, 0.19F, 0.19F, 0.54F);
  colors[ImGuiCol_ButtonActive]          = ImVec4(0.20F, 0.22F, 0.23F, 1.00F);
  colors[ImGuiCol_Header]                = ImVec4(0.00F, 0.00F, 0.00F, 0.52F);
  colors[ImGuiCol_HeaderHovered]         = ImVec4(0.00F, 0.00F, 0.00F, 0.36F);
  colors[ImGuiCol_HeaderActive]          = ImVec4(0.20F, 0.22F, 0.23F, 0.33F);
  colors[ImGuiCol_Separator]             = ImVec4(0.28F, 0.28F, 0.28F, 0.29F);
  colors[ImGuiCol_SeparatorHovered]      = ImVec4(0.44F, 0.44F, 0.44F, 0.29F);
  colors[ImGuiCol_SeparatorActive]       = ImVec4(0.40F, 0.44F, 0.47F, 1.00F);
  colors[ImGuiCol_ResizeGrip]            = ImVec4(0.28F, 0.28F, 0.28F, 0.29F);
  colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.44F, 0.44F, 0.44F, 0.29F);
  colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.40F, 0.44F, 0.47F, 1.00F);
  colors[ImGuiCol_Tab]                   = ImVec4(0.00F, 0.00F, 0.00F, 0.52F);
  colors[ImGuiCol_TabHovered]            = ImVec4(0.14F, 0.14F, 0.14F, 1.00F);
  colors[ImGuiCol_TabActive]             = ImVec4(0.20F, 0.20F, 0.20F, 0.36F);
  colors[ImGuiCol_TabUnfocused]          = ImVec4(0.00F, 0.00F, 0.00F, 0.52F);
  colors[ImGuiCol_TabUnfocusedActive]    = ImVec4(0.14F, 0.14F, 0.14F, 1.00F);
  colors[ImGuiCol_DockingPreview]        = ImVec4(0.33F, 0.67F, 0.86F, 1.00F);
  colors[ImGuiCol_DockingEmptyBg]        = ImVec4(1.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_PlotLines]             = ImVec4(1.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_PlotHistogram]         = ImVec4(1.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_TableHeaderBg]         = ImVec4(0.00F, 0.00F, 0.00F, 0.52F);
  colors[ImGuiCol_TableBorderStrong]     = ImVec4(0.00F, 0.00F, 0.00F, 0.52F);
  colors[ImGuiCol_TableBorderLight]      = ImVec4(0.28F, 0.28F, 0.28F, 0.29F);
  colors[ImGuiCol_TableRowBg]            = ImVec4(0.00F, 0.00F, 0.00F, 0.00F);
  colors[ImGuiCol_TableRowBgAlt]         = ImVec4(1.00F, 1.00F, 1.00F, 0.06F);
  colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.20F, 0.22F, 0.23F, 1.00F);
  colors[ImGuiCol_DragDropTarget]        = ImVec4(0.33F, 0.67F, 0.86F, 1.00F);
  colors[ImGuiCol_NavHighlight]          = ImVec4(1.00F, 0.00F, 0.00F, 1.00F);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00F, 0.00F, 0.00F, 0.70F);
  colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(1.00F, 0.00F, 0.00F, 0.20F);
  colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(1.00F, 0.00F, 0.00F, 0.35F);

  ImGuiStyle& style       = ImGui::GetStyle();
  style.WindowPadding     = ImVec2(8.00F, 8.00F);
  style.FramePadding      = ImVec2(5.00F, 2.00F);
  style.CellPadding       = ImVec2(6.00F, 6.00F);
  style.ItemSpacing       = ImVec2(6.00F, 6.00F);
  style.ItemInnerSpacing  = ImVec2(6.00F, 6.00F);
  style.TouchExtraPadding = ImVec2(0.00F, 0.00F);
  style.IndentSpacing     = 25;
  style.ScrollbarSize     = 15;
  style.GrabMinSize       = 10;
  style.WindowBorderSize  = 1;
  style.ChildBorderSize   = 1;
  style.PopupBorderSize   = 1;
  //    style.FrameBorderSize                   = 1;
  style.TabBorderSize     = 1;
  style.WindowRounding    = 7;
  style.ChildRounding     = 4;
  style.FrameRounding     = 3;
  style.PopupRounding     = 4;
  style.ScrollbarRounding = 9;
  style.GrabRounding      = 3;
  style.LogSliderDeadzone = 4;
  style.TabRounding       = 4;
}

std::string open_file_dialog() {

  OPENFILENAME ofn;
  char sz_file[260];
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize     = sizeof(ofn);
  ofn.hwndOwner       = nullptr; // Si tienes un handle a la ventana de tu aplicación, úsalo aquí
  ofn.lpstrFile       = sz_file;
  ofn.lpstrFile[0]    = '\0';
  ofn.nMaxFile        = sizeof(sz_file) / sizeof(char);
  ofn.lpstrFilter     = "All\0*.*\0Text\0*.TXT\0";
  ofn.nFilterIndex    = 1;
  ofn.lpstrFileTitle  = nullptr;
  ofn.nMaxFileTitle   = 0;
  ofn.lpstrInitialDir = nullptr;
  ofn.Flags           = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  // Abre el diálogo de archivo
  if (GetOpenFileName(&ofn) == TRUE) {
    logger(LogInfo) << "Selected file: {}" << ofn.lpstrFile;
  }
  else {
    logger(LogError) << "Error opening file: " << ofn.lpstrFile;
  }
  return ofn.lpstrFile;
}

} // namespace reveal3d::ui::utl

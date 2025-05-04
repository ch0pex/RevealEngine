/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file styling.hpp
 * @version 1.0
 * @date 17/12/2024
 * @brief ImGui styling
 *
 * ImGui editor styling functions
 */

#pragma once

#include "imgui.hpp"

namespace reveal3d::ui::utl {

inline void set_style() {

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

} // namespace reveal3d::ui::utl

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file Console.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Console log UI component
 *
 */

#pragma once

#include "engine/core/core.hpp"

#include <imgui.h>

namespace rflect3d::ui::console {

namespace detail {

template<LogLevel level>
void logger_console(std::string_view const console_name) {
  if (ImGui::BeginTabItem(std::string(console_name).c_str())) {
    ImGui::TextUnformatted(Logger<level>::log().c_str());

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
      ImGui::SetScrollHereY(1.0F);

    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
      ImGui::OpenPopup("PopupRightClick");
    }

    if (ImGui::BeginPopup("PopupRightClick")) {
      if (ImGui::MenuItem("clear")) {
        Logger<level>::clear();
      }
      ImGui::EndPopup();
    }
    ImGui::EndTabItem();
  }
}

} // namespace detail

inline void draw() {
  ImGui::Begin("Console");

  if (ImGui::BeginTabBar("Console TabBar")) {
    detail::logger_console<LogAll>("All");
    detail::logger_console<LogInfo>("Info");
    detail::logger_console<LogWarning>("Warning");
    detail::logger_console<LogError>("Error");
    ImGui::EndTabBar();
  }

  ImGui::End();
}


} // namespace rflect3d::ui::console

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file MenuBar.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "menu_bar.hpp"
#include "Editor/utils.hpp"
#include "content/content.hpp"
#include "core/scene.hpp"

namespace reveal3d::ui {

MenuBar::MenuBar() { }

void MenuBar::Draw() {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      // Disabling fullscreen would allow the window to be moved to the front of other windows,
      // which we can't undo at the moment without finer window depth/z control.
      ImGui::MenuItem("new", nullptr, nullptr);
      ImGui::MenuItem("Open", nullptr, nullptr);
      ImGui::MenuItem("Recent Projects", nullptr, nullptr);
      ImGui::MenuItem("Close Project", nullptr, nullptr);
      ImGui::Separator();
      ImGui::MenuItem("Save", nullptr, nullptr);
      ImGui::MenuItem("Save as", nullptr, nullptr);
      ImGui::Separator();
      if (ImGui::MenuItem("Import Obj", nullptr, nullptr)) {
        std::string const file = utl::open_file_dialog();
        core::Entity entity    = core::scene.newEntity();
        if (auto obj = content::import_obj(file.c_str()); obj.has_value()) {
          entity.addComponent<core::Geometry>(std::move(obj.value()));
        }
        else {
          logger(LogError) << "Import obj failed";
        }
      }

      ImGui::MenuItem("Export Obj", nullptr, nullptr);
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("view")) {
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Settings")) {
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
  }
}

} // namespace reveal3d::ui

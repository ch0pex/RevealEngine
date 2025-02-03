/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file MenuBar.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Menu bar UI component
 *
 */

#pragma once

#include "../utils/components.hpp"
#include "../utils/imgui.hpp"
#include "content/content.hpp"
#include "core/components/geometry.hpp"

namespace reveal3d::ui::menu_bar {

namespace detail {

template<typename... Args>
void beginMenu(char const* name, auto draw_menu, Args... args) {
  if (ImGui::BeginMenu(name)) {
    draw_menu(std::forward<Args>(args)...);
    ImGui::EndMenu();
  }
}

constexpr auto draw_file = [](core::Scene* scene) {
  ImGui::MenuItem("New", nullptr, nullptr);
  ImGui::MenuItem("Open", nullptr, nullptr);
  ImGui::MenuItem("Recent Projects", nullptr, nullptr);
  ImGui::MenuItem("Close Project", nullptr, nullptr);
  ImGui::Separator();
  ImGui::MenuItem("Save", nullptr, nullptr);
  ImGui::MenuItem("Save as", nullptr, nullptr);
  ImGui::Separator();
  if (ImGui::MenuItem("Import Obj", nullptr, nullptr)) {
    std::string const file = utl::open_file_dialog().value();
    core::Entity entity    = {scene, scene->newEntity()};
    if (auto obj = content::import_obj(file.c_str()); obj.has_value()) {
      entity.addComponent<core::Geometry>(std::move(obj.value()));
    }
    else {
      logger(LogError) << "Import obj failed";
    }
  }

  ImGui::MenuItem("Export Obj", nullptr, nullptr);
};


} // namespace detail

inline void draw(core::Scene& scene) {
  if (ImGui::BeginMenuBar()) {
    beginMenu("File", detail::draw_file, &scene);
    detail::beginMenu("Edit", []() {});
    detail::beginMenu("View", [] {});
    detail::beginMenu("Settings", [] {});
    detail::beginMenu("Help", [] {});
    ImGui::EndMenuBar();
  }
}


} // namespace reveal3d::ui::menu_bar

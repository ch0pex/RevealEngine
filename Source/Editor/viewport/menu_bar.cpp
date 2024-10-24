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
#include "core/scene.hpp"
#include "content/content.hpp"

namespace reveal3d::ui {

MenuBar::MenuBar() {

}

void MenuBar::Draw() {
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("new", NULL, nullptr);
            ImGui::MenuItem("Open", NULL, nullptr);
            ImGui::MenuItem("Recent Projects", NULL, nullptr);
            ImGui::MenuItem("Close Project", NULL, nullptr);
            ImGui::Separator();
            ImGui::MenuItem("Save", NULL, nullptr);
            ImGui::MenuItem("Save as", NULL, nullptr);
            ImGui::Separator();
            if (ImGui::MenuItem("Import Obj", NULL, nullptr)) {
                std::string file = utl::open_file_dialog();
                core::Entity entity = core::scene.newEntity();
                entity.addComponent<core::Geometry>(content::import_obj(file.c_str()));
            }

            ImGui::MenuItem("Export Obj", NULL, nullptr);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {ImGui::EndMenu();}
        if (ImGui::BeginMenu("view")) {ImGui::EndMenu();}
        if (ImGui::BeginMenu("Settings")) {ImGui::EndMenu();}
        if (ImGui::BeginMenu("Help")) {ImGui::EndMenu();}
        ImGui::EndMenuBar();
    }
}

}

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
#include "core/entity.hpp"

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
            ImGui::MenuItem("New", NULL, nullptr);
            ImGui::MenuItem("Open", NULL, nullptr);
            ImGui::MenuItem("Recent Projects", NULL, nullptr);
            ImGui::MenuItem("Close Project", NULL, nullptr);
            ImGui::Separator();
            ImGui::MenuItem("Save", NULL, nullptr);
            ImGui::MenuItem("Save as", NULL, nullptr);
            ImGui::Separator();
            if (ImGui::MenuItem("Import Obj", NULL, nullptr)) {
                OPENFILENAMEW ofn;
                wchar_t szFile[260];
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;  // Si tienes un handle a la ventana de tu aplicación, úsalo aquí
                ofn.lpstrFile = szFile;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t);
                ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                // Abre el diálogo de archivo
                if (GetOpenFileNameW(&ofn) == TRUE) {
                    wprintf(L"Selected file: %s\n", ofn.lpstrFile);
                } else {
                    printf("Dialog was cancelled or an error occurred.\n");
                }
                const std::wstring file = ofn.lpstrFile;
                core::scene.AddEntityFromObj(file.c_str());
            }

            ImGui::MenuItem("Export Obj", NULL, nullptr);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {ImGui::EndMenu();}
        if (ImGui::BeginMenu("View")) {ImGui::EndMenu();}
        if (ImGui::BeginMenu("Settings")) {ImGui::EndMenu();}
        if (ImGui::BeginMenu("Help")) {ImGui::EndMenu();}
        ImGui::EndMenuBar();
    }
}

}

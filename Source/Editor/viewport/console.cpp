/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file Console.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "console.hpp"

#include "IMGUI/imgui.h"

namespace reveal3d::ui {

Console::Console() {

}


void Console::Draw(Timer& timer) {
    ImGui::Begin("Console");


    if (ImGui::BeginTabBar("Console TabBar")) {
        if (ImGui::BeginTabItem("Profiling")) {
            const u32 fps = timer.Fps();
            stats_.fps = "Fps: " + std::to_string(fps) + "\n";
            stats_.ms = "FrameTime: " + std::to_string(timer.FrameTime() * 1000) + "\n";
            const std::string stats = stats_.fps + stats_.ms;
            ImGui::TextUnformatted(stats.c_str());
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Debug")) {
            ImGui::TextUnformatted(Logger::Log(logDEBUG).c_str());
            RightClick(logDEBUG);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Warnings")) {
            ImGui::TextUnformatted(Logger::Log(logWARNING).c_str());
            RightClick(logWARNING);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Errors")) {
            ImGui::TextUnformatted(Logger::Log(logERROR).c_str());
            RightClick(logERROR);
            ImGui::EndTabItem();
        }


        ImGui::EndTabBar();
    }


    ImGui::End();
}

void Console::RightClick(LogLevel log) {
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
        ImGui::OpenPopup("PopupClicDerecho");
    }

    if (ImGui::BeginPopup("PopupClicDerecho")) {
        if (ImGui::MenuItem("Clear")) {
            Logger::Clear(log);
        }
        ImGui::EndPopup();
    }
}

}

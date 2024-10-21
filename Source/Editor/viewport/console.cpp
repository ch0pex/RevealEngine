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
            u32 fps = timer.averageFps();
            stats_.fps = "fps: " + std::to_string(fps) + "\n";
            stats_.frameTime = "Frametime: " + std::to_string(timer.frameTime() * 1000) + "\n";
            stats_.deltaTime = "Deltatime: " + std::to_string(timer.deltaTime() * 1000) + "\n";
            const std::string stats = stats_.fps + stats_.frameTime + stats_.deltaTime;
            ImGui::TextUnformatted(stats.c_str());
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Debug")) {
            ImGui::TextUnformatted(Logger::log(logDEBUG).c_str());
            RightClick(logDEBUG);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Warnings")) {
            ImGui::TextUnformatted(Logger::log(logWARNING).c_str());
            RightClick(logWARNING);
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Errors")) {
            ImGui::TextUnformatted(Logger::log(logERROR).c_str());
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
        if (ImGui::MenuItem("clear")) {
            Logger::clear(log);
        }
        ImGui::EndPopup();
    }
}

}

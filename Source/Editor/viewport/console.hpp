/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file Console.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "common/logger.hpp"
#include "common/timer.hpp"

#include "IMGUI/imgui.h"

namespace reveal3d::ui {

struct Stats {
    std::string fps;
    std::string frameTime;
    std::string deltaTime;
};

class Console {
public:
    Console();
    void Draw(const Timer& timer);
    template<LogLevel lvl>
    static void RightClick() {
    if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
        ImGui::OpenPopup("PopupClicDerecho");
    }

    if (ImGui::BeginPopup("PopupClicDerecho")) {
        if (ImGui::MenuItem("clear")) {
            Logger<lvl>::clear();
        }
        ImGui::EndPopup();
    }
    }
private:
    Stats stats_;
};



}

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file DockSpace.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "menu_bar.hpp"

namespace reveal3d::ui {


class DockSpace {
public:
    DockSpace();
    void draw();
private:
    ImGuiDockNodeFlags dockspace_flags_ = ImGuiDockNodeFlags_PassthruCentralNode;
    MenuBar menu_bar_;
};

};


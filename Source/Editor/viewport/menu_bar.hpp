/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file MenuBar.hpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "IMGUI/imgui.h"
#include "IMGUI/backends/imgui_impl_win32.h"
#include "IMGUI/backends/imgui_impl_dx12.h"


namespace reveal3d::ui {

class MenuBar {
public:
    MenuBar();
    void Draw();
};

}


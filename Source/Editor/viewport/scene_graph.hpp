/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file SceneGraph.hpp
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

#include "core/scene.hpp"

#include <vector>
#include <string>

namespace reveal3d::ui {

class SceneGraph {
public:
    SceneGraph();
    void Draw();
    u32 Selected() { return selected_; }
private:
    bool DrawTreeNode(const core::Scene::Node * const node);
    void DrawSceneGraph();
    std::vector<std::string> entities_names_;
    u32 selected_;
};

}


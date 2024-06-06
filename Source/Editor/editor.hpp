/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details) 
 ************************************************************************/
/**
 * @file editor.hpp
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

#include "Editor/viewport/console.hpp"
#include "Editor/viewport/dock_space.hpp"
#include "Editor/viewport/entity_properties.hpp"
#include "Editor/viewport/scene_graph.hpp"
#include "Editor/viewport/file_explorer.hpp"
#include "render/viewport.hpp"

namespace reveal3d::ui {

class Editor {
public:
    Editor();
    ~Editor();

    template<graphics::HRI T>
    void Init(WHandle window, T& graphics);
    void Draw();

private:
    DockSpace dock_space_;
    EntityProperties entity_properties_;
    SceneGraph scene_graph_;
    Console console_;
    FileExplorer explorer_;

};

template<graphics::HRI T>
void Editor::Init(WHandle window, T& graphics) {

    ImGui_ImplWin32_Init(window.hwnd);
    ImGui_ImplDX12_Init(graphics.GetDevice(), 3,
                        DXGI_FORMAT_R8G8B8A8_UNORM, graphics.GetHeaps().srv.Get(),
                        graphics.GetHeaps().srv.CpuStart(),
                        graphics.GetHeaps().srv.GpuStart());


}

}


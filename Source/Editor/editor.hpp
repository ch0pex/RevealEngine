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

#include "utils.hpp"
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

template<graphics::HRI Gfx, window::Mng<Gfx> Window>
class Editor {
public:
    Editor(render::Viewport<Gfx, Window>& viewport);
    ~Editor();

    void Init(WHandle window, Gfx& graphics);
    void Draw();

private:
    DockSpace dock_space_;
    EntityProperties entity_properties_;
    SceneGraph scene_graph_;
    Console console_;
    FileExplorer explorer_;
    render::Viewport<Gfx, Window>& viewport_;
};

template<graphics::HRI Gfx, window::Mng<Gfx> Window>
Editor<Gfx, Window>::Editor(render::Viewport<Gfx, Window>& viewport) : viewport_(viewport), explorer_("C:\\Alvaro\\Universidad\\tfm") {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    io.ConfigViewportsNoAutoMerge = true;
    io.ConfigViewportsNoTaskBarIcon = true;
    io.WantCaptureKeyboard = false;
    //    std::string font_path = relative("../../Assets/fonts/FontAwesome.ttf");
    //    io.Fonts->AddFontFromFileTTF(font_path.c_str(), 12);
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    SetStyle();
}

template<>
void Editor<graphics::Dx12, window::Win32>::Init(WHandle window, graphics::Dx12& graphics) {

    ImGui_ImplWin32_Init(window.hwnd);
    ImGui_ImplDX12_Init(graphics.GetDevice(), 3,
                        DXGI_FORMAT_R8G8B8A8_UNORM, graphics.GetHeaps().srv.Get(),
                        graphics.GetHeaps().srv.CpuStart(),
                        graphics.GetHeaps().srv.GpuStart());


}

template<>
void Editor<graphics::OpenGL, window::Glfw>::Init(WHandle window, graphics::OpenGL& graphics) {

    //TODO
//    ImGui_ImplWin32_Init(window.hwnd);
//    ImGui_ImplDX12_Init(graphics.GetDevice(), 3,
//                        DXGI_FORMAT_R8G8B8A8_UNORM, graphics.GetHeaps().srv.Get(),
//                        graphics.GetHeaps().srv.CpuStart(),
//                        graphics.GetHeaps().srv.GpuStart());


}



template<>
Editor<graphics::Dx12, window::Win32>::~Editor() {
    ImGui_ImplWin32_Shutdown();
    ImGui_ImplDX12_Shutdown();
    ImGui::DestroyContext();
}

template<>
void Editor<graphics::Dx12, window::Win32>::Draw() {
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DeltaTime = viewport_.Time().DeltaTime();

    dock_space_.Draw();

    scene_graph_.Draw();
    entity_properties_.Draw(scene_graph_.Selected());

    console_.Draw(viewport_.Time());
    explorer_.Draw();

    ImGui::Render();
}
}


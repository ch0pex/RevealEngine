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
#include "Editor/viewport/file_explorer.hpp"
#include "Editor/viewport/scene_graph.hpp"
#include "Project/project.hpp"
#include "render/viewport.hpp"

namespace reveal3d::ui {

template<graphics::HRI Gfx, window::Mng<Gfx> Window>
class Editor {
public:
    Editor(Project& project, window::InitInfo &windowInfo);
    ~Editor();
    void Init();
    void Run();
    void Terminate();

private:
    void Draw();

    DockSpace dock_space_;
    EntityProperties entity_properties_;
    SceneGraph scene_graph_;
    Console console_;
    FileExplorer explorer_;
    render::Viewport<Gfx, Window> viewport_;
    Project& project_;
};

template<graphics::HRI Gfx, window::Mng<Gfx> Window>
Editor<Gfx, Window>::Editor(Project& project, window::InitInfo &windowInfo) :
    viewport_(windowInfo), project_(project), explorer_(project.RootPath())
{
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
void Editor<graphics::Dx12, window::Win32>::Init() {
    auto &graphics = viewport_.renderer.Graphics();
    core::scene.Init();
    viewport_.window.Create(viewport_.renderer);
    viewport_.renderer.Init(viewport_.window.GetHandle());

    ImGui_ImplWin32_Init(viewport_.window.GetHandle().hwnd);
    ImGui_ImplDX12_Init(graphics.GetDevice(), 3,
                        DXGI_FORMAT_R8G8B8A8_UNORM, graphics.GetHeaps().srv.Get(),
                        graphics.GetHeaps().srv.CpuStart(),
                        graphics.GetHeaps().srv.GpuStart());
}

template<>
void Editor<graphics::OpenGL, window::Glfw>::Init() {
    //TODO
}

template<graphics::HRI Gfx, window::Mng<Gfx> Window>
void Editor<Gfx, Window>::Run() {
    viewport_.window.Show();
    log(logDEBUG) << "Initialized";

    viewport_.timer.Reset();
    while(!viewport_.window.ShouldClose()) {
        viewport_.timer.Tick();
        viewport_.window.Update();
        viewport_.window.ClipMouse(viewport_.renderer);
        core::scene.Update(viewport_.timer.DeltaTime());
        viewport_.renderer.Update();
        Draw();
        viewport_.renderer.Render();
    }
}

template<graphics::HRI Gfx, window::Mng<Gfx> Window>
void Editor<Gfx, Window>::Terminate() {
    viewport_.renderer.Destroy();
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

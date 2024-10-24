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

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
class Editor {
public:
    Editor(Project& project, window::Config &window_info);
    ~Editor();
    void init();
    void run();
    void terminate();
    void benchMark(u32 seconds);

private:
    void draw();

    DockSpace dock_space_;
    EntityProperties entity_properties_;
//    WorldProperties world_properties_;
    SceneGraph scene_graph_;
    Console console_;
    FileExplorer explorer_;
    render::Viewport<Gfx, Window> viewport_;
    Project& project_;
};

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
Editor<Gfx, Window>::Editor(Project& project, window::Config &window_info) :
    viewport_(window_info), project_(project), explorer_(project.rootPath())
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
    utl::set_style();
}

template<>
void Editor<graphics::Dx12, window::Win32>::init() {
    auto &graphics = viewport_.renderer.graphics();
    core::scene.init();
    viewport_.window.create(viewport_.renderer);
    viewport_.renderer.init(viewport_.window.getHandle());

    ImGui_ImplWin32_Init(viewport_.window.getHandle().hwnd);
    ImGui_ImplDX12_Init(graphics.device(), 3,
                        DXGI_FORMAT_R8G8B8A8_UNORM, graphics.heaps().srv.get(),
                        graphics.heaps().srv.cpuStart(), graphics.heaps().srv.gpuStart());
}

template<>
void Editor<graphics::OpenGL, window::Glfw>::init() {
    //TODO
}

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
void Editor<Gfx, Window>::run() {
    viewport_.window.show();
    logger(logDEBUG) << "Initialized";

    viewport_.timer.reset();
    while(!viewport_.window.shouldClose()) {
        viewport_.timer.tick();
        viewport_.window.update(viewport_.renderer);
        draw();
        core::scene.update(viewport_.timer.deltaTime());
        viewport_.renderer.update();
        viewport_.renderer.render();
    }
}

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
void Editor<Gfx, Window>::benchMark(u32 seconds) {
    viewport_.window.show();
    logger(logDEBUG) << "Initialized";

    viewport_.timer.reset();
    while(!viewport_.window.shouldClose()) {
        if (seconds < viewport_.time().totalTime())
            break;
        viewport_.timer.tick();
        viewport_.window.update(viewport_.renderer);
        draw();
        core::scene.update(viewport_.timer.deltaTime());
        viewport_.renderer.update();
        viewport_.renderer.render();
    }

    logger(logDEBUG) << viewport_.time().meanFps() << "\n";
}


template<graphics::HRI Gfx, window::Manager<Gfx> Window>
void Editor<Gfx, Window>::terminate() {
    viewport_.renderer.destroy();
}

template<>
Editor<graphics::Dx12, window::Win32>::~Editor() {
    ImGui_ImplWin32_Shutdown();
    ImGui_ImplDX12_Shutdown();
    ImGui::DestroyContext();
}

template<>
void Editor<graphics::Dx12, window::Win32>::draw() {
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.DeltaTime = viewport_.time().deltaTime();

    dock_space_.draw();

    scene_graph_.Draw();
    entity_properties_.draw(scene_graph_.Selected());

    console_.Draw(viewport_.time());
    explorer_.draw();

    ImGui::Render();
}

}

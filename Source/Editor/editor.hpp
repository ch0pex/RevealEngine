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

#include "Editor/utils/imgui.hpp"
#include "Editor/utils/styling.hpp"

#include "Editor/viewport/camera_properties.hpp"
#include "Editor/viewport/console.hpp"
#include "Editor/viewport/dock_space.hpp"
#include "Editor/viewport/entity_properties/entity_properties.hpp"
#include "Editor/viewport/file_explorer.hpp"
#include "Editor/viewport/scene_graph.hpp"
#include "render/viewport.hpp"
#include "viewport/profiler.hpp"


namespace reveal3d::ui {

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
class Editor {
public:
  explicit Editor(render::Viewport<Gfx, Window>& viewport) : explorer_ {reveal3d::absolute("")} {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    io.ConfigViewportsNoAutoMerge   = true;
    io.ConfigViewportsNoTaskBarIcon = true;
    io.WantCaptureKeyboard          = false;
    //    std::string font_path = relative("../../Assets/fonts/FontAwesome.ttf");
    //    io.Fonts->AddFontFromFileTTF(font_path.c_str(), 12);
    ImGuiStyle& style = ImGui::GetStyle();
    if ((io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0) {
      style.WindowRounding              = 0.0F;
      style.Colors[ImGuiCol_WindowBg].w = 1.0F;
    }
    utl::set_style();
    ImGui::Init<Gfx, Window>(viewport.renderer.graphics(), viewport.window.getHandle());
  }

  ~Editor() {
    ImGui::Shutdown<Gfx, Window>();
    ImGui::DestroyContext();
  }

  void draw_components(render::Viewport<Gfx, Window>& viewport) {
    ImGui::NewFrame<Gfx, Window>();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.DeltaTime = viewport.time().deltaTime();

    dock_space_.draw();
    scene_graph_.Draw();

    entity_properties::draw(core::Entity {scene_graph_.selected()});
    camera_properties::draw(viewport.renderer.camera());

    explorer_.draw();

    console::draw();
    profiler::draw(viewport.time());

    ImGui::Render();
  }

private:
  DockSpace dock_space_;
  SceneGraph scene_graph_;
  FileExplorer explorer_;
};


} // namespace reveal3d::ui

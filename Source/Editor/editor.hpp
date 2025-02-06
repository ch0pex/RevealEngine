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
    ImGui::Config();
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

    dockspace::draw();
    scene_graph_.Draw();

    entity_properties::draw(core::Entity {scene_graph_.selected()});
    camera_properties::draw(viewport.renderer.camera());

    explorer_.draw();

    console::draw();
    profiler::draw(viewport.time());

    ImGui::Render();
  }

private:
  SceneGraph scene_graph_;
  FileExplorer explorer_;
};


} // namespace reveal3d::ui

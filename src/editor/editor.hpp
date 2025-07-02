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

#include "editor/utils/imgui.hpp"
#include "editor/utils/styling.hpp"

#include "editor/viewport/camera_properties.hpp"
#include "editor/viewport/console.hpp"
#include "editor/viewport/dock_space.hpp"
#include "editor/viewport/entity_properties/entity_properties.hpp"
#include "editor/viewport/file_explorer.hpp"
#include "editor/viewport/profiler.hpp"
#include "editor/viewport/scene_graph.hpp"
#include "engine/render/viewport.hpp"

namespace rflect3d::ui {

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
class Editor {
public:
  explicit Editor(core::Scene& scene, render::Viewport<Gfx, Window>& viewport) :
    scene_graph_(scene), explorer_ {absolute("")} {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::Config();
    utl::set_style();
    ImGui::Init<Gfx, Window>(viewport.renderer.graphics(), viewport.window.getHandle());
    logger(LogInfo) << "Initializing editor";
  }

  ~Editor() {
    ImGui::Shutdown<Gfx, Window>();
    ImGui::DestroyContext();
    logger(LogInfo) << "Destroying editor";
  }

  void draw_components(render::Viewport<Gfx, Window>& viewport, core::Scene& scene) {
    ImGui::NewFrame<Gfx, Window>();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.DeltaTime = viewport.time().deltaTime();

    dockspace::draw(scene);
    scene_graph_.draw();

    entity_properties::draw(scene_graph_.selected());
    camera_properties::draw(viewport.renderer.camera());

    explorer_.draw();

    console::draw();
    profiler::draw(scene, viewport.time());

    ImGui::Render();
  }

private:
  SceneGraph scene_graph_;
  FileExplorer explorer_;
};


} // namespace rflect3d::ui

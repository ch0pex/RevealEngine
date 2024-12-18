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

#include "utils/imgui.hpp"
#include "utils/styling.hpp"

#include "Editor/viewport/camera_properties.hpp"
#include "Editor/viewport/console.hpp"
#include "Editor/viewport/dock_space.hpp"
#include "Editor/viewport/entity_properties.hpp"
#include "Editor/viewport/file_explorer.hpp"
#include "Editor/viewport/scene_graph.hpp"
#include "render/viewport.hpp"
#include "viewport/profiler.hpp"


namespace reveal3d::ui {

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
class Editor {
public:
  explicit Editor();
  ~Editor();
  void init();
  void run();
  void terminate();
  void benchMark(u32 seconds);

private:
  void draw();

  static void createContext() {
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
  }

  DockSpace dock_space_;
  SceneGraph scene_graph_;
  FileExplorer explorer_;
  render::Viewport<Gfx, Window> viewport_;
};

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
Editor<Gfx, Window>::Editor() : explorer_ {(createContext(), absolute(""))}, viewport_(window::Info()) {
  auto& graphics = viewport_.renderer.graphics();
  viewport_.window.create(viewport_.renderer);
  viewport_.renderer.init(viewport_.window.getHandle());
  ImGui::Init<Gfx, Window>(graphics, viewport_.window.getHandle());
}

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
void Editor<Gfx, Window>::run() {
  viewport_.window.show();
  logger(LogInfo) << "Initialized";

  viewport_.renderer.time().reset();
  while (!viewport_.window.shouldClose()) {
    viewport_.renderer.time().tick();
    viewport_.window.update(viewport_.renderer);
    draw();
    core::scene.update(viewport_.renderer.time().deltaTime());
    viewport_.renderer.update();
    viewport_.renderer.render();
  }
}

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
void Editor<Gfx, Window>::benchMark(u32 seconds) {
  viewport_.window.show();
  logger(LogInfo) << "Initialized";

  viewport_.renderer.time().reset();
  while (!viewport_.window.shouldClose()) {
    [[unlikely]] if (seconds < viewport_.time().totalTime()) { break; }
    viewport_.renderer.time().tick();
    viewport_.window.update(viewport_.renderer);
    draw();
    core::scene.update(viewport_.renderer.time().deltaTime());
    viewport_.renderer.update();
    viewport_.renderer.render();
  }

  logger(LogInfo) << viewport_.time().meanFps() << "\n";
}


template<graphics::HRI Gfx, window::Manager<Gfx> Window>
void Editor<Gfx, Window>::terminate() {
  viewport_.renderer.destroy();
}

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
Editor<Gfx, Window>::~Editor() {
  ImGui::Shutdown<Gfx, Window>();
  ImGui::DestroyContext();
}

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
void Editor<Gfx, Window>::draw() {
  ImGui::NewFrame<Gfx, Window>();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.DeltaTime = viewport_.time().deltaTime();

  dock_space_.draw();
  scene_graph_.Draw();

  entity_properties::draw(core::Entity {scene_graph_.Selected()});
  camera_properties::draw(viewport_.renderer.camera());

  explorer_.draw();

  console::draw();
  profiler::draw(viewport_.time());

  ImGui::Render();
}

} // namespace reveal3d::ui

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file reveal_engine.hpp
 * @version 1.0
 * @date 01/11/2024
 * @brief Reveal Engine Base Class
 *
 */

#pragma once

#include "Editor/editor.hpp"
#include "project/project.hpp"

namespace reveal3d {

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
class Engine {
public:
  Engine() : viewport_(window::Descriptor()), editor_(scene_, viewport_) {};

  void run() {
    scene_.init();
    viewport_.window.show();
    viewport_.renderer.time().reset();
    while (!viewport_.window.shouldClose()) {
      viewport_.renderer.time().tick();
      viewport_.window.update(viewport_.renderer);
      editor_.draw_components(viewport_, scene_);
      scene_.update(viewport_.renderer.time().deltaTime());
      viewport_.renderer.update(scene_);
      viewport_.renderer.render();
    }
  }

  void benchMark(u32 seconds) {
    viewport_.window.show();
    viewport_.renderer.time().reset();
    while (!viewport_.window.shouldClose()) {
      [[unlikely]] if (seconds < viewport_.time().totalTime()) { break; }
      viewport_.renderer.time().tick();
      viewport_.window.update(viewport_.renderer, scene_);
      editor_.draw_components();
      scene_.update(viewport_.renderer.time().deltaTime());
      viewport_.renderer.update(scene_);
      viewport_.renderer.render();
    }
  }

  auto& scene() { return scene_; }

private:
  core::Scene scene_;
  render::Viewport<Gfx, Window> viewport_;
  ui::Editor<Gfx, Window> editor_;
  Project project_;
  Timer timer_;
};

} // namespace reveal3d

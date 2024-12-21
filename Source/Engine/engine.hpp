/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file reveal_engine.hpp
 * @version 1.0
 * @date 01/11/2024
 * @brief Short description
 *
 * Longer description
 */

#pragma once

#include "Editor/editor.hpp"
#include "project/project.hpp"

namespace reveal3d {

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
class Engine {
public:
  Engine() : viewport_(window::Info()), editor_(viewport_) {};

  void run() {
    core::scene.init();
    viewport_.window.show();
    logger(LogInfo) << "Initialized";

    viewport_.renderer.time().reset();
    while (!viewport_.window.shouldClose()) {
      viewport_.renderer.time().tick();
      viewport_.window.update(viewport_.renderer);
      editor_.draw_components(viewport_);
      core::scene.update(viewport_.renderer.time().deltaTime());
      viewport_.renderer.update();
      viewport_.renderer.render();
    }
  }

  void benchMark(u32 seconds) {
    viewport_.window.show();
    logger(LogInfo) << "Initialized";

    viewport_.renderer.time().reset();
    while (!viewport_.window.shouldClose()) {
      [[unlikely]] if (seconds < viewport_.time().totalTime()) { break; }
      viewport_.renderer.time().tick();
      viewport_.window.update(viewport_.renderer);
      editor_.draw_components();
      core::scene.update(viewport_.renderer.time().deltaTime());
      viewport_.renderer.update();
      viewport_.renderer.render();
    }
  }


private:
  render::Viewport<Gfx, Window> viewport_;
  ui::Editor<Gfx, Window> editor_;
  Project project_;
  Timer timer_;
};

} // namespace reveal3d

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
  Engine() : editor_() {};

  void run() {
    core::scene.init();
    editor_.run();
    editor_.terminate();
  }

private:
  ui::Editor<Gfx, Window> editor_;
  Project project_;
  Timer timer_;
};

} // namespace reveal3d

/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file viewport.hpp
 * @version 1.0
 * @date 28/02/2024
 * @brief Short description
 *
 * Viewport template class, it takes two classes as parameters a window manager
 * and a renderer
 *                                 ----------
 *                                | Viewport |
 *                                 ----------
 *                                     |
 *                  -----------------------------------------
 *                  |                                       |
 *              ----------                              ----------
 *             | Renderer |                           | Window Manager |
 *              ----------                              ----------
 *                  |                                       |
 *         -------------------                   -------------------------
 *         |                 |                   |                       |
 *   ----------          ----------         ----------               ----------
 *  |   Dx12   |        |  OpenGL  |       |  Win32   |             |   GLFW   |
 *   ----------          ----------         ----------               ----------
 *
 */

#pragma once

#include "engine/window/window.hpp"
#include "renderer.hpp"

#include <iostream>
#include <stdexcept>

namespace rflect3d::render {

template<graphics::HRI Gfx, window::Manager<Gfx> Window>
struct Viewport {
  explicit Viewport(window::Descriptor const& windowInfo) : window(windowInfo), renderer(window.getRes()) {
    try {
      window.create(renderer);
      renderer.init(window.getHandle());
      window.show();
    }
    catch (std::exception& e) {
      LOG_ERROR(e.what();
    };
  }

  Timer& time() { return renderer.time(); }

  Window window;
  Renderer<Gfx> renderer;
};

} // namespace rflect3d::render

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
    editor_.init();
    editor_.run();
    editor_.terminate();
  }

private:
  ui::Editor<Gfx, Window> editor_;
  Project project_;
};

namespace engine {
// template<typename T>

namespace detail {

template<typename T>
auto run_backend(config::backends::renderer const renderer) {
  switch (renderer) {
    case config::backends::directx12:
      Engine<graphics::Dx12, T>().run();
      break;
    case config::backends::directx11:
      logger(LogError) << "DirectX11 backend not implemented";
      // Engine<graphics::Dx11, T>().run();
      break;
    case config::backends::openGl:
      Engine<graphics::OpenGL, T>().run();
      break;
    case config::backends::vulkan:
      logger(LogError) << "Vulkan backend not implemented";
      // Engine<graphics::Vulkan, T>().run();
      break;
    case config::backends::metal:
      logger(LogError) << "Metal backend not implemented";
      // Engine<graphics::Metal, T>().run();
      break;
  }
};

} // namespace detail

inline void run_from_cfg(config::Backends const backends) {
  switch (backends.window) {
    case config::backends::win32:
      detail::run_backend<window::Win32>(backends.renderer);
      break;
    case config::backends::glfw:
      detail::run_backend<window::Win32>(backends.renderer);
      break;
  }
}

} // namespace engine

} // namespace reveal3d

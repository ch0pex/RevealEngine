/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file run_engine.hpp
 * @version 1.0
 * @date 17/12/2024
 * @brief Run Engine
 *
 * Running Engine configurations
 *
 */

#pragma once

#include "config/config.hpp"
#include "engine.hpp"

namespace reveal3d::engine {

namespace detail {

template<typename T>
void run_backend(config::backends::renderer const renderer) {
  switch (renderer) {
#ifdef WIN32
    case config::backends::directx12:
      Engine<graphics::Dx12, T>().run();
      break;
    case config::backends::directx11:
      logger(LogError) << "DirectX11 backend not implemented";
      // Engine<graphics::Dx11, T>().run();
      break;
#endif
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
#ifdef WIN32
    case config::backends::win32:
      detail::run_backend<window::Win32>(backends.renderer);
      break;
#endif
    case config::backends::glfw:
      detail::run_backend<window::Glfw>(backends.renderer);
      break;
  }
}

inline void benchmark_from_cfg(config::Backends const backends) {
  switch (backends.window) {
#ifdef WIN32
    case config::backends::win32:
      detail::run_backend<window::Win32>(backends.renderer);
      break;
#endif
    case config::backends::glfw:
      detail::run_backend<window::Glfw>(backends.renderer);
      break;
  }
}

} // namespace reveal3d::engine

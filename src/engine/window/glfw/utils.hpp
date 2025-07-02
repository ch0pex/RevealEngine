/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file glfw.hpp
 * @version 1.0
 * @date 10/04/2025
 * @brief GLFW utilities
 *
 * The main goal of this utilities is to wrap the code of glfw that is platform dependent
 */

#pragma once

#include "engine/window/window_info.hpp"

#include <optional>


namespace rflect3d::window::glfw {

namespace detail {

inline GLFWwindow* create_window(Descriptor const& descriptor) {
  return glfwCreateWindow(descriptor.res.width, descriptor.res.height, descriptor.name, NULL, NULL);
}

} // namespace detail

#ifdef WIN32

inline bool create_window(Descriptor& descriptor) {
  GLFWwindow* window     = detail::create_window(descriptor);
  descriptor.handle.hwnd = glfwGetWin32Window(window);
  return window;
}

#else

inline bool create_window(Descriptor& descriptor) {
  WindowHandle const window = detail::create_window(descriptor);
  descriptor.handle         = window;
  return window != nullptr;
}

#endif

} // namespace rflect3d::window::glfw

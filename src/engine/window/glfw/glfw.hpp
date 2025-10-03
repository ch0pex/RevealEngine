/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file glfw.hpp
 * @version 1.0
 * @date 27/02/2024
 * @brief Short description
 *
 * GLFW backend manager class
 */

#pragma once

#include "engine/input/input.hpp"
#include "engine/render/renderer.hpp"
#include "engine/window/window_info.hpp"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "utils.hpp"

#include <exception>


namespace rflect3d::window {

class Glfw {
public:
  explicit Glfw(Descriptor const& info) { }

  template<graphics::HRI Gfx>
  void create(render::Renderer<Gfx>& renderer) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (not glfw::create_window(info_)) {
      glfwTerminate();
      LOG_ERROR("Error creating GLFW window, app will terminate.");
      std::terminate();
    }
#ifndef WIN32
    glfwMakeContextCurrent(info_.handle);
#else
    glfwMakeContextCurrent(window_pointer_);
#endif

    glfwSwapInterval(0);
  }

  void show() { }

  template<graphics::HRI Gfx>
  static void update(render::Renderer<Gfx>& renderer) {
    glfwPollEvents();
  }

  void closeWindow(input::Action act, input::type type);

  bool shouldClose() const { return glfwWindowShouldClose(window_pointer_); }

  [[nodiscard]] Resolution getRes() const { return info_.res; }

  [[nodiscard]] WindowHandle getHandle() const { return info_.handle; }

  [[nodiscard]] auto getWindowPtr() const {
#ifdef WIN32
    return info_.handle.hwnd;
#else
    return info_.handle;
#endif
  }

private:
  template<graphics::HRI Gfx>
  void clipMouse(render::Renderer<Gfx>& renderer) {
    // Void
  }

  Descriptor info_;
  GLFWwindow* window_pointer_;
};

} // namespace rflect3d::window

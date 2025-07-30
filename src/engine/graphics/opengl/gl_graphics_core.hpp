/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file graphics_core.hpp
 * @version 1.0
 * @date 05/04/2024
 * @brief Short description
 *
 * Longer description
 */
#pragma once

#include "engine/render/camera.hpp"
#include "engine/scene/scene.hpp"
#include "gl_render_info.hpp"

#include "gl_render_layers.hpp"

namespace rflect3d::graphics {

struct Surface { };

class OpenGL {
public:
  using surface = Surface;

  explicit OpenGL(window::Resolution res);

  void loadPipeline() { }

  void loadAssets(Scene& scene) { }

  void loadAsset() { }

  void update(Scene& scene, render::Camera const& camera) { }

  void render() {
    Surface mock;
    renderSurface(mock);
  }

  void renderSurface(surface& surface) { }

  void resize(window::Resolution const& res) { }

  void initWindow(WindowHandle const& w_handle) { window_ = w_handle; }

private:
  void createContext() { }

  void swapBuffer() const { }

  void terminateContext() const { }

  math::mat4 pass_constant_ {};
  std::vector<opengl::RenderElement> render_elements_ {};
  opengl::RenderLayers render_layers_;
  WindowHandle window_ {};
};

} // namespace rflect3d::graphics

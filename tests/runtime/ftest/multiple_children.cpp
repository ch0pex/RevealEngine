/************************************************************************
 * Copyright (c) 2025 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file high_poly_meshes.cpp
 * @version 1.0
 * @date 03/02/2025
 * @brief Functional s
 *
 */

#include "app/engine_cfg.hpp"
#include "app/run_engine.hpp"
#include "editor/editor.hpp"

using namespace rflect3d;

#ifdef WIN32

using Renderer      = graphics::Dx12;
using WindowManager = window::Win32;

#else

using Renderer      = graphics::OpenGL;
using WindowManager = window::Glfw;

#endif


i32 main() {
  auto engine        = Engine<Renderer, WindowManager>();
  core::Scene& scene = engine.scene();

  core::Entity const entity = core::new_entity(scene);

  for (i32 i = 0; i < 10; ++i) {
    auto child = entity.addChild();
    for (i32 j = 0; j < 4; ++j) {
      child.addChild();
    }
  }

  engine.run();
}

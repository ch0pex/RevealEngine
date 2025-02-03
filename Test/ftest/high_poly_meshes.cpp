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

#include "Editor/editor.hpp"
#include "Engine/engine_cfg.hpp"
#include "Engine/run_engine.hpp"

using namespace reveal3d;
using namespace reveal3d::core;
using namespace reveal3d::literals;

void add_entities(Scene& scene, u32 const num) {
  auto const human = content::import_obj("../../Assets/models/highpoly_sphere.obj"_abs);
  if (!human)
    return;

  for (u32 i = 0; i < num; ++i) {
    for (u32 j = 0; j < num; ++j) {
      for (u32 k = 0; k < num; ++k) {
        auto human_copy = human.value();
        Entity entity   = core::new_entity(scene);
        entity.addComponent<Geometry>(std::move(human_copy));
        entity.component<Transform>().position(
            {static_cast<f32>(i * 3), static_cast<f32>(j * 3), static_cast<f32>(k * 3)}
        );
      }
    }
  }
}

i32 main() {
  Scene scene;
  add_entities(scene, 5);
  auto engine = Engine<graphics::Dx12, window::Win32>(std::move(scene));
  engine.run();
}

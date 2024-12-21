/************************************************************************
 * Copyright (c) 2024 Alvaro Cabrera Barrio
 * This code is licensed under MIT license (see LICENSE.txt for details)
 ************************************************************************/
/**
 * @file main.cpp
 * @version 1.0
 * @date 02/06/2024
 * @brief Short description
 *
 * Longer description
 */

#include "Editor/editor.hpp"
#include "Engine/engine_cfg.hpp"
#include "Engine/run_engine.hpp"
#include "content/content.hpp"
#include "core/components/transform.hpp"

using namespace reveal3d;
using namespace reveal3d::core;
using namespace reveal3d::literals;

void add_entities(u32 const num) {
  auto const human = content::import_obj("../../Assets/models/highpoly_sphere.obj"_abs);
  if (!human)
    return;

  for (u32 i = 0; i < num; ++i) {
    for (u32 j = 0; j < num; ++j) {
      for (u32 k = 0; k < num; ++k) {
        auto human_copy = human.value();
        Entity entity   = scene.newEntity();
        entity.addComponent<Geometry>(std::move(human_copy));
        entity.component<Transform>().position(
            {static_cast<f32>(i * 3), static_cast<f32>(j * 3), static_cast<f32>(k * 3)}
        );
      }
    }
  }
}

void add_child() {
  Entity const entity = scene.newEntity();
  entity.addChild();
  entity.addChild();
  entity.addChild();
}

i32 main(i32 const argc, char* argv[]) {
  auto const config = engine::read_config(std::span(argv, argc));
  add_entities(1);
  engine::run_from_cfg(config);
}
